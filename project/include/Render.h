#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Animation.h"
#include "AnimationCreator.h"
#include "Layer.h"
#include "Status.h"

#include "Sound.h"

class Render : private sf::NonCopyable {
 public:
  explicit Render(sf::RenderWindow &window);
  void update(sf::Time dt);
  void set_status(const std::vector<std::vector<Status>> &status);
  void draw();
  void inicilize(const std::vector<std::vector<Status>> &status);
  sf::View &get_view();
  void set_player_id(size_t id);

 private:
  void build_scene();
  void add_animation(size_t lay, Status &status);
  void explosion(size_t i, size_t j);
  void sound_render(size_t i, size_t j);

 private:
  sf::RenderWindow &_window;
  sf::View _view;
  std::array<animation::Layer, static_cast<size_t>(animation::Id::COUNT)> _animation_layers;
  std::vector<std::vector<Status>> _status;
  animation::Creator _creator;
  size_t _player_id;

  sounds::SoundPlayer _sound_player;

  sf::Vector2f _extra_size;
};
