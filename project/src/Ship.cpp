#include "Ship.h"

namespace space {

Ship::Ship() : engine::MoveAble(50, 100), _HP(100) {}

void Ship::update(sf::Time dt) {    
    _engine_speed += _engine_acceleration * dt.asSeconds();
    _dictated_speed += _dictated_acceleration * dt.asSeconds();

    if (_engine_speed.get_abs() >= _speed_limit) {
        _engine_speed = _engine_speed.get_normal() * _speed_limit;
    }

    if (_dictated_acceleration.get_abs() == 0) {
        _dictated_speed /= 2;
    }
    
    engine::Vector total_speed = _engine_speed + _dictated_speed;

    engine::Vector tmp = total_speed * dt.asSeconds();
    _position += tmp.get_sf();
    _engine_acceleration.set_x(0);
    _engine_acceleration.set_y(0);
    _dictated_acceleration.set_x(0);
    _dictated_acceleration.set_y(0);
}

animation::Id Ship::get_animation_id() const {
    return animation::Id::SHIP;
}

}  // namespace space
