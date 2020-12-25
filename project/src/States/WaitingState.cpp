#include "WaitingState.h"

#include <memory>
#include "Button.h"
#include "Utility.h"
#include "Holder.h"

WaitingState::WaitingState(StateStack& stack, Context context)
            : State(stack, context) {
    const sf::Texture* texture = context.textures->get(textures::Id::MENU_BACKGROUND);
    _background.setTexture(texture);
    sf::Vector2u size = context.window->getSize();
    sf::Vector2f menu_size;
    menu_size.x = size.x * 1.f;
    menu_size.y = size.y * 1.f;
    _background.setSize(menu_size);
    _background.setPosition(0, 0);

    const sf::Font* font = context.fonts->get(fonts::Id::MAIN);
    _text.setFont(*font);
    _text.setString("Waiting start...");
    centerOrigin(_text);
    _text.setPosition(context.window->getView().getSize() / 2.f);
    _text_effect = sf::Time::Zero;
}

bool WaitingState::update(sf::Time dt) {
    if (getContext().client->is_game_started()) {
        requestStackPop();
        requestStackPush(States::Id::ONLINE);
    }

    _text_effect += dt;

    if (_text_effect >= sf::seconds(0.5f)) {
        _is_showing = !_is_showing;
        _text_effect = sf::Time::Zero;
    }

    return true;
}

void WaitingState::draw() {
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    window.draw(_background);

    if (_is_showing) {
        window.draw(_text);
    }
}

bool WaitingState::handle_event(const sf::Event&) {
    return false;
}
