#include "A-Space.h"

namespace animation {

Space::Space(const sf::Texture *texture, sf::Vector2f position, float angle)
    : Manager(texture, position, angle) {
  set_image_count(sf::Vector2u(1, 1));
  set_start_angle(0);
  set_switch_time(sf::seconds(1.f));
}

void Space::update(sf::Time d_time) { Manager::update(d_time); }

}  // namespace animation
