#include "A-Explosion.h"

namespace animation {

Explosion::Explosion(const sf::Texture *texture, sf::Vector2f position,
                     float angle)
    : Manager(texture, position, angle) {
  set_image_count(sf::Vector2u(3, 2));
  set_size(sf::Vector2f(293, 282.5));
  set_origin(sf::Vector2f(146.5f, 141.25f));
  set_switch_time(sf::seconds(0.1f));
  set_start_angle(0);
}

void Explosion::update(sf::Time d_time) {
  if (_total_time + d_time >= _switch_time) {
    if (_current_image.x >= _image_count.x - 1) {
      _current_image.y++;
      if (_current_image.y >= _image_count.y) {
        _is_playing = false;
      }
    }
  }

  Manager::update(d_time);
}

}  // namespace animation