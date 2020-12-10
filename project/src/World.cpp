#include "World.h"

#include <cassert>
#include <memory>
#include <algorithm>

#include "Ship.h"
#include "Layer.h"
#include "Engine.h"

static constexpr size_t MAP_SIZE = 4 * 450;  // Криво, но пока надо

enum class StatusLay {
    PLAYER = 0,
    MOVEABLE,
    IMMOVEABLE,
    COUNT
    // MOVEABLE,
    // BULLET,
    // COUNT
};

static Status to_status(engine::Entity const &entity) {
    Status status;
    status.id = entity.get_id();
    status.is_removed = false;  // TODO(ANDY) в зависимости от hp
    status.animation_id = entity.get_animation_id();
    switch (status.animation_id) {  // TODO(ANDY) переписать на функцию
    case animation::Id::SHIP:  
        status.lay_id = static_cast<size_t>(animation::LayerNom::OBJECTS);
        break;
    case animation::Id::BLACKHOLE:
        status.lay_id = static_cast<size_t>(animation::LayerNom::PLANETS);
        break;
    default:
        break;
    }
    status.states = entity.get_state();
    status.angle = engine::as_degree(entity.get_angle());
    status.position = entity.get_position();
    return status;
}

World::World() {
    // TODO(SHUREK) чтение карты из файла
    _status.resize(static_cast<size_t>(StatusLay::COUNT));
}

void World::update(sf::Time d_time) {
    while (!_actions.empty()) {
        do_action(0, _actions.front(), d_time);
        _actions.pop();
    }

    // while (!_actions_.empty()) {
    //     do_action(_actions_.front().first, _actions_.front().second, d_time);
    //     _actions.pop();
    // }

    for (auto &it : _players) {
        it->update(d_time);
    }

    for (auto &it : _moveable) {
        it->update(d_time);
    }

    for (auto &it : _immoveable) {
        it->update(d_time);
    }

    // for (auto &it : _bullet) {
    //     it->update(d_time);
    // }

    for (auto &player : _players) {
        // for (auto &moveable : _moveable) {
        //     player->collision(*moveable);
        //     moveable->collsison(*player);
        // }
        for (auto &immoveable : _immoveable) {
            immoveable->collision(*player);
        }
        // for (auto &bullet : _bullet) {
        //     bullet->collision(*player);
        // }
    }

    for (auto &immoveable : _immoveable) {
        // for (auto &bullet : _bullet) {
        //     immoveable->collision(*bullet);
        // }
        for (auto &moveable : _moveable) {
            immoveable->collision(*moveable);
        }
    }

    // for (auto &bullet : _bullet) {
    //     for (auto &moveable : _moveable) {
    //         bullet->collision(*moveable);
    //     }
    // }

    for (size_t i = 0; i < _players.size(); ++i) {
        sf::Vector2f position = _players[i]->get_position();  // TODO(ANDY) обновление status (после реализации angle в Entity)

        if (position.x > MAP_SIZE) {
            _players[i]->set_x(position.x - MAP_SIZE);
        }
        if (position.x < 0) {
            _players[i]->set_x(position.x + MAP_SIZE);
        }
        if (position.y > MAP_SIZE) {
            _players[i]->set_y(position.y - MAP_SIZE);
        }
        if (position.y < 0) {
            _players[i]->set_y(position.y + MAP_SIZE);
        }

        _status[static_cast<size_t>(StatusLay::PLAYER)][i] = to_status(*_players[i]);
    }

    for (size_t i = 0; i < _moveable.size(); ++i) {
        _status[static_cast<size_t>(StatusLay::MOVEABLE)][i] = to_status(*_moveable[i]);
        _status[static_cast<size_t>(StatusLay::MOVEABLE)][i].id += _player_count;
    }

    for (size_t i = 0; i < _immoveable.size(); ++i) {
        _status[static_cast<size_t>(StatusLay::IMMOVEABLE)][i] = to_status(*_immoveable[i]);
    }
}

bool World::is_over() {
    // for (auto &it : _players) {
    //     if (it->get_hp() > 0) {
    //         return true;
    //     }
    // }
    // return false;
    return true;  // TODO(ANDY) убрать заглушку
}

void World::push_player(std::unique_ptr<engine::MoveAble> player) {
    _players.push_back(std::move(player));
    Status status = to_status(dynamic_cast<engine::Entity&>(*_players.back()));
    _status[static_cast<size_t>(StatusLay::PLAYER)].push_back(status);
}

void World::push_back(std::unique_ptr<engine::MoveAble> moveable) {
    _moveable.push_back(std::move(moveable));
    Status status = to_status(dynamic_cast<engine::Entity&>(*_moveable.back()));
    _status[static_cast<size_t>(StatusLay::MOVEABLE)].push_back(status);
}

void World::push_back(std::unique_ptr<engine::ImmoveAble> immoveable) {
    _immoveable.push_back(std::move(immoveable));
    Status status = to_status(dynamic_cast<engine::Entity&>(*_immoveable.back()));
    _status[static_cast<size_t>(StatusLay::IMMOVEABLE)].push_back(status);
}

// void World::push_back(std::unique_ptr<engine::Bullet> bullet) {
//     _bullet.push_back(std::move(bullet));
//     Status status = to_status(dynamic_cast<engine::Entity&>(*_bullet.back()));
//     _status.push_back(status);
// }

// void World::push_back(std::unique_ptr<engine::Entity> object) {
//     _objects.push_back(std::move(object));
//     Status status = to_status(dynamic_cast<engine::Entity&>(*_objects.back()));
//     _status.push_back(status);
// }

void World::do_action(size_t id, Player::Action action, sf::Time d_time) {  // TODO(ANDY) переписать на таблицу Command
    if (_status[static_cast<size_t>(StatusLay::PLAYER)][id].is_removed) {
        return;
    }
    auto &ship = dynamic_cast<space::Ship&>(*_players[id]);

    switch (action) {
    case Player::Action::MOVE_FORWARD:
        ship.give_acceleration(Direction::FORWARD);
        break;
    case Player::Action::MOVE_BACKWARD:
        ship.give_acceleration(Direction::BACKWARD);
        break;
    case Player::Action::MOVE_LEFT:
        ship.rotate(engine::as_radian(- 90.0) * d_time.asSeconds());
        break;
    case Player::Action::MOVE_RIGHT:
        ship.rotate(engine::as_radian(90.0) * d_time.asSeconds()); 
        break;

    default:
        break;
    }
}

std::vector<std::vector<Status>> World::get_status() {
    return _status;
}

std::queue<Player::Action>& World::get_actions() {
    return _actions;
}

void World::set_player_count(size_t player_count) {
    _player_count = player_count;
}
