#pragma once

#include <SFML/System/Time.hpp>
#include <memory>

#include "Bullet.h"
#include "Engine.h"

#define SHIPE_WIDTH 48

namespace space {

class Ship : public engine::MoveAble {
 public:
  Ship();
  ~Ship() = default;

  void update(sf::Time dt) override;
  animation::Id get_animation_id() const override;
  std::unique_ptr<Bullet> fire();
  void collision(engine::MoveAble &MoveAble) override;

  void virtual trigger(engine::MoveAble &moveable) override;

 private:
  const sf::Time _recharge;  // Перезарядка между выстрелами
  sf::Time _countdown;  // Текущий кд
};

}  // end namespace space
