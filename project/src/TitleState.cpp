#include "TitleState.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Utility.h"
#include "Holder.h"


TitleState::TitleState(StateStack& stack, Context context)
           : State(stack, context),
            _text(),
            _ShowText(true),
            _textEffectTime(sf::Time::Zero) {
    _background.setTexture(*context.textures->get(textures::Id::MENU_BACKGROUND));

    _text.setFont(*context.fonts->get(fonts::Id::MAIN));
    _text.setString("Loading...");
    centerOrigin(_text);
    _text.setPosition(context.window->getView().getSize() / 2.f);
}

void TitleState::draw() {
    sf::RenderWindow& window = *getContext().window;
    window.draw(_background);

    if (_ShowText) {
        window.draw(_text);
    }
}

bool TitleState::update(sf::Time dt) {
    _textEffectTime += dt;

    if (_textEffectTime >= sf::seconds(0.5f)) {
        _ShowText = !_ShowText;
        _textEffectTime = sf::Time::Zero;
    }

    return true;
}

bool TitleState::handle_event(const sf::Event &event) {
    if (event.type == sf::Event::KeyReleased) {
        requestStackPop();
        requestStackPush(States::MENU);
    }

    return true;
}
