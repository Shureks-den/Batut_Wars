#pragma once

#include "Engine.h"

namespace space {

class Comet : public engine::MoveAble {
 public:
  Comet(engine::Vector speed);
  ~Comet() = default;

  void collision(engine::MoveAble &moveable) override;
  void virtual trigger(engine::MoveAble &moveable) override;

  void update(sf::Time dt) override;

  animation::Id get_animation_id() const override;

 private:
};

}  // namespace space