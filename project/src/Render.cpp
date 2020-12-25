#include "Render.h"

#include <array>
#include <cmath>
#include <vector>

static constexpr size_t MAP_SIZE =
    10 * 450;  // Криво, но пока надо. 450 - размер текстурки космоса

Render::Render(sf::RenderWindow &window) : _window(window) {
  _view.setSize(1280, 960);

  // size_t width = space.get_size().x;
  // size_t height = space.get_size().y;
  size_t width = 450;
  size_t height = 450;
  // _extra_size.x = _view.getSize().x / 2;
  // _extra_size.y = _view.getSize().y / 2;
  _extra_size = sf::Vector2f(450, 450);
  size_t x_count = ((MAP_SIZE + _extra_size.x) / width + 1) * 2;
  size_t y_count = ((MAP_SIZE + _extra_size.y) / height + 1) * 2;

  for (size_t i = 0; i <= 4 * 10; ++i) {
    auto portal = _creator.get_animation(animation::Id::PORTAL);
    portal->set_position(sf::Vector2f(i * width / 4, 0) + _extra_size);
    _animation_layers[static_cast<size_t>(animation::LayerNom::EFFECTS)]
        .push_back(std::move(portal));
  }
  for (size_t i = 0; i <= 4 * 10; ++i) {
    auto portal = _creator.get_animation(animation::Id::PORTAL);
    portal->set_position(sf::Vector2f(i * width / 4, 10 * 450) + _extra_size);
    _animation_layers[static_cast<size_t>(animation::LayerNom::EFFECTS)]
        .push_back(std::move(portal));
  }
  for (size_t i = 0; i <= 4 * 10; ++i) {
    auto portal = _creator.get_animation(animation::Id::PORTAL);
    portal->set_position(sf::Vector2f(0, i * height / 4) + _extra_size);
    _animation_layers[static_cast<size_t>(animation::LayerNom::EFFECTS)]
        .push_back(std::move(portal));
  }
  for (size_t i = 0; i <= 4 * 10; ++i) {
    auto portal = _creator.get_animation(animation::Id::PORTAL);
    portal->set_position(sf::Vector2f(10 * 450, i * height / 4) + _extra_size);
    _animation_layers[static_cast<size_t>(animation::LayerNom::EFFECTS)]
        .push_back(std::move(portal));
  }

  for (size_t i = 0; i <= x_count; ++i) {
    for (size_t j = 0; j <= y_count; ++j) {
      auto space = _creator.get_animation(animation::Id::SPACE);
      space->set_position(sf::Vector2f(i * width, j * height));
      _animation_layers[static_cast<size_t>(animation::LayerNom::BACKGROUND)]
          .push_back(std::move(space));
    }
  }
}

void Render::draw() {
  for (auto &it : _animation_layers) {
    it.draw(_window);
  }
}

void Render::update(sf::Time dt) {
  _view.setCenter(_status[0][_player_id].position);
  _window.setView(_view);
  _sound_player.remove_stopped_sounds();
  _sound_player.set_listener_position(_status[0][_player_id].position);

  for (auto &it : _animation_layers) {
    it.update(dt);
  }
}

void Render::inicilize(const std::vector<std::vector<Status>> &status) {
  _status.assign(status.begin(), status.end());
  for (auto &lay : _status) {
    for (auto &it : lay) {
      it.position += _extra_size;
    }
  }
  _view.setCenter(_status[0][_player_id].position);
  build_scene();
}

void Render::build_scene() {
  for (auto &lay : _status) {
    for (auto &object : lay) {
      auto added = _creator.get_animation(object.animation_id);
      _animation_layers[object.lay_id].push_back(std::move(added));
    }
  }
}

void Render::set_status(const std::vector<std::vector<Status>> &status) {
  for (size_t i = 0; i < _status.size(); ++i) {
    for (size_t j = 0; j < _status[i].size(); ++j) {
      size_t lay = status[i][j].lay_id;
      size_t id = status[i][j].id;
      _status[i][j] = status[i][j];
      _status[i][j].position += _extra_size;

      if (_status[i][j].is_removed) {
        explosion(i, j);
        continue;
      }

      _animation_layers[lay][id].set_states(_status[i][j].states);
      _animation_layers[lay][id].set_angle(status[i][j].angle);
      _animation_layers[lay][id].set_position(_status[i][j].position);

      sound_render(i, j);
    }

    for (size_t j = _status[i].size(); j < status[i].size(); ++j) {
      _status[i].push_back(status[i][j]);
      _status[i][j].position += _extra_size;
      add_animation(_status[i][j].lay_id, _status[i][j]);
      sound_render(i, j);
    }
  }
}

void Render::add_animation(size_t lay, Status &status) {  // lay не нужен
  auto added = _creator.get_animation(status.animation_id);
  added->set_position(status.position);
  added->set_angle(status.angle);
  _animation_layers[lay].push_back(std::move(added));
}

sf::View &Render::get_view() { return _view; }

void Render::set_player_id(size_t id) { _player_id = id; }

void Render::explosion(size_t i, size_t j) {
    size_t lay = _status[i][j].lay_id;
    size_t id = _status[i][j].id;

    if (!_animation_layers[lay][id].is_playing()) {
        return;
    }

    _animation_layers[lay][id].set_playing(false);
    auto explosion = _creator.get_animation(animation::Id::EXPLOSION);
    auto size = _animation_layers[lay][id].get_size();
    float modul = sqrt(size.x * size.x + size.y * size.y);
    size.x = size.y = modul;
    explosion->set_size_s(size);
    explosion->set_position(_status[i][j].position);
    explosion->set_angle(_status[i][j].angle);
    _animation_layers[static_cast<size_t>(animation::LayerNom::EFFECTS)].push_back(std::move(explosion));

    auto radius = _view.getCenter() - _status[i][j].position;
    auto distance = sqrt(radius.x * radius.x + radius.y * radius.y);
    if (distance < _view.getSize().x / 2) {
        _sound_player.play(sounds::Id::EXPOLOSION, _status[i][j].position);
    }
}

void Render::sound_render(size_t i, size_t j) {
    if (_status[i][j].animation_id == animation::Id::ICE_PLANET) {
      if (_status[i][j].states[0]) {
        _sound_player.play(sounds::Id::REFRACTION, _status[i][j].position);
      }
      return;
    }

    if (_status[i][j].animation_id == animation::Id::MF) {
      if (_status[i][j].states[0]) {
        _sound_player.play(sounds::Id::PLAYERFIRE, _status[i][j].position);
      }
      return;
    }

    if (_status[i][j].animation_id == animation::Id::MAUL) {
      if (_status[i][j].states[0]) {
        _sound_player.play(sounds::Id::ENEMYFIRE, _status[i][j].position);
      }
      return;
    }
}
