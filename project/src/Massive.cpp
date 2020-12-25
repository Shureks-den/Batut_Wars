#include "Massive.h"

#include "Ally.h"

namespace space {

Massive::Massive(int mass, float range) : space::Planet(range), _mass(mass) {}

void Massive::trigger(engine::MoveAble &moveable) {
  if (moveable.is_destroyed()) {
    return;
  }

  engine::Vector tmp(moveable.get_x() - this->get_x(),
                     moveable.get_y() - this->get_y());
  float radius = tmp.get_abs();
  if (radius < this->get_zone()) {
    moveable.give_acceleration(gravitate(moveable.get_position()));
  }
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

float Massive::get_zone() { return _range * (_mass * 0.03); }

}  // namespace space
