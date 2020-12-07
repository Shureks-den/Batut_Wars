#include "MenuState.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include "Button.h"
#include "Utility.h"
#include "Holder.h"

MenuState::MenuState(StateStack& stack, Context context)
          : State(stack, context),
           _container() {
    const sf::Texture* texture = context.textures->get(textures::Id::MENU_BACKGROUND);
    _background.setTexture(*texture);

    auto play_button = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    sf::Vector2u size = context.window->getSize();
    play_button->setPosition(size.x / 2, size.y / 2);  // TODO(ANDY) размеры
    play_button->set_text("Play");
    play_button->set_callback([this] () {
        requestStackPop();
        requestStackPush(States::GAME);
    });

    auto settings_button = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    settings_button->setPosition(size.x / 2, size.y / 2 + 40);
    settings_button->set_text("Settings");
    settings_button->set_callback([this] () {
        requestStackPush(States::SETTINGS);
    });

    auto exit_button = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    exit_button->setPosition(size.x / 2, size.y / 2 + 80);
    exit_button->set_text("Exit");
    exit_button->set_callback([this] () {
        requestStackPop();
    });

    _container.pack(play_button);
    _container.pack(settings_button);
    _container.pack(exit_button);
}

void MenuState::draw() {
    sf::RenderWindow& window = *getContext().window;

    window.draw(_background);
    window.draw(_container);
}

bool MenuState::update(sf::Time) {
    return true;
}

bool MenuState::handle_event(const sf::Event& event) {
    _container.handle_event(event);
    return false;
}
