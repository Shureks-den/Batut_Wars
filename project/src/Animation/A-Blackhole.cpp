#include "A-Blackhole.h"

namespace animation {

Blackhole::Blackhole(const sf::Texture *texture, sf::Vector2f position,
                     float angle)
    : Manager(texture, position, angle) {
  set_image_count(sf::Vector2u(1, 1));
  set_size(sf::Vector2f(250, 250));
  set_origin(sf::Vector2f(125, 125));
  set_start_angle(0);
}

void Blackhole::update(sf::Time d_time) { Manager::update(d_time); }

}  // namespace animation
