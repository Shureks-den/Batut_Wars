#include "layer.h"

namespace animation {

void Layer::update(sf::Time dt) {
    for (auto &it : _manager) {
        it.update(dt);
    }
}

void Layer::draw(sf::RenderWindow &window) {
    for (auto &it : _manager) {
        it.draw(window);
    }
}

size_t Layer::push_back(AnimationManager &added) {
    _manager.push_back(added);
    return _manager.size() - 1;
}

AnimationManager& Layer::operator[] (const int index) {
    return _manager[index];
}

}  // namespace animation
