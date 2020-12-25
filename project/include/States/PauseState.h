#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "State.h"
#include "Container.h"

class PauseState : public State {
 public:
    PauseState(StateStack& stack, Context context);
    ~PauseState();

    void draw() override;
    bool update(sf::Time dt) override;
    bool handle_event(const sf::Event& event) override;

 private:
    sf::RectangleShape _background;
    sf::Text _paused_text;
    GUI::Container _container;
};
