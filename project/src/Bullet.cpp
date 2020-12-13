#include "Bullet.h"

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

animation::Id Bullet::get_animation_id() {
    return animation::Id::BULLET;
} 

float Bullet::getMaxSpeed() const {
    return _maxSpeed;
}

int Bullet::getDamage() const {
    return _dmg;
}

void Bullet::collusion(Entity &object) {
    if (this->get_x() + this->get_size().x <= object.get_x() + object.get_size().x / 2 ||
        this->get_x() - this->get_size().x >= object.get_x() - object.get_size().x / 2 ||
        this->get_y() + this->get_size().y <= object.get_y() + object.get_size().y / 2 ||
        this->get_y() - this->get_size().y >= object.get_y() - object.get_size().y / 2 ) {
            std::cout << "BOOOOOM" << std::endl;
    }
}