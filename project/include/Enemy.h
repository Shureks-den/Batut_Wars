#pragma once

#include <memory>

#include <SFML/System/Time.hpp>

#include "Engine.h"
#include "Ship.h"
#include "Bullet.h"

namespace space {

class Enemy : public engine::MoveAble {
 public:
    Enemy();
    ~Enemy() = default;

    void update(sf::Time dt) override;
    animation::Id get_animation_id() const override;
    
    std::unique_ptr<Bullet> fire();
    void turn_to_player();
    void move();

 private:
    float _rotate_speed;
    bool spot_player(Ship player_ship);
    sf::Vector2f _vision;  // видимость
    const sf::Time _recharge;  // Перезарядка между выстрелами
    sf::Time _countdown;  // Текущий кд
};

}  // end namespace space