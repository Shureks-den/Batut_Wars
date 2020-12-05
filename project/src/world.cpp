#include "world.h"

#include <iostream>
#include <cassert>

#include "ship.h"
#include "layer.h"

World::World() {;}  // TODO(ANDY) написать нормальный конструктор

void World::update(sf::Time d_time) {
    while (!_actions.empty()) {
        do_action(0, _actions.front(), d_time);
        _actions.pop();
    }

    for (auto &it : _objects) {  // TODO(ANDY)
        it->update(d_time);
        _status[0].position = it->get_position();  // TODO(ANDY) обновление status 
        std::cout << it->get_position().x << " " << it->get_position().y << std::endl;
    }
    // Рассчет коллизий
}

void World::push_back(engine::Entity &object) {
    _objects.push_back(&object);
    Status status;  // TODO(ANDY) метод создания status по объекту
    status.angle = 0;
    status.lay_id = static_cast<size_t>(animation::LayerNom::OBJECTS);
    status.id = _objects.size() - 1;
    status.animation_id = animation::Id::SHIP;
    status.is_removed = false;
    status.states.resize(1);
    status.states[1] = true;
    status.position = object.get_position();
    _status.push_back(status);
}

void World::do_action(size_t id, Action action, sf::Time d_time) {  // TODO(ANDY) переписать на таблицу Command
    space::Ship *ship = dynamic_cast<space::Ship*>(_objects[id]);
    assert(ship != nullptr);
    switch (action) {
    case Action::MOVE_FORWARD:
        ship->give_acceleration(Direction::FORWARD, 10.0 * d_time.asSeconds());  // TODO(ANDY) довести до ума
        break;
    case Action::MOVE_BACKWARD:
        ship->give_acceleration(Direction::BACKWARD, 10.0 * d_time.asSeconds());  // TODO(ANDY) довести до ума
        break;
    case Action::MOVE_LEFT:
        ship->rotate(-45.0 * d_time.asSeconds());  // TODO(ANDY) довести до ума
        break;
    case Action::MOVE_RIGHT:
        ship->rotate(45.0 * d_time.asSeconds());  // TODO(ANDY) довести до ума блять
        break;

    default:
        break;
    }
}

std::vector<Status> World::get_status() {
    std::vector<Status> tmp(_status);
    return tmp;
}

std::queue<Action>& World::get_actions() {
    return _actions;
}
