#include "States/PauseState.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include "Button.h"
#include "Holder.h"
#include "Utility.h"

PauseState::PauseState(StateStack& stack, Context context)
        : State(stack, context)
        , _background()
        , _paused_text()
        , _container() {
    getContext().music->setPaused(true);
    const sf::Font* font = context.fonts->get(fonts::Id::MAIN);

    _background.setFillColor(sf::Color(0, 0, 0, 150));
    sf::Vector2u size = context.window->getSize();
    sf::Vector2f position = context.window->getView().getCenter();
    sf::Vector2f menu_size;
    menu_size.x = size.x * 1.f;
    menu_size.y = size.y * 1.f;
    _background.setSize(menu_size);
    _background.setOrigin(menu_size / 2.f);
    _background.setPosition(position);

    _paused_text.setFont(*font);
    _paused_text.setString("Game Paused");
    _paused_text.setCharacterSize(70);
    centerOrigin(_paused_text);
    _paused_text.setPosition(position - sf::Vector2f(0, 50));

    auto to_game = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    to_game->setPosition(position + sf::Vector2f(- 100, 50));
    to_game->set_text("Back to the game");
    to_game->set_callback([this] () {
        requestStackPop();
    });

    auto to_menu = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    to_menu->setPosition(position + sf::Vector2f(- 100, 100));
    to_menu->set_text("Back to the menu");
    to_menu->set_callback([this] () {
        requestStateClear();
        requestStackPush(States::MENU);
    });

    _container.pack(to_game);
    _container.pack(to_menu);
}

void PauseState::draw() {
    sf::RenderWindow& window = *getContext().window;

    window.draw(_background);
    window.draw(_paused_text);
    window.draw(_container);
}

bool PauseState::update(sf::Time) { return false; }

bool PauseState::handle_event(const sf::Event& event) {
  _container.handle_event(event);
  return false;
}

PauseState::~PauseState() { getContext().music->setPaused(false); }
