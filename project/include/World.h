#pragma once

#include <list>
#include <memory>
#include <queue>
#include <vector>

#include "Bullet.h"
#include "Enemy.h"
#include "Engine.h"
#include "Player.h"
#include "Status.h"
#include "Enemy.h"
#include "MissionStatus.h"

class World {
 public:
  World();
  ~World() = default;

    void update(sf::Time d_time);
    std::queue<std::pair<size_t, Player::Action>>& get_actions();
    std::vector<std::vector<Status>> get_status();

    bool is_over();
    std::vector<Mission> get_mission() const;

    void push_player(std::unique_ptr<engine::MoveAble> player);
    void push_back(std::unique_ptr<engine::ImmoveAble> immoveable);
    void push_back(std::unique_ptr<engine::MoveAble> moveable);
    void push_back(std::unique_ptr<space::Bullet> bullet);
    void push_back(std::unique_ptr<space::Enemy> enemy);

    void free();


 private:
    std::queue<std::pair<size_t, Player::Action>> _actions;

    std::vector<std::unique_ptr<engine::MoveAble>> _players;
    std::vector<std::unique_ptr<engine::MoveAble>> _moveable;
    std::vector<std::unique_ptr<engine::ImmoveAble>> _immoveable;
    std::vector<std::unique_ptr<space::Bullet>> _bullet;
    std::vector<std::unique_ptr<space::Enemy>> _enemies;

    std::vector<std::vector<Status>> _status;

    std::vector<Mission> _mission_status;

    size_t _player_count;
    size_t _moveable_count;
    size_t _immoveable_count;

    void do_action(size_t id, Player::Action action, sf::Time d_time);
    void portal(engine::MoveAble& moveable);
    void update_all(sf::Time d_time);

    void player_moveable();
    void player_enemy();
    void player_player();

    void enemy_enemy();
    void enemy_moveable();

    void immoveable_all();
    void bullet_all();

    void portal_all();
};
