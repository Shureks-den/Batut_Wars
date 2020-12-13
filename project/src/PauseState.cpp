#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include "PauseState.h"
#include "Button.h"
#include "Utility.h"
#include "Holder.h"

PauseState::PauseState(StateStack& stack, Context context)
        : State(stack, context)
        , _background()
        , _paused_text()
        , _container() {
    const sf::Font* font = context.fonts->get(fonts::Id::MAIN);
    sf::Vector2f windowSize(context.window->getSize());

    _paused_text.setFont(*font);
    _paused_text.setString("Game Paused");
    _paused_text.setCharacterSize(70);
    centerOrigin(_paused_text);
    _paused_text.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);

    auto returnButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    returnButton->setPosition(0.5f * windowSize.x - 100, 0.4f * windowSize.y + 125);
    returnButton->set_text("Back to the menu");
    returnButton->set_callback([this] () {
        requestStackPop();
    });

    auto backToMenuButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    backToMenuButton->setPosition(0.5f * windowSize.x - 100, 0.4f * windowSize.y + 75);
    backToMenuButton->set_text("Return");
    backToMenuButton->set_callback([this] () {
        requestStateClear();
        requestStackPush(States::MENU);
    });

    _container.pack(returnButton);
    _container.pack(backToMenuButton);
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
