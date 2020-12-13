#include "Server.h"

#include <utility>
#include <iostream>

#include "Network.h"

namespace network {

Server::Server() : _time_per_update(sf::seconds(1.0 / 120.0)),
                   _ip(sf::IpAddress::getLocalAddress()),
                   //_port(sf::Socket::AnyPort),
                   _port(2000),
                   _host(0) {}

Server::~Server() {
    for (auto &it : _clients) {
        delete it;
    }
}

void Server::run() {
    _listener.listen(_port);
    _selector.add(_listener);

    accept_clients();

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
        std::cout << "PLAYER CONNECTED" << std::endl;
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
    for (auto &it : _clients) {
        if (!_selector.isReady(*it)) {
            continue;
        }

        if (it->receive(input_packet) == sf::Socket::Done) {
            input_packet >> _world.get_actions();
        }
    }
}

void Server::add_client() {
    if (_selector.isReady(_listener)) {      // TODO(ANDY) подключение игроков и ожидание
        auto *socket = new sf::TcpSocket;
        _listener.accept(*socket);
        sf::Packet output_packet;
        output_packet << static_cast<int>(_clients.size());

        if (socket->receive(output_packet) == sf::Socket::Done) {
            _clients.push_back(socket);
            _selector.add(*socket);
        }
    }
}

bool Server::is_started() {
    sf::Packet input_packet;
    if (_clients[_host]->receive(input_packet) != sf::Socket::Done) {
        return false;
    }

    int code;
    input_packet >> code;
    return (code == network::START);
}

}  // namespace network
