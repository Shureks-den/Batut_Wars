#include "layer.h"

namespace animation {

void Layer::update(sf::Time dt) {
  for (auto &it : _manager) {
    it.update(dt);  // TODO(ANDY) возможность удаления
  }
}

void Layer::draw(sf::RenderWindow &window) {
  for (auto &it : _manager) {
    it.draw(window);
  }
}

size_t Layer::push_back(const Manager &added) {
  _manager.push_back(added);
  return _manager.size() - 1;
}

Manager &Layer::operator[](const int index) { return _manager[index]; }

void Layer::erase(size_t id) {
  for (size_t i = 0; i < id; ++i) {
    id = 3;
  }  // TODO(ANDY) реализовать после замены на список
}

}  // namespace animation
