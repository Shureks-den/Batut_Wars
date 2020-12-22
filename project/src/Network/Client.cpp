#include "Client.h"

#include <iostream>
#include <mutex>

#include "Network.h"

static std::mutex client_mutex;

namespace network {

Client::Client() : _is_connected(false) {}

Client::Client(std::pair<sf::IpAddress, uint16_t> const &adress) {
    connect(adress);
}

size_t Client::get_id() const {
    return _id;
}

void Client::send_actions() {
    std::unique_lock<std::mutex> lock(client_mutex);
    if (_actions.empty()) {
        return;
    }

    sf::Packet output_packet;
    output_packet << _actions;
    _server.send(output_packet);
}

void Client::receive_status() {
    sf::Packet input_packet;
    if (_selector.wait(sf::microseconds(10))) {
        if (_selector.isReady(_server)) {
            if (_server.receive(input_packet) == sf::Socket::Done) {
                input_packet >> _status;
            }
        }
    }
}

void Client::run() {
    while (true) {
        send_actions();
        receive_status();
    }
}

std::queue<Player::Action>& Client::get_actions() {
    return _actions;
}

bool Client::connect(std::pair<sf::IpAddress, uint16_t> const &adress) {
    std::cout << "Client is trying to connect" << std::endl;
    if (_server.connect(adress.first, adress.second, sf::seconds(10)) != sf::Socket::Done) {
        return false;
    }
    std::cout << "Connectd" << std::endl;
    sf::Packet input_packet;
    if (_server.receive(input_packet) != sf::Socket::Done) {
        std::cout << "CANT FIND MY ID" << std::endl;
        _server.disconnect();
        std::cout << "DISCONNECTED" << std::endl;
        return false;
    }
    int tmp;
    input_packet >> tmp;
    _id = static_cast<size_t>(tmp);

    _server.setBlocking(false);
    _selector.add(_server);
    _is_connected = true;
    std::cout << "MY ID IS: " << _id << " (" << tmp << ")" << std::endl;
    return true;
}

void Client::disconnect() {
    _selector.remove(_server);
    _server.disconnect();
    // _server.setBlocking(true);  // TODO(ANDY) надо или нет?
    _is_connected = true;
}

std::vector<std::vector<Status>> Client::get_status() {
    std::unique_lock<std::mutex> lock(client_mutex);
    // client_mutex.lock();

    // std::cout << "GET_STATUS" << std::endl;
    // if (_status.empty()) {
    //     std::cout << "EMPTY" << std::endl;
    // }
    // for (auto &it : _status) {
    //     for (auto &it2 : it) {
    //         std::cout << "ID: " << it2.id << std::endl << "ANIMAYION ID "
    //                   << static_cast<size_t>(it2.animation_id) << std::endl;
    //     }
    // }

    // std::vector<std::vector<Status>> status;
    // status.assign(_status.begin(), _status.end());
    // client_mutex.unlock();
    // return status;
    return _status;
}

bool Client::is_connected() const {
    return _is_connected;
}

}  // namespace network