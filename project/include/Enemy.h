#pragma once

#include <queue>

#include "Ship.h"

namespace space {

class Enemy : public space::Ship {
 public:
  enum bot_actions { ROTATE_LEFT, ROTATE_RIGHT, FIRE, COUNT };

 public:
    Enemy();
    ~Enemy() = default;

    void update(sf::Time dt) override;
    animation::Id get_animation_id() const override;

    std::unique_ptr<Bullet> fire() override;

    void virtual trigger(engine::MoveAble &moveable) override;
    void trigger(engine::ImmoveAble &immoveable);
    void trigger(Enemy &enemy);

    void turn_to_player();
    void turn_from_planet();
    void turn_from_enemy();

 private:
    bool _is_going_to_planet;
    bool _is_player_spotted;
    bool _aimed;
    bool _close_to_enemy_ship;
    // это ИИ детка //

    const sf::Time _recharge;  // Перезарядка между выстрелами
    sf::Time _countdown;   
    sf::Time _rotate_time;  // Время до поворота

    sf::Vector2f _vision; //  квадрат обзора
    float _rotate_speed;

    sf::Vector2f _enemy_location;
    sf::Vector2f _player_location;
    sf::Vector2f _planet_location;
};

}  // end namespace space