#pragma once

#include <SFML/Graphics.hpp>

#include "status.h"

namespace animation {

class Animation {
 public:
    Animation() = default;
    Animation(const sf::Texture *texture, sf::Vector2u image_count, sf::Time switch_time);
    ~Animation() = default;

    void update(int row, sf::Time d_time, bool is_forward);

    sf::IntRect uv_rect;

 private:
    sf::Vector2u _image_count;
    sf::Vector2u _current_image;

    sf::Time _total_time;
    sf::Time _switch_time;
};

class AnimationManager {
 public:
    AnimationManager(Animation animation, sf::Vector2f position);
    AnimationManager(const sf::Texture *texture, sf::Vector2f position, float angle);  // Переписать на status
    ~AnimationManager() = default;

    void update(sf::Time d_time);
    void draw(sf::RenderWindow &window);
    void set_states(const std::vector<bool> &states);
    void set_position(const sf::Vector2f &position);
    void set_angle(const float angle);

 private:
    sf::RectangleShape _body;
    Animation _animation;
    size_t _current;

    float _angle;
};

}  // namespace animation
