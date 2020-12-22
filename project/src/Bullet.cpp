#include "Bullet.h"

namespace space {

Bullet::Bullet() : engine::MoveAble(0, 350), _lifetime(sf::seconds(10)) {
  _engine_speed = _orientation * 350;
  _current = sf::Time::Zero;
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

  sf::Vector2f size = object.get_size();
  if (_position.x <= object.get_x() + size.x / 2 &&
      _position.x >= object.get_x() - size.x / 2 &&
      _position.y <= object.get_y() + size.y / 2 &&
      _position.y >= object.get_y() - size.y / 2) {
      _is_destroyed = true;
  }
}

void Bullet::trigger(MoveAble &) {}

}  // namespace space
