#include "ship.h"

namespace space {

Ship::Ship() : engine::MoveAble(100){}  // TODO(Tony):

void Ship::update(sf::Time dt) {

    _speed += _acceleration * dt.asSeconds();
    if (_speed.get_abs() >= _speed_limit) {
        _speed = _speed.get_normal() * _speed_limit;
    }

    _position += (_speed * dt.asSeconds()).get_sf();

    _acceleration = engine::Vector(0, 0);
}

animation::Id Ship::get_animation_id() {
    return animation::Id::SHIP;
}

}  // namespace space
