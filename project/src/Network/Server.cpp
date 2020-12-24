#include "Server.h"

#include <utility>
#include <iostream>
#include <mutex>

#include "Network.h"
#include "Ship.h"

static std::mutex server_mutex;

namespace network {

Server::Server() : _time_per_update(sf::seconds(1.0 / 60.0)),
                   _ip(sf::IpAddress::getLocalAddress()),
                   //_port(sf::Socket::AnyPort),
                   _port(2000),
                   _host(0),
                   _is_started(false) {}

Server::~Server() {}

void Server::run() {
    _listener.listen(_port);
    _selector.add(_listener);

    accept_clients();

    for (size_t i = 0; i < _clients.size(); ++i) {
        auto player = std::unique_ptr<space::Ship>(new space::Ship());
        player->set_id(i);
        player->set_position(sf::Vector2f(200 + 200 * i, 400));
        _world.push_player(std::move(player));
    }
    std::cout << "LET'S START GAME" << std::endl;

    sf::Clock clock;
    sf::Time total_time = sf::Time::Zero;

    while (!_world.is_over()) {  // DANGER!
        sf::Time current_time = clock.restart();
        total_time += current_time;

        get_client_actions();

        while (total_time > _time_per_update) {
            total_time -= _time_per_update;

            _world.update(_time_per_update);
            send_update();
        }
    }
}

std::pair<sf::IpAddress, uint16_t> Server::get_adress() const {
    return std::make_pair(_ip, _port);
}

void Server::accept_clients() {
    sf::Clock clock;
    sf::Time total_time = sf::Time::Zero;

    while (true) {  // Пока хост не запустил игру
        sf::Time current_time = clock.restart();
        total_time += current_time;

        if (_selector.wait(sf::microseconds(10))) {
            add_client();
        }
        if (_clients.size() != 0) {
            if (is_started()) {
                return;
            }
        }
        
        while (total_time > _time_per_update) {
            total_time -= _time_per_update;
            send_waiting();
        }
    }
}

void Server::get_client_actions() {
    for (size_t i = 0; i < _clients.size(); ++i) {
        if (_selector.wait(sf::microseconds(10))) {
            if (_selector.isReady(*_clients[i])) {
                read_action(i);
            }
        }
    }
}

void Server::read_action(size_t client_id) {
    sf::Packet input_packet;
    if (_clients[client_id]->receive(input_packet) == sf::Socket::Done) {
        std::queue<Player::Action> actions;
        input_packet >> actions;
        auto &world_action = _world.get_actions();
        while (!actions.empty()) {
            world_action.push(std::make_pair(client_id, actions.front()));
            actions.pop();
        }
    }
}

void Server::send_update() {
    sf::Packet output_packet;
    int result = 1;  // КОСТЫЛЬ-ЗАГЛУШКА
    output_packet << result;
    auto status = _world.get_status();
    output_packet << status;
    for (auto &it : _clients) {
        if (it->send(output_packet) == sf::Socket::Disconnected) {
            _selector.remove(*it);
            it->disconnect();
        }
    }
}

void Server::send_waiting() {
    sf::Packet output_packet;
    int result = 0;
    output_packet << result;
    for (auto &it : _clients) {
        if (it->send(output_packet) == sf::Socket::Disconnected) {
            _selector.remove(*it);
            it->disconnect();
        }
    }
}

void Server::add_client() {
    if (_selector.isReady(_listener)) {
        auto socket = std::shared_ptr<sf::TcpSocket>(new sf::TcpSocket);
        _listener.accept(*socket);
        sf::Packet output_packet;
        output_packet << static_cast<int>(_clients.size());

        if (socket->send(output_packet) == sf::Socket::Done) {
            _selector.add(*socket);
            _clients.push_back(std::move(socket));
        } else {
            _listener.close();
        }
    }
}

bool Server::is_started() {
    return _is_started;
}

void Server::start_game() {
    std::unique_lock<std::mutex> lock(server_mutex);
    _is_started = true;
}

size_t Server::get_players() const {
    std::unique_lock<std::mutex> lock(server_mutex);
    return _clients.size();
}

}  // namespace network