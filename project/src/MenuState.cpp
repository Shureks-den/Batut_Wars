#include "MenuState.h"
#include "Button.h"
#include "Utility.h"
#include "Holder.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


MenuState::MenuState(StateStack& stack, Context context)
        : State(stack, context)
        , _GUIContainer()
{
    const sf::Texture* texture = context.textures->get(textures::Id::MENU_BACKGROUND);
    _BackgroundSprite.setTexture(*texture);

    auto playButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    sf::Vector2u size = context.window->getSize();
    playButton->setPosition(size.x / 2, size.y / 2);
    playButton->setText("Play");
    playButton->setCallback([this] ()
                            {
                                requestStackPop();
                                requestStackPush(States::Game);
                            });

    auto settingsButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    settingsButton->setPosition(size.x / 2, size.y / 2 + 40);
    settingsButton->setText("Settings");
    settingsButton->setCallback([this] ()
                                {
                                    requestStackPush(States::Settings);
                                });

    auto exitButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    exitButton->setPosition(size.x / 2, size.y / 2 + 80);
    exitButton->setText("Exit");
    exitButton->setCallback([this] ()
                            {
                                requestStackPop();
                            });

    _GUIContainer.pack(playButton);
    _GUIContainer.pack(settingsButton);
    _GUIContainer.pack(exitButton);
}

void MenuState::draw()
{
    sf::RenderWindow& window = *getContext().window;


    window.draw(_BackgroundSprite);
    window.draw(_GUIContainer);
}

bool MenuState::update(sf::Time)
{
    return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
    _GUIContainer.handleEvent(event);
    return false;
}