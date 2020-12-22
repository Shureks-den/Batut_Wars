#pragma once

#include <SFML/System/Time.hpp>
#include <memory>
#include <queue>

#include "Bullet.h"
#include "Engine.h"
#include "Ship.h"

namespace space {

class Enemy : public engine::MoveAble {
 public:
  enum bot_actions { NOPLAYER, ROTATE, FIRE, COUNT };

 public:
  Enemy();
  ~Enemy() = default;

  void update(sf::Time dt) override;
  animation::Id get_animation_id() const override;

  std::unique_ptr<Bullet> fire();
  void collision(engine::MoveAble &MoveAble) override;
  void turn_to_player(Ship &player_ship);

  void virtual trigger(engine::MoveAble &player_ship) override;

 private:
  bool _is_player_spotted;
  const sf::Time _recharge;  // Перезарядка между выстрелами
  sf::Time _countdown;
  sf::Vector2f _vision;  //
  float _rotate_speed;
  float _acc;
};

}  // end namespace space