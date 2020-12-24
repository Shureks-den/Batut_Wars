#include "Layer.h"

namespace animation {

void Layer::update(sf::Time dt) {
  for (auto &it : _manager) {
    it->update(dt);  // TODO(ANDY) возможность удаления
  }
}

void Layer::draw(sf::RenderWindow &window) {
  for (auto &it : _manager) {
    it->draw(window);
  }
}

size_t Layer::push_back(std::unique_ptr<Manager> manager) {
  if (manager == nullptr) {
    return 0;
  }
  _manager.push_back(std::move(manager));
  return _manager.size() - 1;
}

Manager &Layer::operator[](const int index) { return *_manager[index]; }

size_t Layer::get_size() const { return _manager.size(); }

void Layer::erase(size_t) {
  // TODO(ANDY) реализовать после замены на список
}

}  // namespace animation
