#include "PauseState.h"
#include "Button.h"
#include "Utility.h"
#include "Holder.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


PauseState::PauseState(StateStack& stack, Context context)
        : State(stack, context)
        , _BackgroundSprite()
        , _PausedText()
        , _GUIContainer()
{
    const sf::Font* font = context.fonts->get(fonts::Id::MAIN);
    sf::Vector2f windowSize(context.window->getSize());

    _PausedText.setFont(*font);
    _PausedText.setString("Game Paused");
    _PausedText.setCharacterSize(70);
    centerOrigin(_PausedText);
    _PausedText.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);

    auto returnButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    returnButton->setPosition(0.5f * windowSize.x - 100, 0.4f * windowSize.y + 75);
    returnButton->setText("Return");
    returnButton->setCallback([this] ()
                              {
                                  requestStackPop();
                              });

    auto backToMenuButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    backToMenuButton->setPosition(0.5f * windowSize.x - 100, 0.4f * windowSize.y + 125);
    backToMenuButton->setText("Back to menu");
    backToMenuButton->setCallback([this] ()
                                  {
                                      requestStateClear();
                                      requestStackPush(States::Menu);
                                  });

    _GUIContainer.pack(returnButton);
    _GUIContainer.pack(backToMenuButton);
}

void PauseState::draw() {
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    backgroundShape.setSize(window.getView().getSize());

    window.draw(backgroundShape);
    window.draw(_PausedText);
    window.draw(_GUIContainer);
}

bool PauseState::update(sf::Time)
{
    return false;
}

bool PauseState::handleEvent(const sf::Event& event)
{
    _GUIContainer.handleEvent(event);
    return false;
}