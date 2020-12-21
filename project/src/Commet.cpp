#include "Commet.h"

#include <iostream>

namespace space {
Commet::Commet(engine::Vector speed) : engine::MoveAble(0) {
  _engine_speed = speed;
}
void Commet::collision(engine::MoveAble& moveable) {
  float critical_radius = 12 + 7;
  engine::Vector tmp(moveable.get_x() - this->get_x(),
                     moveable.get_y() - this->get_y());
  float radius = tmp.get_abs();
  if (radius <= critical_radius) {
    moveable.set_hp(moveable.get_hp() - COMMET_DAMAGE);
    moveable.set_is_destroyed(true);
    std::cout << "mini BOOOM n TRASH";
    exit(0);
  }
}
}  // namespace space
   // красава :)