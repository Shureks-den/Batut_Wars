#include "Comet.h"
#ifndef NO_CONSOLE_INFO_OF_DMG
#include <iostream>
#endif  // NO_CONSOLE_INFO_OF_DMG

namespace space {

Comet::Comet(engine::Vector speed)
    : engine::MoveAble(0.f, 40) {  // TODO(anyone) переписать конструктор на
  _engine_speed = speed;  // модуль скорости + угол (с осью ОХ)
  _orientation = _engine_speed.get_normal();
  set_size(sf::Vector2f(20, 20));
}

void Comet::collision(engine::MoveAble& moveable) {
  if (_is_destroyed) {
    return;
  }

  if (moveable.is_destroyed()) {
    return;
  }

    auto other_size = moveable.get_size();
    auto other_radius = sqrt(other_size.x * other_size.x + other_size.y * other_size.y) / 2.f;
    float critical_radius = _size.y  / 2.f + other_radius;
    engine::Vector tmp(moveable.get_x() - _position.x, moveable.get_y() - _position.y);

    float radius = tmp.get_abs();
    if (radius <= critical_radius) {
      moveable.take_damage(_dmg);

#ifndef NO_CONSOLE_INFO_OF_DMG
      std::cout << moveable.get_hp() << " - Comet - " << this->get_hp()
                << std::endl;
#endif  // NO_CONSOLE_INFO_OF_DMG
    }
}

animation::Id Comet::get_animation_id() const { return animation::Id::COMET; }

void Comet::trigger(engine::MoveAble&) {}

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
   // красава :)   Вообще-то это Антон мне(Лизе) написал :(
   // спасибо (:
   // выходи за меня :)
   // я согласен
