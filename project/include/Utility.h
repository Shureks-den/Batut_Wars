#pragma once

#include <sstream>
#include <cmath>
#include <string>

#include <SFML/Window/Keyboard.hpp>

namespace sf {
class Sprite;
class Text;
}  // namespace sf

void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);
std::string toString(sf::Keyboard::Key key);
