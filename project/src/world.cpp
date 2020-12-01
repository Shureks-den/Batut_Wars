#include "world.h"

#include <cassert>

#include "ship.h"

World::World() {
    _objects.push_back(space::Ship());  // TODO(ANDY) написать нормальный конструктор
}

void World::update(sf::Time d_time) {
    while (!_actions.empty()) {
        do_action(0, _actions.front(), d_time);
        _actions.pop();
    }

    for (auto &it : _objects) {  // TODO(ANDY) 
        it.update(d_time);
    }
    // Рассчет коллизий
}

void World::push_back(engine::Entity &object) {
    _objects.push_back(object);
}

void World::do_action(size_t id, Action action, sf::Time d_time) {  // TODO(ANDY) переписать на таблицу Command
    space::Ship *ship = dynamic_cast<space::Ship*>(&_objects[id]);
    assert(ship != nullptr);
    switch (action) {
    case Action::MOVE_FORWARD:
        ship->give_acceleration(Direction::FORWARD, 10.0 * d_time.asSeconds()); // TODO(ANDY) довести до ума
        break;
    case Action::MOVE_BACKWARD:
        ship->give_acceleration(Direction::BACKWARD, 10.0 * d_time.asSeconds()); // TODO(ANDY) довести до ума
        break;
    case Action::MOVE_LEFT:
        ship->rotate(-45.0 * d_time.asSeconds()); // TODO(ANDY) довести до ума
        break;
    case Action::MOVE_RIGHT:
        ship->rotate(45.0 * d_time.asSeconds()); // TODO(ANDY) довести до ума блять
        break;

    default:
        break;
    }
}