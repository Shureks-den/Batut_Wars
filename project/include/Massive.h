#pragma once

#include "Planet.h"

namespace space {

class Massive : public space::Planet {
 public:
  Massive(int mass, float range);
  ~Massive() = default;
  virtual void trigger(engine::MoveAble &moveable) override;
  float get_zone();

  engine::Vector gravitate(sf::Vector2f position);

  animation::Id get_animation_id() const override;
  void update(sf::Time dt) override;

 protected:
  const int _mass;
};

}  // namespace space
