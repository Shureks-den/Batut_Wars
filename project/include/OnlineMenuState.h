#pragma once

#include "Container.h"
#include "State.h"

class OnlineMenuState : public State {
 public:
    OnlineMenuState(StateStack& stack, Context context);
    ~OnlineMenuState() = default;

    void draw() override;
    bool update(sf::Time dt) override;
    bool handle_event(const sf::Event& event) override;

 private:
    sf::RectangleShape _background;
    GUI::Container _container;
};
