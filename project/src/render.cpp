#include "render.h"

void Render::draw() {
    for (auto &it : _manager) {
        it.draw(_window);
    }
}

void Render::update(sf::Time dt) {
    for (auto &it : _manager) {
        it.update(dt);
    }
}