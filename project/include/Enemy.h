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
    void turn_to_player(Ship *player_ship);
    void move();

 private:
    bool spot_player(Ship *player_ship);
    const sf::Time _recharge;  // Перезарядка между выстрелами
    sf::Time _countdown;
    sf::Vector2f _vision; // 
    float _rotate_speed;
    float _acc
     
};

}  // end namespace space