#include "Ship.h"

namespace space {

Ship::Ship() : engine::MoveAble(50, 100) {
    this->set_size(sf::Vector2f(50.0f, 50.0f));
}

void Ship::update(sf::Time dt) {
    _speed += _acceleration * dt.asSeconds();
    if (_speed.get_abs() >= _speed_limit) {
        _speed = _speed.get_normal() * _speed_limit;;
    }

    engine::Vector tmp = _speed * dt.asSeconds();
    _position += tmp.get_sf();
    _acceleration.set_x(0);
    _acceleration.set_y(0);
}

std::unique_ptr<Bullet> Ship::fire() {
    auto bullet = std::unique_ptr<Bullet>(new Bullet);
    bullet->set_position(_position);
    return bullet;
}

animation::Id Ship::get_animation_id() const {
    return animation::Id::SHIP;
}

}  // namespace space
