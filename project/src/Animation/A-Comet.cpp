#include "A-Comet.h"

namespace animation {

Comet::Comet(const sf::Texture *texture, sf::Vector2f position, float angle)
    : Manager(texture, position, angle) {
  set_image_count(sf::Vector2u(6, 1));
  set_size(sf::Vector2f(160, 160));
  set_origin(sf::Vector2f(100, 80));  // Радиус ~20
  set_switch_time(sf::seconds(0.1f));
  set_start_angle(0);
}

void Comet::update(sf::Time d_time) { Manager::update(d_time); }

}  // namespace animation