#pragma once

#include <queue>
#include <vector>
#include <memory>

#include "Engine.h"
#include "Player.h"
#include "Status.h"

class World {
 public:
    World();
    ~World() = default;

    void update(sf::Time d_time);
    void push_back(std::unique_ptr<engine::Entity> object);
    std::queue<Player::Action>& get_actions();
    std::vector<Status> get_status();
    // size_t get_player_id();
    bool is_over();
    void add_player(size_t id);

 private:
    std::vector<std::unique_ptr<engine::Entity>> _objects;
    std::queue<Player::Action> _actions;
    //std::queue<std::pair<size_t, Player::Action>> _actions_;
    std::vector<Status> _status;
    std::vector<size_t> _players;

    void do_action(size_t id, Player::Action action, sf::Time d_time);
};

// struct ShipMover
// {
//    ShipMover(float vx, float vy)
//    : velocity(vx, vy)
//    {
//    }

//    void operator() (space::Ship& ship, sf::Time) const
//    {
//        ship.get_acceleration()
//    }

//    sf::Vector2f velocity;
// };
