#pragma once

#include <SFML/Network.hpp>
#include <SFML/System/Time.hpp>

#include "World.h"

namespace network {

constexpr int START = 1;

class Server {
 public:
    Server();
    ~Server() = default;
    void run();
    std::pair<sf::IpAddress, uint16_t> get_adress() const;
    size_t get_players() const;
    void start_game();

 private:
    World _world;
    sf::Time _time_per_update;

    std::vector<std::shared_ptr<sf::TcpSocket>> _clients;
    sf::SocketSelector _selector;
    sf::TcpListener _listener;
    sf::IpAddress _ip;
    /*const*/ uint16_t _port;
    size_t _host;

    void read_action(size_t client_id);
    void accept_clients();
    void get_client_actions();
    void send_update();
    void send_waiting();
    void add_client();
    bool is_started();

    bool _is_started;
};

}  // namespace network
