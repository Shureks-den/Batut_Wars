#include "Enemy.h"

#include <iostream>

namespace space {

Enemy::Enemy() : engine::MoveAble(35, 150),
               _recharge(sf::seconds(1.5f)),
               _countdown(_recharge),
               _vision(100,100),
               _rotate_speed(1.f) {
    this->set_size(sf::Vector2f(50.0f, 50.0f));
}

void Enemy::update(sf::Time dt) {
    if(spot_player && _speed.get_x() != 0 && _speed.get_y() != 0) {
        _speed -= _acceleration * dt.asSeconds();
    }
    
    engine::Vector tmp = _speed * dt.asSeconds();
    _position += tmp.get_sf();
    _acceleration.set_x(0);
    _acceleration.set_y(0);

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
    bullet->set_position(_position + _orientation.get_sf() * _size.x * 0.5f);
    bullet->rotate(get_angle());
    return bullet;
}

animation::Id Enemy::get_animation_id() const {
    return animation::Id::SHIP;
}

bool Enemy::spot_player(Ship *player_ship) {
    if(player_ship->get_position().x >= this-> get_position().x - _vision.x &&
    player_ship->get_position().x <= this->get_position().x + _vision.x &&
    player_ship->get_position().y >= this->get_position().y - _vision.y &&
    player_ship->get_position().y <= this->get_position().y + _vision.y) {   // если корабль игрока в квадрате видимости
        
        return true;
    }
    return false;
}

void Enemy::turn_to_player(Ship *player_ship) {  // проверить работоспособность точно запихнуть в update
    if (this->spot_player(player_ship)) {
        sf::Vector2f new_orientaion(player_ship->get_position().x - this->get_position().x, 
            player_ship->get_position().y - this->get_position().y);
            float norm_orientation = sqrt(pow(new_orientaion.x,2), pow(new_orientaion.y, 2));

        float rotate_angle = acos((new_orientaion.x * this->get_orientation().x + new_orientaion.y + 
        this->get_orientation().y)/(norm_orientation * this->get_abs(this->get_orientation()))));
        while (this->get_angle != rotate_angle) {
            this->angle += _rotate_speed;
        }
    }
}

void Enemy::move() {
    if(!this->spot_player() && _countdown == sf::Time::Zero) {
        _speed = _speed_limit / 3;
        rotate(90);
    }
}

}  // namespace space