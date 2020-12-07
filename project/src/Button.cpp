#include "Button.h"
#include "Utility.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


namespace GUI {

    Button::Button(const fonts::Holder& fonts, const textures::Holder& textures)
            : _Callback()
            , _NormalTexture(*textures.get(textures::Id::BUTTON_NORMAL))
            , _SelectedTexture(*textures.get(textures::Id::BUTTON_SELECTED))
            , _PressedTexture(*textures.get(textures::Id::BUTTON_PRESSED))
            , _Sprite()
            , _Text("", *fonts.get(fonts::Id::MAIN), 16)
            , _IsToggle(false)
    {
        _Sprite.setTexture(_NormalTexture);

        sf::FloatRect bounds = _Sprite.getLocalBounds();
        _Text.setPosition(bounds.width / 2.f, bounds.height / 2.f);
    }

    void Button::setCallback(Callback callback)
    {
        _Callback = std::move(callback);
    }

    void Button::setText(const std::string& text)
    {
        _Text.setString(text);
        centerOrigin(_Text);
    }

    void Button::setToggle(bool flag)
    {
        _IsToggle = flag;
    }

    bool Button::isSelectable() const
    {
        return true;
    }

    void Button::select()
    {
        Component::select();

        _Sprite.setTexture(_SelectedTexture);
    }

    void Button::deselect()
    {
        Component::deselect();

        _Sprite.setTexture(_NormalTexture);
    }

    void Button::activate()
    {
        Component::activate();

        // If we are toggle then we should show that the button is pressed and thus "toggled".
        if (_IsToggle)
            _Sprite.setTexture(_PressedTexture);

        if (_Callback)
            _Callback();

        // If we are not a toggle then deactivate the button since we are just momentarily activated.
        if (!_IsToggle)
            deactivate();
    }

    void Button::deactivate()
    {
        Component::deactivate();

        if (_IsToggle)
        {
            // Reset texture to right one depending on if we are selected or not.
            if (isSelected())
                _Sprite.setTexture(_SelectedTexture);
            else
                _Sprite.setTexture(_NormalTexture);
        }
    }

    void Button::handleEvent(const sf::Event&) {
    }

    void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        target.draw(_Sprite, states);
        target.draw(_Text, states);
    }

}
