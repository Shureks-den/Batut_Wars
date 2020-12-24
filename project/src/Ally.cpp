#include "Ally.h"

namespace space {

Ally::Ally() : space::Ship(sf::seconds(1.5f), 15) {}

void Ally::update(sf::Time dt) {
  if (_is_destroyed) {
    return;
  }

  _engine_speed += _engine_acceleration * dt.asSeconds();
  _dictated_speed += _dictated_acceleration * dt.asSeconds();

  if (_engine_speed.get_abs() >= _speed_limit) {
    _engine_speed = _engine_speed.get_normal() * _speed_limit;
  }

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
  _engine_acceleration.set_x(0);
  _engine_acceleration.set_y(0);

  if (_countdown > sf::Time::Zero) {
    _countdown -= (_countdown > dt) ? dt : _countdown;
  }
}

std::unique_ptr<Bullet> Ally::fire() {
  if (_is_destroyed) {
    return nullptr;
  }

  if (_countdown != sf::Time::Zero) {
    return nullptr;
  }

  _countdown = _recharge;

  auto bullet = std::make_unique<Bullet>();
  bullet->set_position(_position + _orientation.get_sf() * _size.y * 0.7f);
  bullet->rotate(get_angle());
  return bullet;
}

void Ally::trigger(engine::MoveAble &) {}

// problems with id?
animation::Id Ally::get_animation_id() const {
    return animation::Id::SHIP;
}

}  // namespace space
