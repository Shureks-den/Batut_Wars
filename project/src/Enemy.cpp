#include "Enemy.h"

namespace space {

Enemy::Enemy() : engine::MoveAble(60, 70),
               _is_player_spotted(false),
               _recharge(sf::seconds(3.0f)),
               _countdown(_recharge),
               _rotate_time(sf::seconds(2)),
               _vision(500,500),
               _rotate_speed(0.05f),
               _aimed(false) {
    set_size(sf::Vector2f(50.0f, 64.0f));
}

void Enemy::update(sf::Time dt) {
     if (_is_destroyed) {
        return;
    }
    if(!_is_player_spotted) {    // афк действия, если игрока нет рядом, просто двигается, крутится
        _aimed = false;
        if (_rotate_time > sf::seconds(1) && _rotate_time < sf::seconds(7)) {   // простое перемещение запустите прочекайте
            give_acceleration(Direction::FORWARD);
        }
        if (_rotate_time > sf::seconds(9)) {
            rotate(engine::as_radian(90.0) * dt.asSeconds());
        }
        if(_rotate_time == sf::Time::Zero) {
            _rotate_time = sf::seconds(10);
        }
    }

    if (_is_player_spotted) {    // TODO(anyone) сделать изящное торможение и/или другое перемещение 
        give_acceleration(Direction::FORWARD);  
        turn_to_player();   
    }
    
    _engine_speed += _engine_acceleration * dt.asSeconds();
    _dictated_speed += _dictated_acceleration * dt.asSeconds();

    if (_engine_speed.get_abs() >= _speed_limit) {
        _engine_speed = _engine_speed.get_normal() * _speed_limit;
    }

    if (_dictated_speed.get_abs() > 0) {
        _dictated_speed *= (1 - dt.asSeconds());
    } else {
        _dictated_speed = engine::Vector(0, 0);
    }
    
    engine::Vector total_speed = _engine_speed + _dictated_speed;

    engine::Vector tmp = total_speed * dt.asSeconds();
    _position += tmp.get_sf();
    _dictated_acceleration.set_x(0);
    _dictated_acceleration.set_y(0);
    _engine_acceleration.set_x(0);
    _engine_acceleration.set_y(0);

    if (_countdown > sf::Time::Zero) {
        _countdown -= (_countdown > dt) ? dt : _countdown;
    }
    if (_rotate_time > sf::Time::Zero) {
        _rotate_time -= (_rotate_time > dt) ? dt : _rotate_time;
    }
}

std::unique_ptr<Bullet> Enemy::fire() {
    if (_countdown != sf::Time::Zero || _aimed == false || _is_destroyed) {
        return nullptr;
    }

    _countdown = _recharge;

    auto bullet = std::make_unique<Bullet>();
    bullet->set_position(_position + _orientation.get_sf() * _size.x);
    bullet->rotate(get_angle());
    return bullet;
}

animation::Id Enemy::get_animation_id() const {
    return animation::Id::SHIP;
}

void Enemy::trigger(engine::MoveAble &moveable) {
    if (_is_destroyed) {
        return;
    }
    if (moveable.is_destroyed()) {
        _is_player_spotted = false;
        return;
    }
 
    if(moveable.get_position().x >= this-> get_position().x - _vision.x &&
     moveable.get_position().x <= this->get_position().x + _vision.x &&
     moveable.get_position().y >= this->get_position().y - _vision.y &&
     moveable.get_position().y <= this->get_position().y + _vision.y) {
        _is_player_spotted = true;
        _player_location = moveable.get_position();
    } else {
        _is_player_spotted = false;
    }
}

void Enemy::turn_to_player() {  // проверить работоспособность точно запихнуть в update
    engine::Vector new_orientaion(_player_location.x - this->get_position().x, 
        _player_location.y - this->get_position().y);

    float rotate_angle = acos((new_orientaion.get_x() * this->get_orientation().get_x() + new_orientaion.get_y() * 
    this->get_orientation().get_y())/(new_orientaion.get_abs() * this->get_orientation().get_abs()));
    if (new_orientaion.get_y() * get_orientation().get_x() < get_orientation().get_y() * new_orientaion.get_x()) {
        rotate_angle *= -1;
    }
    if (fabs(rotate_angle) > 0.05) {
        _aimed = false;
        if (rotate_angle > 0) {
            rotate(_rotate_speed);
        } else {
            rotate(-_rotate_speed);
        }
    } else {
        _aimed = true;   // буп-бип цель захвачена, пли
    }
}

void Enemy::collision(engine::MoveAble &) {}

}  // namespace space