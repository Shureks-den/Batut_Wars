#include "ship.h"

namespace space {

void Ship::update(sf::Time dt) {
    engine::Vector tmp = _speed * dt.asSeconds() + _acceleration * dt.asSeconds() * dt.asSeconds() / 2;
    _position += tmp.get_sf();
    _speed += _acceleration * dt.asSeconds();

    if (_speed.get_abs() >= SPEED_LIMIT) {
        _speed = _speed.get_normal() * SPEED_LIMIT;
    }
}

} // namespace space
