#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include "States/PauseState.h"
#include "Button.h"
#include "Utility.h"
#include "Holder.h"

PauseState::PauseState(StateStack& stack, Context context)
        : State(stack, context)
        , _background()
        , _paused_text()
        , _container() {
    getContext().music->setPaused(true);
    const sf::Font* font = context.fonts->get(fonts::Id::MAIN);
    sf::Vector2f windowSize(context.window->getSize());

    _paused_text.setFont(*font);
    _paused_text.setString("Game Paused");
    _paused_text.setCharacterSize(70);
    centerOrigin(_paused_text);
    _paused_text.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);

    auto to_game = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    to_game->setPosition(0.5f * windowSize.x - 100, 0.4f * windowSize.y + 125);
    to_game->set_text("Back to the game");
    to_game->set_callback([this] () {
        requestStackPop();
    });

    auto to_menu = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    to_menu->setPosition(0.5f * windowSize.x - 100, 0.4f * windowSize.y + 75);
    to_menu->set_text("Back to the menu");
    to_menu->set_callback([this] () {
        requestStateClear();
        requestStackPush(States::MENU);
    });

    _container.pack(to_menu);
    _container.pack(to_game);
}

void PauseState::draw() {
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    backgroundShape.setSize(window.getView().getSize());

    window.draw(backgroundShape);
    window.draw(_paused_text);
    window.draw(_container);
}

bool PauseState::update(sf::Time) {
    return false;
}

bool PauseState::handle_event(const sf::Event& event) {
    _container.handle_event(event);
    return false;
}

PauseState::~PauseState() {
   getContext().music->setPaused(false);
}
