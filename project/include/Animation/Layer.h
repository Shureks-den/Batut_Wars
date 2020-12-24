#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Animation.h"

namespace animation {

enum class LayerNom { BACKGROUND = 0, OBJECTS, PLANETS, EFFECTS, COUNT };

class Layer {
 public:
  Layer() = default;
  ~Layer() = default;
  void update(sf::Time dt);
  void draw(sf::RenderWindow &window);
  size_t push_back(std::unique_ptr<Manager> manager);
  void erase(size_t id);  // TODO(ANDY) реализовать после замены на список
  Manager &operator[](const int index);
  size_t get_size() const;

 private:
  // std::vector<Manager> _manager;
  std::vector<std::unique_ptr<Manager>> _manager;
};

}  // namespace animation
