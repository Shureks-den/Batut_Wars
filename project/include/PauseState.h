#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "State.h"
#include "Container.h"

class PauseState : public State {
 public:
    PauseState(StateStack& stack, Context context);
    ~PauseState() = default;

    void draw() override;
    bool update(sf::Time dt) override;
    bool handleEvent(const sf::Event& event) override;

 private:
    sf::Sprite _BackgroundSprite;
    sf::Text _PausedText;
    GUI::Container _GUIContainer;
};
