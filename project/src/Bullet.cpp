#include "Bullet.h"
#include <iostream>

namespace space {

Bullet::Bullet() : engine::MoveAble(0,200) {
    _speed = _orientation * 200;
}

void Bullet::update(sf::Time dt) {
     _speed += _acceleration * dt.asSeconds();
    if (_speed.get_abs() >= _maxSpeed) {
      _speed = _speed.get_normal() * _speed_limit;;
    }

    engine::Vector tmp = _speed * dt.asSeconds();
    _position += tmp.get_sf();
    _acceleration.set_x(0);
    _acceleration.set_y(0);
}

animation::Id Bullet::get_animation_id() const {
    return animation::Id::BULLET;
} 

float Bullet::getMaxSpeed() const {
    return _maxSpeed;
}

int Bullet::getDamage() const {
    return _dmg;
}

void Bullet::collision(engine::MoveAble &object) {
    sf::Vector2f size = object.get_size();
    if (_position.x <= object.get_x() + size.x / 2 &&
        _position.x >= object.get_x() - size.x / 2 &&
        _position.y <= object.get_y() + size.y / 2 &&
        _position.y >= object.get_y() - size.y / 2 ) {
        std::cout << "BOOOOOM" << std::endl;
    }
}

}  //namespace space