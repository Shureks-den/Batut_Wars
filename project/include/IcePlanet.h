#pragma once

#include "Bullet.h"
#include "Planet.h"

namespace space {

class IcePlanet : public space::Planet {
 public:
  explicit IcePlanet(float range);
  ~IcePlanet() = default;
  void collision(space::Bullet& bullet);
  virtual void trigger(engine::MoveAble& moveable) override;

  animation::Id get_animation_id() const override;
  void update(sf::Time dt) override;
};

}  // namespace space