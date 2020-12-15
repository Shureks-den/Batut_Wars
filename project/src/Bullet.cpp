#include "Bullet.h"
#include <iostream>

namespace space {

Bullet::Bullet() : engine::MoveAble(0, 350) {
    _engine_speed = _orientation * 200;
}

void Bullet::update(sf::Time dt) {
    _engine_speed += _engine_acceleration * dt.asSeconds();
    _dictated_speed += _dictated_acceleration * dt.asSeconds();

    if (_engine_speed.get_abs() >= _speed_limit) {
        _engine_speed = _engine_speed.get_normal() * _speed_limit;
    }

    if (_dictated_acceleration.get_abs() == 0) {
        _dictated_speed /= 1.1;
    }
    
    engine::Vector total_speed = _engine_speed + _dictated_speed;

    engine::Vector tmp = total_speed * dt.asSeconds();
    _position += tmp.get_sf();
    _dictated_acceleration.set_x(0);
    _dictated_acceleration.set_y(0);
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