#include "States/TitleState.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Holder.h"
#include "Utility.h"

TitleState::TitleState(StateStack& stack, Context context)
           : State(stack, context),
            _text(),
            _is_showing(true),
            _text_effect(sf::Time::Zero) {
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
    _text.setString("Press any key to continue");
    centerOrigin(_text);
    _text.setPosition(context.window->getView().getSize() / 2.f);
}

void TitleState::draw() {
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    window.draw(_background);

    if (_is_showing) {
        window.draw(_text);
    }
}

bool TitleState::update(sf::Time dt) {
    _text_effect += dt;

    if (_text_effect >= sf::seconds(0.5f)) {
        _is_showing = !_is_showing;
        _text_effect = sf::Time::Zero;
    }

  return true;
}

bool TitleState::handle_event(const sf::Event& event) {
  if (event.type == sf::Event::KeyReleased) {
    requestStackPop();
    requestStackPush(States::MENU);
  }

  return true;
}
