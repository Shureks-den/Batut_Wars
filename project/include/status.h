#pragma once

#include <SFML/Graphics.hpp>

enum class AnimationId {  // Для анимаций
    SHIP = 0,
    BULLET,
    PLANET,
    COUNT
};

class Status {
 public:
    Status() = default;
    ~Status() = default;

    size_t lay_id;
    size_t id;

    bool is_removed;
    AnimationId animation_id;

    std::vector<bool> states;
    double angle;
    sf::Vector2f position;
};
