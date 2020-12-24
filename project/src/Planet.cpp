#include "Planet.h"

#ifndef NO_CONSOLE_INFO_OF_DMG
#include <iostream>
#endif  // NO_CONSOLE_INFO_OF_DMG

namespace space {

Planet::Planet(float range) : _range(range) {}

float Planet::get_range() { return _range; }

void Planet::collision(engine::MoveAble &moveable) {
  float critical_radius = this->_range + 12;
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
