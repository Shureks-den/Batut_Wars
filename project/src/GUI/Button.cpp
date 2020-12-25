#include "Button.h"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

#include "Utility.h"

namespace GUI {

Button::Button(const fonts::Holder& fonts, const textures::Holder& textures)
    : _callback(),
      _normal(textures.get(textures::Id::BUTTON_NORMAL)),
      _selected(textures.get(textures::Id::BUTTON_SELECTED)),
      _pressed(textures.get(textures::Id::BUTTON_PRESSED)),
      _text("", *fonts.get(fonts::Id::MAIN), 16),
      _is_toggle(false) {
  _background.setTexture(_normal);
  _background.setSize(sf::Vector2f(200, 50));
  _text.setPosition(100, 25);
}

void Button::set_callback(Callback callback) {
  _callback = std::move(callback);
}

void Button::set_text(const std::string& text) {
  _text.setString(text);
  centerOrigin(_text);
}

void Button::set_toggle(bool flag) { _is_toggle = flag; }

bool Button::is_selectable() const { return true; }

void Button::select() {
  Component::select();
  _background.setTexture(_selected);
}

void Button::deselect() {
  Component::deselect();
  _background.setTexture(_normal);
}

void Button::activate() {
  Component::activate();

  if (_is_toggle) {
    _background.setTexture(_pressed);
  }

  if (_callback) {
    _callback();
  }

  if (!_is_toggle) {
    deactivate();
  }
}

void Button::deactivate() {
  Component::deactivate();

  if (_is_toggle) {
    if (is_selected()) {
      _background.setTexture(_selected);
    } else {
      _background.setTexture(_normal);
    }
  }
}

void Button::handle_event(const sf::Event&) {}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getTransform();
  target.draw(_background, states);
  target.draw(_text, states);
}

}  // namespace GUI
