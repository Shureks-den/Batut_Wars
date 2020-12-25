#include "IcePlanet.h"

namespace space {

IcePlanet::IcePlanet(float range) : space::Planet(range) {
  _state.resize(1);
}

void IcePlanet::collision(space::Bullet& bullet) {
  if(bullet.is_destroyed()) {
    return;
  }
  auto other_size = bullet.get_size();
  auto other_radius = sqrt(other_size.x * other_size.x + other_size.y * other_size.y) / 2.f;
  float critical_radius = _range + other_radius;

  engine::Vector radius(-bullet.get_x() + get_x(), -bullet.get_y() + get_y());

  if (radius.get_abs() >= critical_radius) {
    return;
  }

  float angle = radius.compute_angle(bullet.get_orientation());  // rad

  if (radius.get_x() * bullet.get_orientation().get_y() >
      radius.get_y() * bullet.get_orientation().get_x()) {
    bullet.rotate((PI / 2 - angle) * 2);
  } else {
    bullet.rotate(-(PI / 2 - angle) * 2);
  }

  _state[0] = true;  // Дзынь
}

animation::Id IcePlanet::get_animation_id() const {
  return animation::Id::ICE_PLANET;
}

void IcePlanet::trigger(engine::MoveAble&) {}

void IcePlanet::update(sf::Time) {
    _state[0] = false;
}

}  // namespace space