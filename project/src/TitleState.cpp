#include "TitleState.h"
#include "Utility.h"
#include "Holder.h"

#include <SFML/Graphics/RenderWindow.hpp>


TitleState::TitleState(StateStack& stack, Context context)
        : State(stack, context)
        , _Text()
        , mShowText(true)
        , mTextEffectTime(sf::Time::Zero) {
    _BackgroundSprite.setTexture(*context.textures->get(textures::Id::MENU_BACKGROUND));

    _Text.setFont(*context.fonts->get(fonts::Id::MAIN));
    _Text.setString("Press any key to start");
    centerOrigin(_Text);
    _Text.setPosition(context.window->getView().getSize() / 2.f);
}

void TitleState::draw() {
    sf::RenderWindow& window = *getContext().window;
    window.draw(_BackgroundSprite);

    if (mShowText)
        window.draw(_Text);
}

bool TitleState::update(sf::Time dt) {
    mTextEffectTime += dt;

    if (mTextEffectTime >= sf::seconds(0.5f)) {
        mShowText = !mShowText;
        mTextEffectTime = sf::Time::Zero;
    }

    return true;
}

bool TitleState::handleEvent(const sf::Event &event) {
    if (event.type == sf::Event::KeyReleased) {
        requestStackPop();
        requestStackPush(States::Menu);
    }

    return true;
}