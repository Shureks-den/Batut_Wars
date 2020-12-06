#ifndef BOOK_STRINGHELPERS_HPP
#define BOOK_STRINGHELPERS_HPP

#include <SFML/Window/Keyboard.hpp>

#include <sstream>
#include <cmath>

namespace sf {
    class Sprite;
    class Text;
}

void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);

#endif // BOOK_STRINGHELPERS_HPP
