#include "Textbox.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "Utility.h"


namespace GUI {

Textbox::Textbox(const fonts::Holder& fonts, const textures::Holder& textures)
              : _callback(),
              _normal(textures.get(textures::Id::BUTTON_NORMAL)),
              _selected(textures.get(textures::Id::BUTTON_SELECTED)),
              _is_toggle(false),
              _text("", *fonts.get(fonts::Id::MAIN), 16) {
    _background.setTexture(_normal);
    _background.setSize(sf::Vector2f(200, 50));
    _text.setPosition(100, 25);
}

void Textbox::set_callback(Callback callback) {
    _callback = std::move(callback);
}

bool Textbox::is_selectable() const {
    return true;
}

void Textbox::select() {
    Component::select();
    _background.setTexture(_selected);
}

void Textbox::deselect() {
    Component::deselect();
    _background.setTexture(_normal);
}

void Textbox::activate() {
    Component::activate();

    if (_callback) {
        _callback();
    }

    if (!_is_toggle)
        deactivate();
    }

void Textbox::deactivate() {
    Component::deactivate();

    if (_is_toggle) {
        if (is_selected()) {
            _background.setTexture(_selected);
        } else {
            _background.setTexture(_normal);
        }
    }
}

void Textbox::handle_event(const sf::Event&) {}

void Textbox::handle_event(const sf::Event& event, sf::IpAddress *ip) {
    if (event.type == sf::Event::TextEntered) {
            //Обработка ввода
        _textChanged = true ;
        switch (event.text.unicode) {
            case 0xD:  // Return
                _newText += L'\n';
                break ;
            case 0x8:  // Backspace
                if ( !_newText.isEmpty() )
                    _newText.erase(_newText.getSize()-1) ;
                break ;
            default : {
                    _newText += static_cast<wchar_t>(event.text.unicode) ;
            }
        }
    }
    if (event.key.code == sf::Keyboard::Enter) {
        *ip = get_text();
    }
}

void Textbox::setText (const sf::String & str) {
        _text.setString(str);
    }

std::string Textbox::get_text() {
        return _newText;
    }

void Textbox::draw(sf::RenderTarget& target, sf::RenderStates states) const {
     if (_textChanged) {
            const_cast<Textbox*>(this)->setText (_newText);
            _textChanged = false ;
        }
    states.transform *= getTransform();
    target.draw(_background, states);
    target.draw(_text, states);
}
}  // namespace GUI