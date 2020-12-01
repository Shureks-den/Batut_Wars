#include "animation.h"

#include <vector>

Animation::Animation(sf::Texture *texture, sf::Vector2u image_count, sf::Time switch_time) {
    _image_count = image_count;
    _switch_time = switch_time;
    _total_time = sf::Time::Zero;
    _current_image.x = 0;

    uv_rect.width = texture->getSize().x / static_cast<double>(image_count.x);
    uv_rect.height = texture->getSize().y / static_cast<double>(image_count.y);
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

    uv_rect.left = _current_image.x * uv_rect.width;
    uv_rect.top = _current_image.y * uv_rect.height;

    if (is_forward) {
        uv_rect.left = _current_image.x * uv_rect.width;
        uv_rect.width = abs(uv_rect.width);
    } else {
        uv_rect.left = (_current_image.x + 1) * abs(uv_rect.width);
        uv_rect.width = -abs(uv_rect.width);
    }
    
}

AnimationManager::AnimationManager(std::vector<Animation> &animations, sf::Vector2f position) {
    _animations = animations;
    _current = 0;
    _body.setSize(sf::Vector2f(80.0, 80.0));  // TODO(ANDY) костыль
    _body.setPosition(position);
    _body.setTextureRect(_animations.begin()->uv_rect);
}

void AnimationManager::draw(sf::RenderWindow &window) {
    window.draw(_body);
}

void update() {  // TODO(ANDY) реализовать
    ;            // На вход - изменение состояния (и позиции)
}