#include "ship.h"

#include <iostream>

namespace space {

void Ship::update(sf::Time dt) {
    _speed += _acceleration * dt.asSeconds();
    if (_speed.get_abs() >= SPEED_LIMIT) {
        _speed = _speed.get_normal() * SPEED_LIMIT;;
    }

    engine::Vector tmp = _speed * dt.asSeconds();
    _position += tmp.get_sf();
}

} // namespace space
