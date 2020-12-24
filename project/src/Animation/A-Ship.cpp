#include "A-Ship.h"

namespace animation {

Ship::Ship(const sf::Texture *texture, sf::Vector2f position, float angle)
    : Manager(texture, position, angle) {
  set_switch_time(sf::seconds(0.1f));
  set_image_count(sf::Vector2u(5, 1));
  set_start_angle(90);

  set_size(sf::Vector2f(48, 64));
  set_origin(sf::Vector2f(24, 37));
}

void Ship::update(sf::Time d_time) { Manager::update(d_time); }

}  // namespace animation
