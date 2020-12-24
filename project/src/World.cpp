#include "World.h"

#include <algorithm>
#include <cassert>
#include <memory>

#include "Ally.h"
#include "Engine.h"
#include "IcePlanet.h"
#include "Layer.h"

static constexpr size_t MAP_SIZE = 10 * 450;  // Криво, но пока надо

enum class StatusLay {
  PLAYER = 0,
  MOVEABLE,
  IMMOVEABLE,
  BULLET,
  ENEMIES,
  COUNT,
};

static Status to_status(engine::Entity const &entity) {
  Status status;
  status.id = entity.get_id();
  status.is_removed = entity.is_destroyed();
  status.animation_id = entity.get_animation_id();
  switch (status.animation_id) {  // TODO(ANDY) переписать на функцию
    case animation::Id::SHIP:
    case animation::Id::BULLET:
    case animation::Id::COMET:
      status.lay_id = static_cast<size_t>(animation::LayerNom::OBJECTS);
      break;
    case animation::Id::ICE_PLANET:
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

World::World() : _player_count(0), _moveable_count(0), _immoveable_count(0) {
  // TODO(SHUREK) чтение карты из файла
  _status.resize(static_cast<size_t>(StatusLay::COUNT));
}

void World::update(sf::Time d_time) {
  while (!_actions.empty()) {
    do_action(_actions.front().first, _actions.front().second, d_time);
    _actions.pop();
  }

  for (auto &it : _players) {
    it->update(d_time);
  }

  for (auto &it : _moveable) {
    it->update(d_time);
  }

  for (auto &it : _immoveable) {
    it->update(d_time);
  }

  for (auto &it : _bullet) {
    it->update(d_time);
  }

  for (auto &it : _enemies) {
    it->update(d_time);
  }

  for (auto &player : _players) {
    for (auto &moveable : _moveable) {
      // player->collision(*moveable); just wrong
      moveable->collision(*player);
      moveable->trigger(*player);
    }

    for (auto &immoveable : _immoveable) {
      immoveable->collision(*player);
      immoveable->trigger(*player);
    }

    for (auto &bullet : _bullet) {
      bullet->collision(*player);
    }

    for (auto &enemy : _enemies) {
      player->collision(*enemy);  //
      // enemy->collision(*player);
      enemy->trigger(*player);
    }
  }

  for (size_t i = 0; i < _enemies.size(); ++i) {
    for (size_t j = i; i < _enemies.size(); ++i) {
      _enemies[i]->collision((engine::MoveAble &)_enemies[j]);
    }
  }

  for (size_t i = 0; i < _players.size(); ++i) {
    for (size_t j = i; j < _players.size(); ++j) {
      _players[i]->collision((engine::MoveAble &)_players[j]);
    }
  }

  for (auto &immoveable : _immoveable) {
    for (auto &bullet : _bullet) {
      if (auto tmp = dynamic_cast<space::IcePlanet *>(immoveable.get())) {
        tmp->collision(*bullet);
      } else {
        immoveable->collision(*bullet);
      }
      immoveable->trigger(*bullet);
    }
    for (auto &moveable : _moveable) {
      immoveable->collision(*moveable);
      immoveable->trigger(*moveable);
    }
    for (auto &enemy : _enemies) {
      immoveable->collision(*enemy);
      immoveable->trigger(*enemy);
    }
  }

  for (auto &bullet : _bullet) {
    for (auto &moveable : _moveable) {
      bullet->collision(*moveable);
      // moveable->collision(*bullet);
    }
    for (auto &enemy : _enemies) {
      bullet->collision(*enemy);
    }
  }

  for (auto &enemy : _enemies) {
    push_back(enemy->fire());
  }

  for (size_t i = 0; i < _players.size(); ++i) {
    portal(*_players[i]);
    _status[static_cast<size_t>(StatusLay::PLAYER)][i] =
        to_status(*_players[i]);
  }

  for (size_t i = 0; i < _bullet.size(); ++i) {
    portal(*_bullet[i]);
    _status[static_cast<size_t>(StatusLay::BULLET)][i] = to_status(*_bullet[i]);
  }

  for (size_t i = 0; i < _moveable.size(); ++i) {
    portal(*_moveable[i]);
    _status[static_cast<size_t>(StatusLay::MOVEABLE)][i] =
        to_status(*_moveable[i]);
  }

  for (size_t i = 0; i < _enemies.size(); ++i) {
    portal(*_enemies[i]);
    _status[static_cast<size_t>(StatusLay::ENEMIES)][i] =
        to_status(*_enemies[i]);
  }

  for (size_t i = 0; i < _immoveable.size(); ++i) {
    _status[static_cast<size_t>(StatusLay::IMMOVEABLE)][i] =
        to_status(*_immoveable[i]);
  }
}

bool World::is_over() {
  // for (auto &it : _players) {
  //     if (it->get_hp() > 0) {
  //         return true;
  //     }
  // }
  // return false;
  return false;  // TODO(ANDY) убрать заглушку
}

void World::push_player(std::unique_ptr<engine::MoveAble> player) {
  if (player == nullptr) {
    return;
  }

  player->set_id(_player_count++);
  Status status = to_status(dynamic_cast<engine::Entity &>(*player));
  _status[static_cast<size_t>(StatusLay::PLAYER)].push_back(status);
  _players.push_back(std::move(player));
}

void World::push_back(std::unique_ptr<engine::MoveAble> moveable) {
  if (moveable == nullptr) {
    return;
  }

  moveable->set_id(_player_count + _moveable_count++);
  Status status = to_status(dynamic_cast<engine::Entity &>(*moveable));
  _status[static_cast<size_t>(StatusLay::MOVEABLE)].push_back(status);
  _moveable.push_back(std::move(moveable));
}

void World::push_back(std::unique_ptr<engine::ImmoveAble> immoveable) {
  if (immoveable == nullptr) {
    return;
  }

  immoveable->set_id(_immoveable_count++);
  Status status = to_status(dynamic_cast<engine::Entity &>(*immoveable));
  _status[static_cast<size_t>(StatusLay::IMMOVEABLE)].push_back(status);
  _immoveable.push_back(std::move(immoveable));
}

void World::push_back(std::unique_ptr<space::Bullet> bullet) {
  if (bullet == nullptr) {
    return;
  }

  bullet->set_id(_player_count + _moveable_count++);
  Status status = to_status(dynamic_cast<engine::Entity &>(*bullet));
  _status[static_cast<size_t>(StatusLay::BULLET)].push_back(status);
  _bullet.push_back(std::move(bullet));
}

void World::push_back(std::unique_ptr<space::Enemy> enemy) {
  if (enemy == nullptr) {
    return;
  }

  enemy->set_id(_player_count + _moveable_count++);
  Status status = to_status(dynamic_cast<engine::Entity &>(*enemy));
  _status[static_cast<size_t>(StatusLay::ENEMIES)].push_back(status);
  _enemies.push_back(std::move(enemy));
}

void World::do_action(
    size_t id, Player::Action action,
    sf::Time d_time) {  // TODO(ANDY) переписать на таблицу Command
  if (_status[static_cast<size_t>(StatusLay::PLAYER)][id].is_removed) {
    return;
  }
  auto &ship = dynamic_cast<space::Ally &>(*_players[id]);

  switch (action) {
    case Player::Action::MOVE_FORWARD:
      ship.give_acceleration(Direction::FORWARD);
      break;
    case Player::Action::MOVE_BACKWARD:
      ship.give_acceleration(Direction::BACKWARD);
      break;
    case Player::Action::MOVE_LEFT:
      ship.rotate(engine::as_radian(-90.0) * d_time.asSeconds());
      break;
    case Player::Action::MOVE_RIGHT:
      ship.rotate(engine::as_radian(90.0) * d_time.asSeconds());
      break;
    case Player::Action::FIRE:
      push_back(std::move(ship.fire()));
      break;
    default:
      break;
  }
}

std::vector<std::vector<Status>> World::get_status() { return _status; }

std::queue<std::pair<size_t, Player::Action>> &World::get_actions() {
  return _actions;
}

void World::set_player_count(size_t player_count) {
  _player_count = player_count;
}

void World::portal(engine::MoveAble &moveable) {
  sf::Vector2f position =
      moveable.get_position();  // TODO(ANDY) обновление status (после
                                // реализации angle в Entity)

  if (position.x > MAP_SIZE) {
    moveable.set_x(position.x - MAP_SIZE);
  }
  if (position.x < 0) {
    moveable.set_x(position.x + MAP_SIZE);
  }
  if (position.y > MAP_SIZE) {
    moveable.set_y(position.y - MAP_SIZE);
  }
  if (position.y < 0) {
    moveable.set_y(position.y + MAP_SIZE);
  }
}
