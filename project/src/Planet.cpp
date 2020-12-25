#include "Planet.h"

#ifndef NO_CONSOLE_INFO_OF_DMG
#include <iostream>
#endif  // NO_CONSOLE_INFO_OF_DMG

namespace space {

Planet::Planet(float range) : _range(range) {}

float Planet::get_range() { return _range; }

void Planet::collision(engine::MoveAble &moveable) {
  auto other_size = moveable.get_size();
  auto other_radius = sqrt(other_size.x * other_size.x + other_size.y * other_size.y) / 2.f;
  float critical_radius = _range + other_radius;
  engine::Vector tmp(moveable.get_x() - this->get_x(),
                     moveable.get_y() - this->get_y());
  float radius = tmp.get_abs();
  if (radius <= critical_radius) {
    moveable.take_damage(moveable.get_hp());

#ifndef NO_CONSOLE_INFO_OF_DMG
// std::cout << moveable.get_hp() << " - Planet - " << std::endl; // уж очень
// часто выводит, почти бесполезно
#endif  // NO_CONSOLE_INFO_OF_DMG
  }
}

}  // namespace space
