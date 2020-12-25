#include "Animation.h"

#include <vector>

namespace animation {

Manager::Manager(const sf::Texture *texture, sf::Vector2f position,
                 float angle) {
  _is_playing = true;

  _image_count = sf::Vector2u(1, 1);
  _switch_time = sf::seconds(0.1f);
  _total_time = sf::Time::Zero;
  _current_image.x = 0;
  _current_image.y = 0;

  _uv_rect.width = texture->getSize().x / static_cast<float>(_image_count.x);
  _uv_rect.height = texture->getSize().y / static_cast<float>(_image_count.y);

  _body.setPosition(position);
  _body.setSize(sf::Vector2f(_uv_rect.width, _uv_rect.height));
  _body.setTextureRect(_uv_rect);
  _body.setTexture(texture);
  _body.setOrigin(_uv_rect.width / 2, _uv_rect.height / 2);
  _angle = angle;
}

void Manager::draw(sf::RenderWindow &window) {
  if (!_is_playing) {
    return;
  }

  window.draw(_body);
}

void Manager::update(sf::Time d_time) {
  if (!_is_playing) {
    return;
  }

  // _current_image.y = row;
  _total_time += d_time;

  if (_total_time >= _switch_time) {
    _total_time -= _switch_time;
    _current_image.x++;

    if (_current_image.x >= _image_count.x) {
      _current_image.x = 0;
    }
  }

  _uv_rect.top = _current_image.y * _uv_rect.height;

  // if (is_forward) {
  if (true) {
    _uv_rect.left = _current_image.x * _uv_rect.width;
    _uv_rect.width = abs(_uv_rect.width);
  } else {
    _uv_rect.left = (_current_image.x + 1) * abs(_uv_rect.width);
    _uv_rect.width = -abs(_uv_rect.width);
  }

  _body.setTextureRect(_uv_rect);
  _body.setRotation(_angle + _start_angle);
}

void Manager::set_angle(const float angle) { _angle = angle; }

void Manager::set_start_angle(const float start_angle) {
  _start_angle = start_angle;
}

void Manager::set_states(const std::vector<bool> &status) {
  _status.assign(status.begin(), status.end());
}

void Manager::set_position(const sf::Vector2f &position) {
  _body.setPosition(position);
}

void Manager::set_switch_time(sf::Time switch_time) {
  _switch_time = switch_time;
}

void Manager::set_image_count(sf::Vector2u image_count) {
  _uv_rect.width *= _image_count.x;
  _uv_rect.height *= _image_count.y;
  _image_count = image_count;
  _uv_rect.width = _uv_rect.width / static_cast<float>(image_count.x);
  _uv_rect.height = _uv_rect.height / static_cast<float>(image_count.y);
  _current_image.x = 0;
  _current_image.y = 0;

  _body.setSize(sf::Vector2f(_uv_rect.width, _uv_rect.height));
  _body.setTextureRect(_uv_rect);
  _body.setOrigin(_uv_rect.width / 2, _uv_rect.height / 2);
}

sf::Vector2f Manager::get_size() const { return _body.getSize(); }

void Manager::set_size(sf::Vector2f size) { _body.setSize(size); }

void Manager::set_size_s(sf::Vector2f size) {  // Безопасна для центра
  auto coef = _body.getSize();
  coef.x /= size.x;
  coef.y /= size.y;
  auto new_origin = _body.getOrigin();
  new_origin.x /= coef.x;
  new_origin.y /= coef.y;
  _body.setSize(size);
  _body.setOrigin(new_origin);
}

void Manager::set_origin(sf::Vector2f center) {
  _body.setOrigin(center.x, center.y);
}

void Manager::set_playing(bool is_playing) { _is_playing = is_playing; }

bool Manager::is_playing() const { return _is_playing; }

}  // namespace animation
