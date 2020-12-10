#pragma once

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "State.h"
#include "Container.h"

class MenuState : public State {
 public:
    MenuState(StateStack& stack, Context context);

    void draw() override;
    bool update(sf::Time dt) override;
    bool handle_event(const sf::Event& event) override;

 private:
    sf::RectangleShape _background;
    GUI::Container _container;
};
