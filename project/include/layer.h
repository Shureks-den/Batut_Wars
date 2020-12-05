#pragma once

#include <SFML/Graphics.hpp>

#include "animation.h"

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
    size_t push_back(const AnimationManager &added);
    void erase(size_t id);  // TODO(ANDY) реализовать после замены на список
    AnimationManager& operator[] (const int index);

 private:
    std::vector<AnimationManager> _manager;
};

}  // namespace animation
