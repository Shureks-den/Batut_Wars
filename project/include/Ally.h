#pragma once

#include "Ship.h"

namespace space {

class Ally : public space::Ship {
 public:
  Ally();
  ~Ally() = default;

  void update(sf::Time dt) override;
  animation::Id get_animation_id() const override;

  void virtual trigger(engine::MoveAble &moveable) override;  // if needed

  std::unique_ptr<Bullet> fire() override;

 private:
};

}  // end namespace space
