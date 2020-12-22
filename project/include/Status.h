#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "Identificators.h"

class Status {
 public:
  Status() = default;
  ~Status() = default;

  size_t lay_id;
  size_t id;

  bool is_removed;
  animation::Id animation_id;

  float angle;
  sf::Vector2f position;

  std::vector<bool> states;
};
