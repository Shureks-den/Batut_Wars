#pragma once

#include "Animation.h"

namespace animation {

class Maul : public Manager {
 public:
  Maul(const sf::Texture *texture, sf::Vector2f position = sf::Vector2f(0, 0), float angle = 0);
  ~Maul() = default;
  void virtual update(sf::Time d_time);
};

}  // namespace animation