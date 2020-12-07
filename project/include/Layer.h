#pragma once

#include <SFML/Graphics.hpp>

#include "Animation.h"

namespace animation {

enum class LayerNom {
    BACKGROUND = 0,
    OBJECTS,
    EFFECTS,
    COUNT
};

class Layer {
 public:
    Layer() = default;
    ~Layer() = default;
    void update(sf::Time dt);
    void draw(sf::RenderWindow &window);
    size_t push_back(const Manager &added);
    void erase(size_t id);  // TODO(ANDY) реализовать после замены на список
    Manager& operator[] (const int index);

 private:
    std::vector<Manager> _manager;
};

}  // namespace animation
