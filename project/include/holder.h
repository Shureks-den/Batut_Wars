#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <cassert>
#include <memory>
#include <stdexcept>

#include "status.h"

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
