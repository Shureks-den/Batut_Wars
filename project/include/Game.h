#pragma once

#include <thread>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Player.h"
#include "Client.h"
#include "Server.h"
#include "States/StateStack.h"
#include "Holder.h"

class Game : sf::NonCopyable {
 public:
  Game();
  ~Game() = default;
  void run();

 private:
    bool update(sf::Time dt);
    void render();
    bool handle_event(const sf::Event& event);
    void get_input();

    void registrates();

    sf::RenderWindow _window;
    Player _player;  // Читать команды игрока

    textures::Holder _textures;
    fonts::Holder _fonts;

    std::pair<sf::IpAddress, uint16_t> _network_info;  // Как сервер
    network::Client _client;
    network::Server _server;
    std::thread _server_thread;

    StateStack _state_stack;

  static const sf::Time _time_per_frame;
};
