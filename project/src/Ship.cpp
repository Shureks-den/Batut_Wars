#include "Ship.h"

#include <iostream>

namespace space {

Ship::Ship(const sf::Time recharge)
    : engine::MoveAble(35, 150), _recharge(recharge), _countdown(_recharge) {
  set_size(sf::Vector2f(50.0f, 64.0f));
}

void Ship::collision(engine::MoveAble &other) {
  float critical_radius = 24 * 2;
  engine::Vector tmp(other.get_x() - this->get_x(),
                     other.get_y() - this->get_y());
  float radius = tmp.get_abs();

  if (radius > critical_radius) {
    return;
  }

  this->set_hp(this->get_hp() - 20);
  other.set_hp(other.get_hp() - 20);
  std::cout << "HP: " << this->get_hp() << std::endl;

  engine::Vector V10 = this->get_engine_speed();
  engine::Vector V20 = other.get_engine_speed();

  int a = V10.get_x() + V20.get_x();
  int b = V10.get_y() + V20.get_y();
  int c = V10.get_x() * V10.get_x() + V20.get_x() * V20.get_x();
  int d = V10.get_y() * V10.get_y() + V20.get_y() * V20.get_y();

  int V1x = (a + sqrt(2 * c - a * a)) / 2;
  int V2x = (a - sqrt(2 * c - a * a)) / 2;
  int V1y = (b + sqrt(2 * d - b * b)) / 2;
  int V2y = (b - sqrt(2 * d - b * b)) / 2;

  this->set_engine_speed(engine::Vector(V2x, V2y));

  other.set_engine_speed(engine::Vector(V1x, V1y));
}

void Ship::trigger(MoveAble &) {}

}  // namespace space
