#pragma once

#include "animation.h"

namespace animation {

class Ship : public Manager {
 public:
    Ship(sf::Vector2f position, float angle);
    ~Ship() = default;
};

Ship::Ship(sf::Vector2f position, float angle): Manager(Id::SHIP, position, angle) {
    set_switch_time(sf::seconds(0.1f));
    set_image_count(sf::Vector2u(5, 1));

    sf::Vector2f size(_body.getTextureRect().width, _body.getTextureRect().height);
    size.x /= 2;
    size.y /= 2;
    _body.setSize(size);
    size.x /= 2;
    size.y /= 2;
    _body.setOrigin(size.x, size.y);
}

class Space : public Manager {
 public:
    Space(sf::Vector2f position, float angle);
    ~Space() = default;
};

Space::Space(sf::Vector2f position, float angle) : Manager(Id::SPACE, position, angle) {
    set_image_count(sf::Vector2u(1, 1));
}

}  // namespace animation
