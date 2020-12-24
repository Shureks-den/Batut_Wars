#pragma once

#include "Engine.h"

namespace space {

class Planet : public engine::ImmoveAble {
 public:
  explicit Planet(float range);
  ~Planet() = default;
  virtual void collision(engine::MoveAble &moveable) override;
  virtual void trigger(engine::MoveAble &moveable) = 0;

  float get_range();
  virtual void update(sf::Time dt) = 0;

  virtual animation::Id get_animation_id() const = 0;

 protected:
  const float _range;
};

}  // namespace space
