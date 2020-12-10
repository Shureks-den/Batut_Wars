#include "Massive.h"

namespace space {

Massive::Massive(int mass, float range) : _mass(mass), _range(range) {}

void Massive::collision(engine::MoveAble &moveable) {
    moveable.get_angle();  // TODOD(Tony) заглушка, реализовать
}

float Massive::get_range() {
    return _range;
}

engine::Vector Massive::gravitate(sf::Vector2f position){

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

void Massive::update(sf::Time dt) {
    dt.asSeconds();  // Заглушка. Не трогать
}

} // namespace space