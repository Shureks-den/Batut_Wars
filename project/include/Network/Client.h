#pragma once

#include <SFML/Network.hpp>

#include "Player.h"
#include "Status.h"

namespace network {

class Client {
 public:
    Client();
    explicit Client(std::pair<sf::IpAddress, uint16_t> const &adress);
    ~Client() = default;

    void run();

    size_t get_id() const;
    std::queue<Player::Action>& get_actions();
    std::vector<std::vector<Status>> get_status();
    bool connect(std::pair<sf::IpAddress, uint16_t> const &adress);
    void disconnect();

    bool is_connected() const;
    bool is_game_started() const;

 private:
    sf::TcpSocket _server;
    sf::IpAddress _server_ip;
    uint16_t _server_port;
    sf::SocketSelector _selector;

    size_t _id;

    std::queue<Player::Action> _actions;
    std::vector<std::vector<Status>> _status;

    bool _is_connected;
    int _result;

    void send_actions();
    void receive_status();
};

}  // namespace network
