#pragma once

#include <SFML/Graphics/Text.hpp>
#include <memory>
#include <string>

#include "Component.h"
#include "Holder.h"

namespace GUI {

class Label : public Component {
 public:
  typedef std::shared_ptr<Label> Ptr;

 public:
  Label(const std::string& text, const fonts::Holder& fonts);

  virtual bool is_selectable() const;
  void set_text(const std::string& text);

  virtual void handle_event(const sf::Event& event);

 private:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const;

 private:
  sf::Text _text;
};

}  // namespace GUI
