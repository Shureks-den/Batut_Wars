#include "A-Bullet.h"

namespace animation {

Bullet::Bullet(const sf::Texture *texture, sf::Vector2f position, float angle)
    : Manager(texture, position, angle) {
  set_image_count(sf::Vector2u(4, 1));
  set_size(sf::Vector2f(30, 30));
  set_origin(sf::Vector2f(15, 15));
  set_switch_time(sf::seconds(0.03f));
  set_start_angle(0);
}

void Bullet::update(sf::Time d_time) { Manager::update(d_time); }

}  // namespace animation
