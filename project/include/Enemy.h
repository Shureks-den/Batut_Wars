#pragma once

#include "Ship.h"

#include <queue>

namespace space {

class Enemy : public space::Ship {
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
    
    std::unique_ptr<Bullet> fire() override;

    void virtual trigger(engine::MoveAble &moveable) override;

    void turn_to_player();

 private:
    float _rotate_speed;
    bool _is_player_spotted;
    sf::Time _rotate_time;  // Время до поворота
    sf::Vector2f _vision; //  квадрат обзора
    sf::Vector2f _player_location;
    std::queue<bot_actions> action_queue;
    bool _aimed;
};

}  // end namespace space