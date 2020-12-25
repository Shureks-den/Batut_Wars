#pragma once

#include "Animation.h"

namespace animation {

class Explosion : public Manager {
 public:
  Explosion(const sf::Texture *texture,
            sf::Vector2f position = sf::Vector2f(0, 0), float angle = 0);
  ~Explosion() = default;
  void virtual update(sf::Time d_time);
};

}  // namespace animation
