#pragma once

#include "engine.h"
#include "player.h"

class World {
 public:
    World();
    ~World() = default;

    void update(sf::Time d_time);
    void push_back(engine::Entity &object);
    std::queue<Action>& get_actions();

 private:
    std::vector<engine::Entity> _objects;
    std::queue<Action> _actions;

    void do_action(size_t id, Action action, sf::Time d_time);
};

// struct ShipMover
// {
// 	ShipMover(float vx, float vy)
// 	: velocity(vx, vy)
// 	{
// 	}

// 	void operator() (space::Ship& ship, sf::Time) const
// 	{
// 		ship.get_acceleration()
// 	}

// 	sf::Vector2f velocity;
// };