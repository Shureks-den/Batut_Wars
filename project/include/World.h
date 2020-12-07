#pragma once

#include "Engine.h"
#include "Player.h"
#include "Status.h"

class World {
 public:
    World();
    ~World() = default;

    void update(sf::Time d_time);
    void push_back(engine::Entity &object);
    std::queue<Player::Action>& get_actions();
    std::vector<Status> get_status();

 private:
    std::vector<engine::Entity*> _objects;
    std::queue<Player::Action> _actions;
    std::vector<Status> _status;

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
