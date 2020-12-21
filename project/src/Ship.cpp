#include "Ship.h"

#include <iostream>

namespace space {

Ship::Ship() : engine::MoveAble(35, 150),
               _recharge(sf::seconds(1.5f)),
               _countdown(_recharge) {
    set_size(sf::Vector2f(50.0f, 64.0f));
}

void Ship::update(sf::Time dt) {    
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

std::unique_ptr<Bullet> Ship::fire() {
    if (_countdown != sf::Time::Zero) {
        return nullptr;
    }

    _countdown = _recharge;

    auto bullet = std::make_unique<Bullet>();
    bullet->set_position(_position + _orientation.get_sf() * _size.y * 0.7f);
    bullet->rotate(get_angle());
    return bullet;
}

animation::Id Ship::get_animation_id() const {
    return animation::Id::SHIP;
}

void Ship::collision(engine::MoveAble &) {}

void Ship::trigger(MoveAble &) {}

}  // namespace space
