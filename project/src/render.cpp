#include "render.h"

#include <vector>

Render::Render(sf::RenderWindow& window)
    : _window(window) {
    _animation_layers.resize(static_cast<size_t>(animation::LayerNom::COUNT));
}

void Render::draw() {
    for (auto &it : _animation_layers) {
        it.draw(_window);
    }
}

void Render::update(sf::Time dt) {
    for (auto &it : _animation_layers) {
        it.update(dt);
    }
}

void Render::inicilize_status(std::vector<Status> &status) {
    _status = status;
    _view.setCenter(_status[0].position);  // TODO(ANDY) вместо 0 - id данного игрока
}

void Render::build_scene() {
    for (auto &it : _status) {
        animation::AnimationManager added(it.animation_id, it.position, it.angle);  // Вероятно, ResourceHolder должен быть тут
        _animation_layers[it.lay_id].push_back(added);
    }
}

void Render::set_status(std::vector<Status> &status) {
    for (size_t i = 0; i < status.size(); ++i) {  // TODO(ANDY) Ломается при удалении. Переписать на list
        size_t lay = _status[i].lay_id;
        size_t id = status[i].id;
        if (status[i].is_removed) {
            _status.erase(status.begin() + i);
            _animation_layers[lay].erase(id);
            continue;
        }

        if (_status[i].states != status[i].states) {
            _status[i].states = status[i].states;
            _animation_layers[lay][id].set_states(_status[i].states);
        }

        if (_status[i].angle != status[i].angle) {
            _status[i].angle = status[i].angle;
            _animation_layers[lay][id].set_angle(status[i].angle);
        }
        
        if (_status[i].position != status[i].position) {
            _status[i].position = status[i].position;
            _animation_layers[lay][id].set_position(status[i].position);
        }
    }

    for (size_t i = status.size(); i < _status.size(); ++i) {
        status.push_back(_status[i]);


    }
}

void Render::add_animation(size_t lay, Status &status) {
    animation::AnimationManager added(status.animation_id, status.position, status.angle);
    _animation_layers[lay].push_back(added);
}
