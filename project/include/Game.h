#pragma once

#include "Player.h"
#include "StateStack.h"
#include "Holder.h"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

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
    StateStack _state_stack;

  static const sf::Time _time_per_frame;
};
