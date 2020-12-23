#pragma once

#include "State.h"

class WaitingState : public State {
 public:
    WaitingState(StateStack& stack, Context context);
    ~WaitingState() = default;

    void draw() override;
    bool update(sf::Time dt) override;
    bool handle_event(const sf::Event& event) override;

 private:
    sf::RectangleShape _background;

    sf::Text _text;

    bool _is_showing;
    sf::Time _text_effect;
};
