#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "Component.h"
#include "Holder.h"

namespace GUI {

class Textbox : public Component {
 public:
  typedef std::shared_ptr<Textbox> Ptr;
  typedef std::function<void()> Callback;

 public:
  Textbox(const fonts::Holder &fonts, const textures::Holder &textures);
  virtual bool is_selectable() const;

  void set_toggle(bool flag);
  void set_opening(std::string string);
  void set_string(const std::string &string);
  void set_callback(Callback callback);
  std::string get_text();

  virtual void select();
  virtual void deselect();

  virtual void activate();
  virtual void deactivate();

  void handle_event(const sf::Event &event) override;

 private:
  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

 private:
  Callback _callback;
  sf::RectangleShape _background;
  const sf::Texture *_normal;
  const sf::Texture *_selected;
  const sf::Texture *_pressed;
  bool _is_toggle;

  sf::Text _text;
  std::string _string;
  std::string _opening;
};

}  // namespace GUI
