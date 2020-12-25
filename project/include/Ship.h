#pragma once

#include <SFML/System/Time.hpp>
#include <memory>

#include "Bullet.h"
#include "Engine.h"

#define SHIPE_WIDTH 48

namespace space {

class Ship : public engine::MoveAble {
 public:
  Ship(const sf::Time, int dmg);
  ~Ship() = default;

  virtual std::unique_ptr<Bullet> fire() = 0;

  virtual void trigger(engine::MoveAble &moveable) = 0;

  void collision(engine::MoveAble &other) override;

 protected:
  const sf::Time _recharge;  // Перезарядка между выстрелами
  sf::Time _countdown;  // Текущий кд
};

}  // end namespace space
