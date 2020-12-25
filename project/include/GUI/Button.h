#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "Component.h"
#include "Holder.h"

namespace GUI {

class Button : public Component {
 public:
  typedef std::shared_ptr<Button> Ptr;
  typedef std::function<void()> Callback;

 public:
  Button(const fonts::Holder &fonts, const textures::Holder &textures);

  void set_callback(Callback callback);
  void set_text(const std::string &text);
  void set_toggle(bool flag);

  virtual bool is_selectable() const;
  virtual void select();
  virtual void deselect();

  virtual void activate();
  virtual void deactivate();

  virtual void handle_event(const sf::Event &event);

 private:
  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

 private:
  Callback _callback;
  sf::RectangleShape _background;
  const sf::Texture *_normal;
  const sf::Texture *_selected;
  const sf::Texture *_pressed;
  sf::Text _text;
  bool _is_toggle;
};
}  // namespace GUI
