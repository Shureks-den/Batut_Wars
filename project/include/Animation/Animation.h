#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Holder.h"
#include "Identificators.h"
#include "Status.h"

namespace animation {

class Manager {
 public:
  explicit Manager(const sf::Texture *texture,
                   sf::Vector2f position = sf::Vector2f(0, 0), float angle = 0);
  Manager(const Manager &) = default;
  ~Manager() = default;

  virtual void update(sf::Time d_time);
  void draw(sf::RenderWindow &window);

  void set_states(const std::vector<bool> &states);
  void set_position(const sf::Vector2f &position);
  void set_angle(const float angle);
  void set_start_angle(float start_angle);
  sf::Vector2f get_size() const;
  void set_size(sf::Vector2f size);
  void set_origin(sf::Vector2f center);
  void set_size_s(sf::Vector2f size);

  void set_switch_time(sf::Time switch_time);
  void set_image_count(sf::Vector2u image_count);
  void set_playing(bool is_playing);
  bool is_playing() const;

 protected:
  sf::Vector2u _image_count;
  sf::Vector2u _current_image;

  sf::Time _total_time;
  sf::Time _switch_time;

  sf::IntRect _uv_rect;
  sf::RectangleShape _body;

  std::vector<bool> _status;

  bool _is_playing;

  float _angle;
  float _start_angle;  // Угол между анимацией и OX
};

}  // namespace animation
