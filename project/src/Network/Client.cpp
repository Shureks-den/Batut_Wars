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
    _ser->send(output_packet);
    // _server.send(output_packet);
}

void Client::receive_status() {
    if (_selector.wait(sf::microseconds(10))) {
        if (_selector.isReady(*_ser)) {
        // if (_selector.isReady(_server)) {
            std::vector<Mission> mission;
            sf::Packet input_packet;
            if (_ser->receive(input_packet) == sf::Socket::Done) {
            // if (_server.receive(input_packet) == sf::Socket::Done) {
                input_packet >> mission;
                if (mission.empty()) {
                    return;
                }
                _mission_status = mission[_id];
                input_packet >> _status;
            }
        }
    }
}

void Client::run() {
    _mission_status = Mission::AWAITING;
    while (_mission_status == Mission::AWAITING) {
        receive_status();
    }

    while (_mission_status == Mission::RUN) {
        send_actions();
        receive_status();
    }

    sf::Clock clock;
    clock.restart();
    while (clock.getElapsedTime().asSeconds() < 5) {
        send_actions();
        receive_status();
    }

    disconnect();
    std::cout << "CLIENT END" << std::endl;
}

std::queue<Player::Action> &Client::get_actions() { return _actions; }

bool Client::connect(std::pair<sf::IpAddress, uint16_t> const &adress) {
    std::cout << "Client is trying to connect" << std::endl;
    _ser = std::make_unique<sf::TcpSocket>();
    auto connection = _ser->connect(adress.first, adress.second, sf::seconds(5));
    // auto connection = _server.connect(adress.first, adress.second, sf::seconds(5));
    std::cout << connection << std::endl;
    if (connection != sf::Socket::Done) {
        return false;
    }
    std::cout << "Connectd" << std::endl;
    sf::Packet input_packet;
    if (_ser->receive(input_packet) != sf::Socket::Done) {
    // if (_server.receive(input_packet) != sf::Socket::Done) {
        std::cout << "CANT FIND MY ID" << std::endl;
        _ser->disconnect();
        // _server.disconnect();
        std::cout << "DISCONNECTED" << std::endl;
        return false;
    }
    int tmp;
    input_packet >> tmp;
    _id = static_cast<size_t>(tmp);

    //  _server.setBlocking(false);
    _ser->setBlocking(false);
    // _selector.add(_server);
    _selector.add(*_ser);
    _is_connected = true;
    std::cout << "MY ID IS: " << _id << " (" << tmp << ")" << std::endl;

    _mission_status = Mission::AWAITING;
    return true;
}

void Client::disconnect() {
    std::unique_lock<std::mutex> lock(client_mutex);
    // _selector.remove(_server);
    _selector.remove(*_ser);
    _ser->disconnect();
    // _server.disconnect();
    _is_connected = false;
}

std::vector<std::vector<Status>> Client::get_status() const {
    std::unique_lock<std::mutex> lock(client_mutex);
    return _status;
}

Mission Client::get_mission() const {
    std::unique_lock<std::mutex> lock(client_mutex);
    return _mission_status;
}

bool Client::is_connected() const {
    return _is_connected;
}

bool Client::is_game_started() const {
    std::unique_lock<std::mutex> lock(client_mutex);
    return (_mission_status != Mission::AWAITING);
}

}  // namespace network