#include "A-Maul.h"

namespace animation {

Maul::Maul(const sf::Texture *texture, sf::Vector2f position, float angle)
    : Manager(texture, position, angle) {
  set_switch_time(sf::seconds(0.1f));
  set_image_count(sf::Vector2u(1, 1));
  set_start_angle(90);

  set_size(sf::Vector2f(35, 49.5));
  set_origin(sf::Vector2f(17.5, 24.75));
}

void Maul::update(sf::Time d_time) { Manager::update(d_time); }

}  // namespace animation