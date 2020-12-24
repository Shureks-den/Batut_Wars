#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>

namespace GUI {

class Component : public sf::Drawable,
                  public sf::Transformable,
                  private sf::NonCopyable {
 public:
  typedef std::shared_ptr<Component> Ptr;

 public:
  Component();
  virtual ~Component() = default;
  virtual bool is_selectable() const = 0;
  bool is_selected() const;
  virtual void select();
  virtual void deselect();

  virtual bool is_active() const;
  virtual void activate();
  virtual void deactivate();

  virtual void handle_event(const sf::Event& event) = 0;

 private:
  bool _is_selected;
  ;
  bool _is_active;
};
}  // namespace GUI
