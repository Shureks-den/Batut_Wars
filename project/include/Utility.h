#pragma once

#include <SFML/Window/Keyboard.hpp>

#include <sstream>
#include <cmath>

namespace sf {
    class Sprite;
    class Text;
}

void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);
std::string toString(sf::Keyboard::Key key);

