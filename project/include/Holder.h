#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <cassert>
#include <memory>
#include <stdexcept>
#include <vector>

#include "Animation.h"
#include "Identificators.h"

namespace animation {

class Holder {
 public:
  Holder();
  ~Holder() = default;
  const sf::Texture* get(Id id) const;

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

namespace sounds {

class Holder {
 public:
  Holder();
  ~Holder() = default;
  const sf::SoundBuffer* get(Id id) const;

 private:
  std::vector<sf::SoundBuffer> _resource_map;
};

}
