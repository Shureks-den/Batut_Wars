#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "State.h"
#include "Container.h"

class MenuState : public State {
 public:
    MenuState(StateStack& stack, Context context);

    void draw() override;
    bool update(sf::Time dt) override;
    bool handleEvent(const sf::Event& event) override;

 private:
    sf::Sprite _BackgroundSprite;
    GUI::Container _GUIContainer;
};
