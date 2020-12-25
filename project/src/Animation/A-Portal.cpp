#include "A-Portal.h"

namespace animation {

Portal::Portal(const sf::Texture *texture, sf::Vector2f position, float angle)
    : Manager(texture, position, angle) {
  set_image_count(sf::Vector2u(4, 4));
  set_size(sf::Vector2f(182, 206));
  set_origin(sf::Vector2f(91, 103));
  set_switch_time(sf::seconds(0.1f));
  set_start_angle(0);
}

void Portal::update(sf::Time d_time) {
  if (_total_time + d_time >= _switch_time) {
    if (_current_image.x >= _image_count.x - 1) {
      _current_image.y++;
      if (_current_image.y >= _image_count.y) {
        _current_image.y = 0;
      }
    }
  }

  Manager::update(d_time);
}

}  // namespace animation
