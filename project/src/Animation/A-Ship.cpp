#include "A-Ship.h"

namespace animation {

Ship::Ship(const sf::Texture *texture, sf::Vector2f position, float angle)
    : Manager(texture, position, angle) {
  set_switch_time(sf::seconds(0.1f));
  set_image_count(sf::Vector2u(5, 3));
  set_start_angle(90);

  set_size(sf::Vector2f(48, 64));
  set_origin(sf::Vector2f(24, 37));
}

void Ship::update(sf::Time d_time) {
  if (_status[1]) {
    _current_image.y = 0;
  } else if (_status[2]) {
    _current_image.y = 1;
  } else if ((_status[3])) {
    _current_image.y = 2;
  }

  Manager::update(d_time);
}

}  // namespace animation
