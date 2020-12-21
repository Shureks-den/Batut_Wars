#pragma once

#include <memory>
#include <queue>

#include <SFML/System/Time.hpp>

#include "Engine.h"
#include "Ship.h"
#include "Bullet.h"

namespace space {
   
class Enemy : public engine::MoveAble {
 public:
    enum bot_actions {
       ROTATE_LEFT,
       ROTATE_RIGHT,
       FIRE,
       COUNT
    };
 public:
    Enemy();
    ~Enemy() = default;

    void update(sf::Time dt) override;
    animation::Id get_animation_id() const override;
    
    std::unique_ptr<Bullet> fire();
    void collision(engine::MoveAble &MoveAble) override;
    void turn_to_player();

    void trigger(engine::MoveAble &moveable);

    void spot_player(Ship &player_ship);

 private:
    bool _is_player_spotted;
    const sf::Time _recharge;  // Перезарядка между выстрелами
    sf::Time _countdown;   
    sf::Time _rotate_time;  // Время до поворота
    sf::Vector2f _vision; //  квадрат обзора
    float _rotate_speed;
    sf::Vector2f _player_location;
    std::queue<bot_actions> action_queue;
     
};

}  // end namespace space