#pragma once

#include "State.h"
#include "Container.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class PauseState : public State {
public:
    PauseState(StateStack& stack, Context context);
    ~PauseState() = default;

    void draw() override;
    bool update(sf::Time dt) override;
    bool handleEvent(const sf::Event& event) override;


private:
    sf::Sprite			mBackgroundSprite;
    sf::Text			mPausedText;
    GUI::Container 		mGUIContainer;
};
