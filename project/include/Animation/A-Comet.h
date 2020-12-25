#pragma once

#include "Animation.h"

namespace animation {

class Comet : public Manager {
 public:
  Comet(const sf::Texture *texture, sf::Vector2f position = sf::Vector2f(0, 0),
        float angle = 0);
  ~Comet() = default;
  void virtual update(sf::Time d_time);
};

}  // namespace animation