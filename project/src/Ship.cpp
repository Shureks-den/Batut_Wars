#include "Ship.h"

#ifndef NO_CONSOLE_INFO_OF_DMG
#include <iostream>
#endif  // NO_CONSOLE_INFO_OF_DMG

namespace space {

Ship::Ship(const sf::Time recharge, int dmg)
    : engine::MoveAble(35, 150, dmg),
      _recharge(recharge),
      _countdown(_recharge) {
  set_size(sf::Vector2f(50.0f, 50.0f));
}

void Ship::collision(engine::MoveAble &other) {
  if (_is_destroyed || other.is_destroyed()) {
    return;
  }

  auto other_size = other.get_size();
  auto other_radius = sqrt(other_size.x * other_size.x + other_size.y * other_size.y) / 2.f;
  auto this_radius = sqrt(_size.x * _size.x + _size.y * _size.y) / 2.f;

  float critical_radius = this_radius + other_radius;
  engine::Vector tmp(other.get_x() - this->get_x(),
                     other.get_y() - this->get_y());
  float radius = tmp.get_abs();

  if (radius > critical_radius) {
    return;
  }

  // Just some physics
  engine::Vector V10 = (this->get_engine_speed() + this->get_dictated_speed());
  engine::Vector V20 = (other.get_engine_speed() + other.get_dictated_speed());

  float a = V10.get_x() + V20.get_x();
  float b = V10.get_y() + V20.get_y();
  float c = V10.get_x() * V10.get_x() + V20.get_x() * V20.get_x();
  float d = V10.get_y() * V10.get_y() + V20.get_y() * V20.get_y();

  this->take_damage(other.get_damage() *
                    (1 + fabs(sin((V10.get_abs() * V20.get_abs()) /
                                  (V10.get_abs() + V20.get_abs())))));
  other.take_damage(this->get_damage() *
                    (1 + fabs(sin((V10.get_abs() * V20.get_abs()) /
                                  (V10.get_abs() + V20.get_abs())))));

#ifndef NO_CONSOLE_INFO_OF_DMG
  std::cout << other.get_hp() << " - Ship - " << this->get_hp() << std::endl;
#endif  // NO_CONSOLE_INFO_OF_DMG

  // if (2 * c - a * a < 0 || 2 * d - b * b < 0) {
  //   std::cout << 2 * c - a * a << "\t" << 2 * d - b * b << std::endl;
  // }

  // float V1x = 0, V2x = 0, V1y = 0, V2y = 0;
  // if (2 * c - a * a >= 0) {
  //   V1x = (a + sqrt(2 * c - a * a)) / 2;
  //   V2x = (a - sqrt(2 * c - a * a)) / 2;
  // }
  // if (2 * d - b * b >= 0) {
  //   V1y = (b + sqrt(2 * d - b * b)) / 2;
  //   V2y = (b - sqrt(2 * d - b * b)) / 2;
  // }

  float V1y = (b + sqrt(fabs(2 * d - b * b))) / 2;
  float V2y = (b - sqrt(fabs(2 * d - b * b))) / 2;
  float V1x = (a + sqrt(fabs(2 * c - a * a))) / 2;
  float V2x = (a - sqrt(fabs(2 * c - a * a))) / 2;

  // std::cout << V10.get_x() << "\t" << V10.get_y() << "\t//\t" << V20.get_x()
  //           << "\t" << V20.get_y() << std::endl;
  // std::cout << V1x << "\t" << V1y << "\t//\t" << V2x << "\t" << V2y <<
  // std::endl
  //           << std::endl;

  // this->set_engine_speed(engine::Vector(V1x, V1y));

  // other.set_engine_speed(engine::Vector(V2x, V2y));

  this->set_engine_speed(engine::Vector(0, 0));
  other.set_engine_speed(engine::Vector(0, 0));

  this->set_dictated_speed(this->get_dictated_speed() +
                           engine::Vector(V2x, V2y));
  other.set_dictated_speed(other.get_dictated_speed() -
                           engine::Vector(V1x, V1y));
}

}  // namespace space
