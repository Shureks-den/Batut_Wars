#include "Server.h"

#include <utility>
#include <iostream>

#include "Network.h"
#include "Ship.h"

namespace network {

Server::Server() : _time_per_update(sf::seconds(1.0 / 120.0)),
                   _ip(sf::IpAddress::getLocalAddress()),
                   //_port(sf::Socket::AnyPort),
                   _port(2000),
                   _host(0) {}

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
        if (_selector.wait()) {
            // if (_clients.size() != 0 && _selector.isReady(*_clients[_host])) {
            //     if (is_started()) {
            //         return;
            //     }
            // }
            add_client();
        }
        if (_clients.size() != 0) {
            if (is_started()) {
                return;
            }
        }
    }
}

void Server::get_client_actions() {
    sf::Packet input_packet;
    for (auto &it : _clients) {
        // if (!_selector.isReady(*it)) {
        //     continue;
        // }

        if (it->receive(input_packet) == sf::Socket::Done) {
            input_packet >> _world.get_actions();
        }
    }
}

void Server::send_update() {
    sf::Packet output_packet;
    auto status = _world.get_status();
    output_packet << status;
    for (auto &it : _clients) {
        // if (!_selector.isReady(*it)) {
        //     continue;
        // }

        it->send(output_packet);
    }
}

void Server::add_client() {
    // if (_selector.isReady(_listener)) { // Почему-то ломается
        std::cout << "ADD CLIENT 1" << std::endl;
        auto socket = std::shared_ptr<sf::TcpSocket>(new sf::TcpSocket);
        std::cout << "ADD CLIENT 2" << std::endl;
        _listener.accept(*socket);
        std::cout << "ADD CLIENT 3" << std::endl;
        sf::Packet output_packet;
        std::cout << "ADD CLIENT 4" << std::endl;
        output_packet << static_cast<int>(_clients.size());
        std::cout << "SERVER IS GOING TO SEND ID " << _clients.size() << std::endl;

        if (socket->send(output_packet) == sf::Socket::Done) {
            std::cout << "SERVER SELECTOR ADD SOCKET"<< std::endl;
            _selector.add(*socket);
            std::cout << "SERVER PUSH_BACK" << std::endl;
            _clients.push_back(std::move(socket));
            std::cout << "CLIENTS: " << _clients.size() << std::endl;
        } else {
            std::cout << "FAIL SENDING ID" << _clients.size() << std::endl;
        }
    // }
}

bool Server::is_started() {
    std::cout << "IS STARTED?" << std::endl;
    if (_clients.size() == 1) {
        std::cout << "GAME START" << std::endl;
        return true;
    } else {
        return false;
    }

    sf::Packet input_packet;
    if (_clients[_host]->receive(input_packet) != sf::Socket::Done) {
        return false;
    }

    int code;
    input_packet >> code;
    return (code == network::START);
}

}  // namespace network
