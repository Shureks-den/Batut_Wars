#include "Enemy.h"

namespace space {

Enemy::Enemy()
    : space::Ship(sf::seconds(3.0f), 10),
      _is_going_to_planet(false),
      _is_player_spotted(false),
      _aimed(false),
      _close_to_enemy_ship(false),
      _recharge(sf::seconds(3.0f)),
      _countdown(_recharge),
      _rotate_time(sf::seconds(2)),
      _vision(500,500),
      _rotate_speed(0.05f) {
  set_size(sf::Vector2f(32.0f, 46.0f));
  _engine_thrust = 50;
  _speed_limit = 100;
  _HP = 50;
  _state.resize(1);
}

void Enemy::update(sf::Time dt) {
     if (_is_destroyed) {
        return;
    }
    if(!_is_player_spotted) {    // афк действия, если игрока нет рядом, просто двигается, крутится
        _aimed = false;
        if (_is_going_to_planet) {
            turn_from_planet();
            give_acceleration(Direction::FORWARD);
        } else if (_close_to_enemy_ship) {
            turn_from_enemy();
            give_acceleration(Direction::FORWARD);
        } else {
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
    _is_going_to_planet = false;
    _is_player_spotted = false;
    _close_to_enemy_ship = false;

    _state[0] = false;
}

std::unique_ptr<Bullet> Enemy::fire() {
  if (_is_destroyed) {
    return nullptr;
  }

  if (_countdown != sf::Time::Zero) {
    return nullptr;
  }

  if (!_aimed) {
    return nullptr;
  }

  _countdown = _recharge;

  auto bullet = std::make_unique<Bullet>();
  bullet->set_position(_position + _orientation.get_sf() * (_size.y * 0.6f + bullet->get_size().x));
  bullet->rotate(get_angle());

  _state[0] = true;  // Бабах
  return bullet;
}

animation::Id Enemy::get_animation_id() const { return animation::Id::MAUL; }

void Enemy::trigger(engine::MoveAble &moveable) {
    if (_is_destroyed) {
        return;
    }

    if (moveable.is_destroyed()) {  // тут был исправлен баг в онлайне
        return;
    }
 
    if (moveable.get_position().x >= _position.x - _vision.x &&
        moveable.get_position().x <= _position.x + _vision.x &&
        moveable.get_position().y >= _position.y - _vision.y &&
        moveable.get_position().y <= _position.y + _vision.y) {
          _is_player_spotted = true;
          _player_location = moveable.get_position();
    } else {
        return;
    }
}

void Enemy::trigger(engine::ImmoveAble &immoveable) {
    engine::Vector dist (immoveable.get_position().x - this->_position.x, immoveable.get_position().y - this->_position.y);
    if (dist.get_abs() <= 300) {
        _planet_location.x = immoveable.get_position().x;
        _planet_location.y = immoveable.get_position().y;
        _is_going_to_planet = true;
    } else {
        return;
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

void Enemy::turn_from_planet() {
    engine::Vector new_orientaion(_position.x - _planet_location.x, _position.y - _planet_location.y);

    float rotate_angle = acos((new_orientaion.get_x() * this->get_orientation().get_x() + new_orientaion.get_y() * 
    this->get_orientation().get_y())/(new_orientaion.get_abs() * this->get_orientation().get_abs()));
    if (new_orientaion.get_y() * get_orientation().get_x() < get_orientation().get_y() * new_orientaion.get_x()) {
        rotate_angle *= -1;
    }
    if (fabs(rotate_angle) < PI) {
        if (rotate_angle > 0) {
            rotate(_rotate_speed);
        } else {
            rotate(-_rotate_speed);
        }
    }
}

void Enemy::trigger(Enemy &enemy) {
     if (_is_destroyed) {
        return;
    }

    if (enemy.is_destroyed()) {  // тут был исправлен баг в онлайне
        return;
    }
 
    engine::Vector dist (enemy.get_position().x - this->_position.x,enemy.get_position().y - this->_position.y);
    if (dist.get_abs() <= 120) {
        _enemy_location.x = enemy.get_position().x;
        _enemy_location.y = enemy.get_position().y;
        _close_to_enemy_ship = true;
    } else {
        return;
    }
}


void Enemy::turn_from_enemy() {
    engine::Vector new_orientaion(this->get_position().x - _enemy_location.x, 
          this->get_position().y - _enemy_location.y);

    float rotate_angle = acos((new_orientaion.get_x() * this->get_orientation().get_x() + new_orientaion.get_y() * 
    this->get_orientation().get_y())/(new_orientaion.get_abs() * this->get_orientation().get_abs()));
    if (new_orientaion.get_y() * get_orientation().get_x() < get_orientation().get_y() * new_orientaion.get_x()) {
        rotate_angle *= -1;
    }

    if (fabs(rotate_angle) < PI) {
        if (rotate_angle > 0) {
            rotate(_rotate_speed);
        } else {
            rotate(-_rotate_speed);
        }
    }
}

}  // namespace space