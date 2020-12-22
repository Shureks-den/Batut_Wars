#include "Comet.h"

#include <iostream>

namespace space {

Comet::Comet(engine::Vector speed) : engine::MoveAble(0), _dmg(55) {  // TODO(anyone) переписать конструктор на
  _engine_speed = speed;                                              // модуль скорости + угол (с осью ОХ)
  _orientation = _engine_speed.get_normal();
}

void Comet::collision(engine::MoveAble& moveable) {
  float critical_radius = 20;
  engine::Vector tmp(moveable.get_x() - this->get_x(),
                     moveable.get_y() - this->get_y());
  float radius = tmp.get_abs();
  if (radius <= critical_radius) {
    moveable.set_hp(moveable.get_hp() - _dmg);
    moveable.set_is_destroyed(true);
    std::cout << "mini BOOOM n TRASH";
  }
}

animation::Id Comet::get_animation_id() const {
  return animation::Id::COMET;
}

void Comet::trigger(engine::MoveAble &) {}

void Comet::update(sf::Time dt) {
  _dictated_speed += _dictated_acceleration * dt.asSeconds();

  if (_dictated_speed.get_abs() > 0) {
    _dictated_speed *= (1 - dt.asSeconds());
  } else {
    _dictated_speed = engine::Vector(0, 0);
  }

  engine::Vector total_speed = _engine_speed + _dictated_speed;

  engine::Vector tmp = total_speed * dt.asSeconds();
  _position += tmp.get_sf();
  _dictated_acceleration.set_x(0);
  _dictated_acceleration.set_y(0);
}

}  // namespace space
   // красава :)
   // спасибо (: