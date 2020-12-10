#pragma once

#include <vector>
#include <string>
#include <memory>
#include <functional>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Network/IpAddress.hpp>

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

    void set_callback(Callback callback);
    std::string get_text();

    virtual void select();
    virtual void deselect();

    virtual void activate();
    virtual void deactivate();
    void handle_event(const sf::Event& event, sf::IpAddress *ip);
    virtual void handle_event(const sf::Event& event);

    void setText (const sf::String & str);

 private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


 private:
    Callback _callback;
    sf::RectangleShape _background;
    const sf::Texture* _normal;
    const sf::Texture* _selected;
    bool _is_toggle;
  
    sf::Text _text;
    mutable sf::String _newText ;
    mutable bool _textChanged ;
    
};
}  // namespace GUI
