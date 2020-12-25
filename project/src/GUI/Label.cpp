#include "Label.h"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "Utility.h"

namespace GUI {

Label::Label(const std::string& text, const fonts::Holder& fonts)
    : _text(text, *fonts.get(fonts::Id::MAIN), 16) {}

bool Label::is_selectable() const { return false; }

void Label::handle_event(const sf::Event&) {}

void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getTransform();
  target.draw(_text, states);
}

void Label::set_text(const std::string& text) { _text.setString(text); }

}  // namespace GUI
