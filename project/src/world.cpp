#include "world.h"

#include <cassert>

#include "ship.h"
#include "layer.h"
#include "engine.h"

static const size_t MAP_SIZE = 2000;  // Криво, но пока надо

static Status to_status(engine::Entity &entity) {
    Status status;
    status.id = entity.get_id();
    status.is_removed = false;  // TODO(ANDY) в зависимости от hp
    status.animation_id = entity.get_animation_id();
    status.lay_id = static_cast<size_t>(animation::LayerNom::OBJECTS);  // TODO(ANDY) получить LayerNom по Id
    status.states = entity.get_state();
    status.angle = 0;  // TODO(ANDY) костыль
    status.position = entity.get_position();
    return status;
}

World::World() {;}  // TODO(ANDY) написать нормальный конструктор

void World::update(sf::Time d_time) {
    while (!_actions.empty()) {
        do_action(0, _actions.front(), d_time);
        _actions.pop();
    }

    for (size_t i = 0; i < _objects.size(); ++i) {
        _objects[i]->update(d_time);
        _status[i].position = _objects[i]->get_position();  // TODO(ANDY) обновление status (после реализации angle в Entity)

        if (_status[i].position.x > MAP_SIZE) {
            _status[i].position.x -= MAP_SIZE;
            _objects[i]->set_x(_status[i].position.x);
        }
        if (_status[i].position.x < 0) {
            _status[i].position.x += MAP_SIZE;
            _objects[i]->set_x(_status[i].position.x);
        }
        if (_status[i].position.y > MAP_SIZE) {
            _status[i].position.y -= MAP_SIZE;
            _objects[i]->set_y(_status[i].position.y);
        }
        if (_status[i].position.y < 0) {
            _status[i].position.y += MAP_SIZE;
            _objects[i]->set_y(_status[i].position.y);
        }

    }

    // Рассчет коллизий
}

void World::push_back(engine::Entity &object) {
    _objects.push_back(&object);
    Status status = to_status(object);
    _status.push_back(status);
}

void World::do_action(size_t id, Action action, sf::Time d_time) {  // TODO(ANDY) переписать на таблицу Command
    space::Ship* ship = dynamic_cast<space::Ship*>(_objects[id]);
    assert(ship != nullptr);
    switch (action) {
    case Action::MOVE_FORWARD:
        ship->give_acceleration(Way::ALONG);  // TODO(ANDY) довести до ума
        break;
    case Action::MOVE_BACKWARD:
        ship->give_acceleration(Way::CONTRA);  // TODO(ANDY) довести до ума
        break;
    case Action::MOVE_LEFT:
        ship->rotate_orientation(engine::as_radian(- 90.0) * d_time.asSeconds());  // TODO(ANDY) довести до ума
        _status[id].angle = engine::as_degree(ship->get_angle());
        break;
    case Action::MOVE_RIGHT:
        ship->rotate_orientation(engine::as_radian(90.0) * d_time.asSeconds());  // TODO(ANDY) довести до ума
        _status[id].angle = engine::as_degree(ship->get_angle());
        break;

    default:
        break;
    }
}

std::vector<Status> World::get_status() {
    return _status;
}

std::queue<Action>& World::get_actions() {
    return _actions;
}
