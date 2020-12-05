#include "animation.h"

#include <vector>

namespace animation {

Animation::Animation(const sf::Texture *texture, sf::Vector2u image_count, sf::Time switch_time) {
    _image_count = image_count;
    _switch_time = switch_time;
    _total_time = sf::Time::Zero;
    _current_image.x = 0;

    uv_rect.width = texture->getSize().x / static_cast<float>(image_count.x);
    uv_rect.height = texture->getSize().y / static_cast<float>(image_count.y);
}

void Animation::update(int row, sf::Time d_time, bool is_forward) {
    _current_image.y = row;
    _total_time += d_time;

    if (_total_time >= _switch_time) {
        _total_time -= _switch_time;
        _current_image.x++;

        if (_current_image.x >= _image_count.x) {
            _current_image.x = 0;
        }
    }

    uv_rect.top = _current_image.y * uv_rect.height;

    if (is_forward) {
        uv_rect.left = _current_image.x * uv_rect.width;
        uv_rect.width = abs(uv_rect.width);
    } else {
        uv_rect.left = (_current_image.x + 1) * abs(uv_rect.width);
        uv_rect.width = -abs(uv_rect.width);
    }
}

void Animation::set_switch_time(sf::Time switch_time) {
    _switch_time = switch_time;
}

void Animation::set_image_count(sf::Vector2u image_count) {
    uv_rect.width *= _image_count.x;
    uv_rect.height *= _image_count.y;
    _image_count = image_count;
    uv_rect.width = uv_rect.width / static_cast<float>(image_count.x);
    uv_rect.height = uv_rect.height / static_cast<float>(image_count.y);
    _current_image.x = 0;
    _current_image.y = 0;
}

Manager::Manager(Animation animation, sf::Vector2f position) {
    _animation = animation;
    _current = 0;
    _body.setSize(sf::Vector2f(_animation.uv_rect.width, _animation.uv_rect.height));
    _body.setPosition(position);
    _body.setTextureRect(_animation.uv_rect);
}

Manager::Manager(const sf::Texture *texture, sf::Vector2f position, float angle) {
    _animation = Animation(texture, sf::Vector2u(1, 1), sf::seconds(0.1f));
    _body.setPosition(position);
    _body.setSize(sf::Vector2f(_animation.uv_rect.width, _animation.uv_rect.height));
    _body.setTextureRect(_animation.uv_rect);
    _body.setTexture(texture);
    _body.setOrigin(_animation.uv_rect.width / 2, _animation.uv_rect.height / 2);
    _angle = angle;
    _current = 0;
}

Manager::Manager(Id id, sf::Vector2f position, float angle) {
    const sf::Texture *texture = _holder.get_texture(id);
    _animation = Animation(texture, sf::Vector2u(1, 1), sf::seconds(0.1f));
    _body.setPosition(position);
    _body.setSize(sf::Vector2f(_animation.uv_rect.width, _animation.uv_rect.height));
    _body.setTextureRect(_animation.uv_rect);
    _body.setTexture(texture);
    _body.setOrigin(_animation.uv_rect.width / 2, _animation.uv_rect.height / 2);
    _angle = angle;
    _current = 0;
}

void Manager::draw(sf::RenderWindow &window) {
    window.draw(_body);
}

void Manager::update(sf::Time d_time) {
    _animation.update(_current, d_time, true);
    _body.setTextureRect(_animation.uv_rect);
    _body.setRotation(_angle);
}

void Manager::set_angle(const float angle) {
    _angle = angle;
}

void Manager::set_states(const std::vector<bool> &states) {
    if (states.empty()) {
        _current = 0;  // TODO(ANDY) правило перехода из status в _current
    } else {
        _current = _current;
    }
}

void Manager::set_position(const sf::Vector2f &position) {
    _body.setPosition(position);
}

void Manager::set_switch_time(sf::Time switch_time) {
    _animation.set_switch_time(switch_time);
}

void Manager::set_image_count(sf::Vector2u image_count) {
    _animation.set_image_count(image_count);
    _body.setSize(sf::Vector2f(_animation.uv_rect.width, _animation.uv_rect.height));
    _body.setTextureRect(_animation.uv_rect);
    _body.setOrigin(_animation.uv_rect.width / 2, _animation.uv_rect.height / 2);
}

Holder Manager::_holder;  // static-член класса Manager

}  // namespace animation
