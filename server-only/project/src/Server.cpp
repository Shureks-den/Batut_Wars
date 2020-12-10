#include "Server.h"

#include <iostream>
#include <utility>

#include "Network.h"

namespace network {

Server::Server() : _time_per_update(sf::seconds(1.0 / 120.0)),
                   _ip(sf::IpAddress::getLocalAddress()),
                   _port(sf::Socket::AnyPort),
                   _host(0) {
    // _port = 2000;
    _listener.listen(_port);
    _selector.add(_listener);
}

Server::~Server() {
    for (auto &it : _clients) {
        delete it;
    }
}

void Server::run() {
    std::cout << "SERVER IS RUNING" << std::endl;
    accept_clients();
    std::cout << "GAME IS STARTED. TOTAL PLAYERS CONNECTED: " << _clients.size() << std::endl;

    sf::Clock clock;
    sf::Time total_time = sf::Time::Zero;

    while (!_world.is_over()) {
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
    while (true) {  // Пока хост не запустил игру
        if (!_selector.wait()) {
            continue;
        }

        if (_clients.size() != 0 && _selector.isReady(*_clients[_host])) {
            if (is_started()) {
                return;
            }
        }

        add_client();
    }
}

void Server::get_client_actions() {
    if (!_selector.wait()) {
        return;
    }

    sf::Packet input_packet;
    for (auto &it : _clients) {
        if (!_selector.isReady(*it)) {
            continue;
        }

        if (it->receive(input_packet) == sf::Socket::Done) {
            input_packet >> _world.get_actions();
        }
    }
}

void Server::send_update() {
    sf::Packet input_packet;
    input_packet << &_world.get_status();
    for (auto &it : _clients) {
        it->receive(input_packet);
    }
}

void Server::add_client() {
    if (_selector.isReady(_listener)) {  // TODO(ANDY) подключение игроков и ожидание
        auto *socket = new sf::TcpSocket;
        _listener.accept(*socket);
        sf::Packet output_packet;
        output_packet << static_cast<int>(_clients.size());

        if (socket->receive(output_packet) == sf::Socket::Done) {
            _clients.push_back(socket);
            _selector.add(*socket);
        }
        std::cout << "CLIENT " << socket->getRemoteAddress().toString() << "CONNECTED" << std::endl;
    }
}

bool Server::is_started() {
    // if (_clients.size() == 1) {
    //     return true;
    // }
    sf::Packet input_packet;
    if (_clients[_host]->receive(input_packet) != sf::Socket::Done) {
        return false;
    }

    int code;
    input_packet >> code;
    return (code == network::START);
}

}  // namespace network
