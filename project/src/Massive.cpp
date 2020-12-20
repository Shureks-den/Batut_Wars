#include "Massive.h"
#include "Engine.h"
#include "Ship.h"
#include <iostream>

namespace space {

Massive::Massive(int mass, float range) : _mass(mass), _range(range) {}

void Massive::collision(engine::MoveAble &) {
    // float critical_radius = this->_range + 12;
    // engine::Vector tmp(moveable.get_x() - this->get_x(), moveable.get_y() - this->get_y()); 
    // float radius = tmp.get_abs();
    // if (radius <= critical_radius) {
    //     moveable.set_hp(0);
    //     moveable.set_is_destroyed(true);
    //     exit(0);
    // }
}


void Massive::trigger(engine::MoveAble &moveable) {
    engine::Vector tmp(moveable.get_x() - this->get_x(), moveable.get_y() - this->get_y()); 
    float radius = tmp.get_abs();
    if (radius < this->get_zone()) {
        moveable.give_acceleration(gravitate(moveable.get_position()));
    }
}

float Massive::get_range() {
    return _range;
}

engine::Vector Massive::gravitate(sf::Vector2f position) {
    engine::Vector tmp(this->get_x() - position.x, this->get_y() - position.y);

    float radius = tmp.get_abs();
    float current_component_a = G * _mass / (radius * radius);

    tmp.get_normal();
    tmp *= current_component_a;

    return tmp;
}

animation::Id Massive::get_animation_id() const {
    return animation::Id::BLACKHOLE;
}

void Massive::update(sf::Time) {}

float Massive::get_zone() {
    return _range * (_mass * 0.03);
}

} // namespace space
