#pragma once

#include <memory>
#include <vector>

#include "Component.h"

namespace GUI {
class Container : public Component {
 public:
  typedef std::shared_ptr<Container> Ptr;

 public:
  Container();

  void pack(Component::Ptr component);

  virtual bool is_selectable() const;
  virtual void handle_event(const sf::Event& event);
  Component::Ptr& operator[](const size_t index);

 private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  bool has_selection() const;
  void select(size_t index);
  void select_next();
  void select_previous();

 private:
  std::vector<Component::Ptr> _children;
  int _selected_child;
};
}  // namespace GUI
