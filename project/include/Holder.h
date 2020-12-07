#pragma once

#include <memory>
#include <stdexcept>
#include <cassert>
#include <vector>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

#include "Identificators.h"

namespace animation {

class Holder {
 public:
    Holder();
    ~Holder() = default;
    const sf::Texture* get_texture(Id id) const;

 private:
    std::vector<sf::Texture> _resource_map;
};

}  // namespace animation

namespace fonts {

class Holder {
 public:
    Holder();
    ~Holder() = default;
    const sf::Font* get(Id id) const;

 private:
    std::vector<sf::Font> _resource_map;
};

}  // namespace fonts

namespace textures {

class Holder {
 public:
    Holder();
    ~Holder() = default;
    const sf::Texture* get(Id id) const;

 private:
      std::vector<sf::Texture> _resource_map;
};

}  // namespace textures
