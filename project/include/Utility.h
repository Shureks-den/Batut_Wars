#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <sstream>
#include <string>

namespace sf {
class Sprite;
class Text;
}  // namespace sf

void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);
std::string toString(sf::Keyboard::Key key);
