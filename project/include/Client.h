#pragma once

#include <SFML/Network.hpp>

#include "GameState.h"
#include "Player.h"
#include "Status.h"

namespace network {

class Client {
 public:
    Client() = default;
    explicit Client(std::pair<sf::IpAddress, uint16_t> const &adress);
    ~Client() = default;

    size_t get_id() const;
    void send_actions();
    std::queue<Player::Action>& get_actions();
    std::vector<Status> get_status();
    void set_adress(std::pair<sf::IpAddress, uint16_t> const &adress);

 private:
    sf::TcpSocket _server;

    // sf::IpAddress _server_ip;
    // uint16_t _server_port;

    size_t _id;
    std::queue<Player::Action> _actions;
};

}  // namespace network
