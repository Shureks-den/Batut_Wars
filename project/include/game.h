#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "player.h"
#include "render.h"
#include "world.h"

class Game : sf::NonCopyable {
 public:
  Game();
  ~Game() = default;
  void run();

 private:
  void draw();
  bool update(sf::Time dt);
  void render(sf::Time dt);
  bool handle_event(const sf::Event& event);
  void get_input();

  void update_statistic(sf::Time time);

  sf::RenderWindow _window;
  World _world;    // Логика игры
  Render _render;  // Отрисовка игры
  Player _player;  // Читать команды игрока

  sf::Time _update_time;
  size_t _frames;
  sf::Font _statistic_font;
  sf::Text _statistic_text;

  static const sf::Time _time_per_frame;
};
