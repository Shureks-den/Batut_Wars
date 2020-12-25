#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "State.h"
#include "Container.h"

class GameOverState : public State {
 public:
    GameOverState(StateStack& stack, Context context);

    void draw() override;
    bool update(sf::Time dt) override;
    bool handle_event(const sf::Event&) override;

 private:
    sf::RectangleShape _background;
    sf::Text _mission;
    sf::Text _info;
};
