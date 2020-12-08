#include "Render.h"

#include <vector>

#include "Aship.h"

static const size_t MAP_SIZE = 2000;  // Криво, но пока надо

Render::Render(sf::RenderWindow& window)
    : _window(window) {
    _view.setSize(640, 480);

    _animation_layers.resize(static_cast<size_t>(animation::LayerNom::COUNT));

    animation::Space space(sf::Vector2f(0, 0), 0);
    size_t width = space.get_size().x;
    size_t height = space.get_size().y;
    _extra_size.x = _view.getSize().x / 2;
    _extra_size.y = _view.getSize().y / 2;
    size_t x_count = ((MAP_SIZE + _extra_size.x) / width + 1) * 2;
    size_t y_count = ((MAP_SIZE + _extra_size.y) / height + 1) * 2;

    for (size_t i = 0; i <= x_count; ++i) {  // TODO(ANDY) размерность карты
        for (size_t j = 0; j <= y_count; ++j) {
            space.set_position(sf::Vector2f(i * width, j * height));
            _animation_layers[0].push_back(space);
        }
    }
}

void Render::draw() {
    for (auto &it : _animation_layers) {
        it.draw(_window);
    }
}

void Render::update(sf::Time dt) {
    for (auto &it : _status) {
        if (it.id == _player_id) {
            _view.setCenter(it.position);
        }
    }
    // _view.setCenter(_status[_player_id].position);
    _window.setView(_view);
    for (auto &it : _animation_layers) {
        it.update(dt);
    }
}

void Render::inicilize(const std::vector<Status> &status) {
    _status.assign(status.begin(), status.end());
    for (size_t i = 0; i < status.size(); ++i) {
        _status[i].position += _extra_size;
    }

    for (auto &it : _status) {
        if (it.id == _player_id) {
            _view.setCenter(it.position);
        }
    }
    // _view.setCenter(_status[_player_id].position);
    build_scene();
}

void Render::build_scene() {
    for (auto &it : _status) {
        animation::Manager *added;
        switch (it.animation_id) {
        case animation::Id::SHIP:
            added = new animation::Ship(it.position, it.angle);
            _animation_layers[it.lay_id].push_back(*added);
            break;

        default:
            break;
        }
    }
}

void Render::set_status(const std::vector<Status> &status) {
    for (size_t i = 0; i < _status.size(); ++i) {  // TODO(ANDY) Ломается при удалении. Переписать на list
        size_t lay = status[i].lay_id;
        size_t id = status[i].id;
        if (status[i].is_removed) {
            _status.erase(status.begin() + i);
            _animation_layers[lay].erase(id);
            continue;
        }


        _status[i].states = status[i].states;
        _animation_layers[lay][id].set_states(_status[i].states);

        _status[i].angle = status[i].angle;
        _animation_layers[lay][id].set_angle(status[i].angle);

        _status[i].position = status[i].position + _extra_size;
        _animation_layers[lay][id].set_position(_status[i].position);
    }

    for (size_t i = _status.size(); i < status.size(); ++i) {
        _status.push_back(status[i]);
        _status[i].position += _extra_size;
    }
}

void Render::add_animation(size_t lay, Status &status) {
    animation::Manager added(_holder.get_texture(status.animation_id), status.position, status.angle);
    _animation_layers[lay].push_back(added);
}

sf::View& Render::get_view() {
    return _view;
}

void Render::set_player_id(size_t id) {
    _player_id = id;
}
