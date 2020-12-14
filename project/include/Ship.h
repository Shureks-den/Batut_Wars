#pragma once

#include <memory>

#include <SFML/System/Time.hpp>

#include "Engine.h"
#include "Bullet.h"

namespace space {

class Ship : public engine::MoveAble {
 public:
    Ship();
    ~Ship() = default;

    void update(sf::Time dt) override;
    animation::Id get_animation_id() const override;
    std::unique_ptr<Bullet> fire();

 private:

    const sf::Time _recharge;  // Перезарядка между выстрелами
    sf::Time _countdown;  // Текущий кд
};

}  // end namespace space
