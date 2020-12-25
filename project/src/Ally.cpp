#include "Ally.h"

namespace space {

Ally::Ally() : space::Ship(sf::seconds(1.0f), 20) {
    _HP = 100;
    _engine_thrust = 40;
    _speed_limit = 175;
    set_size(sf::Vector2f(42.0f, 50.0f));
    _state.resize(4);
    _state[1] = true;
}

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

  _state[0] = false;  // Бабах от выстрела
  if (_HP > 66) {
    _state[1] = true;
    _state[2] = false;
    _state[3] = false;
  } else if (_HP > 33) {
    _state[1] = false;
    _state[2] = true;
    _state[3] = false;
  } else {
    _state[1] = false;
    _state[2] = false;
    _state[3] = true;
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
  bullet->set_position(_position + _orientation.get_sf() * (_size.y * 0.8f + bullet->get_size().x));
  bullet->rotate(get_angle());

  _state[0] = true;
  return bullet;
}

void Ally::trigger(engine::MoveAble &) {}

// problems with id?
animation::Id Ally::get_animation_id() const {
    return animation::Id::MF;
}

}  // namespace space
