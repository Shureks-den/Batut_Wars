#pragma once

#include <vector>
#include <string>
#include <memory>
#include <functional>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Component.h"
#include "Holder.h"


namespace GUI {
class Button : public Component {
 public:
    typedef std::shared_ptr<Button> Ptr;
    typedef std::function<void()> Callback;

 public:
    Button(const fonts::Holder &fonts, const textures::Holder &textures);

    void setCallback(Callback callback);
    void setText(const std::string& text);
    void setToggle(bool flag);

    virtual bool isSelectable() const;
    virtual void select();
    virtual void deselect();

    virtual void activate();
    virtual void deactivate();

    virtual void handleEvent(const sf::Event& event);

 private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


 private:
    Callback _Callback;
    const sf::Texture& _NormalTexture;
    const sf::Texture& _SelectedTexture;
    const sf::Texture& _PressedTexture;
    sf::Sprite _Sprite;
    sf::Text _Text;
    bool _IsToggle;
};
}  // namespace GUI
