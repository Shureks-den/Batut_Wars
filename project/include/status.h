#pragma once

#include <SFML/Graphics.hpp>

namespace animation {

enum class Id {  // Для анимаций
    SHIP = 0,
    SPACE,
    BULLET,
    PLANET,
    COUNT
};

}  // namespace animation

class Status {
 public:
    Status() = default;
    ~Status() = default;

    size_t lay_id;
    size_t id;

    bool is_removed;
    animation::Id animation_id;

    std::vector<bool> states;
    float angle;
    sf::Vector2f position;
};
