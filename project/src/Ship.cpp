#include "Ship.h"

#include <iostream>

namespace space {

Ship::Ship() : engine::MoveAble(35, 150),
               _recharge(sf::seconds(3)),
               _countdown(_recharge) {
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

    if (_countdown > sf::Time::Zero) {
        _countdown -= (_countdown > dt) ? dt : _countdown;
    }

    std::cout << "RAD: " << get_angle() << " DEG: " << engine::as_degree(get_angle()) << " OR_ABS: " << _orientation.get_abs() << std::endl;
}

std::unique_ptr<Bullet> Ship::fire() {
    if (_countdown != sf::Time::Zero) {
        return nullptr;
    }

    _countdown = _recharge;

    auto bullet = std::make_unique<Bullet>();
    bullet->set_position(_position);
    bullet->rotate(get_angle());
    return bullet;
}

animation::Id Ship::get_animation_id() const {
    return animation::Id::SHIP;
}

}  // namespace space
