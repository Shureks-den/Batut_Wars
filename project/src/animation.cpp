#include "animation.h"

#include <vector>

namespace animation {

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

AnimationManager::AnimationManager(Animation &animation, sf::Vector2f position) {
    _animation = animation;
    _current = 0;
    _body.setSize(sf::Vector2f(_animation.uv_rect.width, _animation.uv_rect.height));  // TODO(ANDY) мб хрень написал
    _body.setPosition(position);
    _body.setTextureRect(_animation.uv_rect);
}

AnimationManager::AnimationManager(AnimationId animation_id, sf::Vector2f position, float angle) {
    _angle = angle;
    _body.setPosition(position);
    sf::Texture texture;
    switch (animation_id) {
    case AnimationId::SHIP:  // TODO(ANDY) загрузка конкретной текстуры из файла
        texture.loadFromFile("project/media/smallfreighterspr.png");
        _animation = animation::Animation(&texture, sf::Vector2u(1, 1), sf::seconds(0.5));
        break;
    default:
        break;
    }
}

void AnimationManager::draw(sf::RenderWindow &window) {
    window.draw(_body);
}

void AnimationManager::update(sf::Time d_time) {  // TODO(ANDY) реализовать
    _animation.update(_current, d_time, false);
}

void AnimationManager::set_angle(float angle) {
    _angle = angle;
}

void AnimationManager::set_states(std::vector<bool> &states) {
    if (states.empty()) {
        _current = 0; // TODO(ANDY) правило перехода из status в _current
    } else {
        _current = _current;
    }
}

void AnimationManager::set_position(sf::Vector2f &position) {
    _body.setPosition(position);
}

} // namespace animation
