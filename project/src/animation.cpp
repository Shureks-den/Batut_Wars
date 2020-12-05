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

AnimationManager::AnimationManager(Animation animation, sf::Vector2f position) {
    _animation = animation;
    _current = 0;
    _body.setSize(sf::Vector2f(_animation.uv_rect.width, _animation.uv_rect.height));
    _body.setPosition(position);
    _body.setTextureRect(_animation.uv_rect);
}

AnimationManager::AnimationManager(const sf::Texture *texture, sf::Vector2f position, float angle) {
    _animation = Animation(texture, sf::Vector2u(1, 1), sf::seconds(0.5f));
    _body.setPosition(position);
    _body.setSize(sf::Vector2f(_animation.uv_rect.width, _animation.uv_rect.height));
    _body.setTextureRect(_animation.uv_rect);
    _body.setTexture(texture);
    _angle = angle;
    _current = 0;
}

void AnimationManager::draw(sf::RenderWindow &window) {
    window.draw(_body);
}

void AnimationManager::update(sf::Time d_time) {
    _animation.update(_current, d_time, true);
}

void AnimationManager::set_angle(const float angle) {
    _angle = angle;
}

void AnimationManager::set_states(const std::vector<bool> &states) {
    if (states.empty()) {
        _current = 0;  // TODO(ANDY) правило перехода из status в _current
    } else {
        _current = _current;
    }
}

void AnimationManager::set_position(const sf::Vector2f &position) {
    _body.setPosition(position);
}

}  // namespace animation
