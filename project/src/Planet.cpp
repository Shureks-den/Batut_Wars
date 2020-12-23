#include "Planet.h"

#include "Ally.h"

namespace space {

Planet::Planet(float range) : _range(range) {}

float Planet::get_range() { return _range; }

void Planet::collision(engine::MoveAble &moveable) {
  float critical_radius = this->_range + 12;
  engine::Vector tmp(moveable.get_x() - this->get_x(),
                     moveable.get_y() - this->get_y());
  float radius = tmp.get_abs();
  if (radius <= critical_radius) {
    moveable.set_hp(0);
    moveable.set_is_destroyed(true);
  }
}

}  // namespace space
