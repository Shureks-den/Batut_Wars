#include "Bullet.h"

#ifndef NO_CONSOLE_INFO_OF_DMG
#include <iostream>
#endif  // NO_CONSOLE_INFO_OF_DMG

namespace space {

Bullet::Bullet() : engine::MoveAble(0, 350, 15), _lifetime(sf::seconds(10)) {
  _engine_speed = _orientation * 350;
  _current = sf::Time::Zero;
  set_size(sf::Vector2f(7.5, 7.5));
}

void Bullet::update(sf::Time dt) {
  if (_is_destroyed) {
    return;
  }

  _current += dt;
  _is_destroyed = (_current >= _lifetime);
  if (_is_destroyed) {
    return;
  }

  _engine_speed += _engine_acceleration * dt.asSeconds();
  _dictated_speed += _dictated_acceleration * dt.asSeconds();

  if (_engine_speed.get_abs() >= _speed_limit) {
    _engine_speed = _engine_speed.get_normal() * _speed_limit;
  }

  if (_dictated_acceleration.get_abs() == 0) {
    _dictated_speed /= 1.1;
  }

  engine::Vector total_speed = _engine_speed + _dictated_speed;

  engine::Vector tmp = total_speed * dt.asSeconds();
  _position += tmp.get_sf();
  _dictated_acceleration.set_x(0);
  _dictated_acceleration.set_y(0);
  _engine_acceleration.set_x(0);
  _engine_acceleration.set_y(0);
}

animation::Id Bullet::get_animation_id() const { return animation::Id::BULLET; }

int Bullet::get_damage() const { return _dmg; }

void Bullet::collision(engine::MoveAble &object) {
  if (_is_destroyed) {
    return;
  }

  if (object.is_destroyed()) {
    return;
  }

  auto other_size = object.get_size();
  auto other_radius = sqrt(other_size.x * other_size.x + other_size.y * other_size.y) / 2.f;
  auto this_radius = _size.x / 2.f;

  float critical_radius = this_radius + other_radius;
  engine::Vector tmp(object.get_x() - _position.x,
                     object.get_y() - _position.y);
  float radius = tmp.get_abs();

  if (critical_radius > radius) {
    take_damage(_HP);
    object.take_damage(_dmg);

#ifndef NO_CONSOLE_INFO_OF_DMG
    std::cout << object.get_hp() << " - Bullet - " << this->get_hp()
              << std::endl;
#endif  // NO_CONSOLE_INFO_OF_DMG
  }
}

void Bullet::trigger(MoveAble &) {}

}  // namespace space
