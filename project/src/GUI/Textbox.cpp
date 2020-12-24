#include "Textbox.h"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

#include "Utility.h"

namespace GUI {

Textbox::Textbox(const fonts::Holder& fonts, const textures::Holder& textures)
    : _callback(),
      _normal(textures.get(textures::Id::BUTTON_NORMAL)),
      _selected(textures.get(textures::Id::BUTTON_SELECTED)),
      _pressed(textures.get(textures::Id::BUTTON_PRESSED)),
      _is_toggle(false),
      _text("", *fonts.get(fonts::Id::MAIN), 16) {
  _background.setTexture(_normal);
  _background.setSize(sf::Vector2f(200, 50));
  _text.setPosition(100, 25);
}

void Textbox::set_callback(Callback callback) {
  _callback = std::move(callback);
}

void Textbox::set_toggle(bool flag) { _is_toggle = flag; }

void Textbox::set_string(const std::string& string) {
  _string = string;
  _text.setString(_opening + _string);
  centerOrigin(_text);
}

void Textbox::set_opening(std::string string) {
  _opening = string;
  _text.setString(_opening + _string);
  centerOrigin(_text);
}

bool Textbox::is_selectable() const { return true; }

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

  if (_is_toggle) {
    _background.setTexture(_selected);
  }
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

void Textbox::handle_event(const sf::Event& event) {
  if (event.type == sf::Event::KeyReleased && event.text.unicode == 13) {
    deactivate();
    return;
  }

  if (event.type != sf::Event::TextEntered) {
    return;
  }

  if (event.text.unicode == 8) {
    if (_string.size() != 0) {
      _string.pop_back();
    }
  } else if ((event.text.unicode >= 48 && event.text.unicode <= 58) ||
             event.text.unicode == 46) {
    _string.push_back(static_cast<char>(event.text.unicode));
  }

  _text.setString(_opening + _string);
  centerOrigin(_text);
}

std::string Textbox::get_text() { return _string; }

void Textbox::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getTransform();
  target.draw(_background, states);
  target.draw(_text, states);
}

}  // namespace GUI