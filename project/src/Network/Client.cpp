#include "Client.h"

#include "Network.h"
#include <iostream>

namespace network {

Client::Client() : _is_connected(false) {}

Client::Client(std::pair<sf::IpAddress, uint16_t> const &adress) {
    connect(adress);
}

size_t Client::get_id() const {
    return _id;
}

void Client::send_actions() {
    sf::Packet output_packet;
    output_packet << _actions;
    _server.send(output_packet);
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
    _is_connected = true;
    std::cout << "MY ID IS: " << _id << " (" << tmp << ")" << std::endl;
    return true;
}

void Client::disconnect() {
    _server.disconnect();
    _server.setBlocking(true);  // TODO(ANDY) надо или нет?
    _is_connected = false;
}

std::vector<std::vector<Status>> Client::get_status() {
    sf::Packet input_packet;
    std::vector<std::vector<Status>> status;
    if (_server.receive(input_packet) == sf::Socket::Done) {
        input_packet >> status;
    }
    return status;
}

bool Client::is_connected() const {
    return _is_connected;
}

}  // namespace network