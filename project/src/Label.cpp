#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "Label.h"
#include "Utility.h"

namespace GUI {

    Label::Label(const std::string& text, const fonts::Holder& fonts)
            : _Text(text, *fonts.get(fonts::Id::MAIN), 16) {
    }

    bool Label::isSelectable() const {
        return false;
    }

    void Label::handleEvent(const sf::Event&) {
    }

    void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        target.draw(_Text, states);
    }

    void Label::setText(const std::string& text) {
        _Text.setString(text);
    }

}  // namespace GUI
