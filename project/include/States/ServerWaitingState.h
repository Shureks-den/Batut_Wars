#pragma once

#include "State.h"
#include "Container.h"

class ServerWaitingState : public State {
 public:
    ServerWaitingState(StateStack& stack, Context context);
    ~ServerWaitingState() = default;

    void draw() override;
    bool update(sf::Time dt) override;
    bool handle_event(const sf::Event& event) override;

 private:
    sf::RectangleShape _background;

    GUI::Container _container;

    sf::Text _text;
    sf::Text _ip;
    sf::Text _port;

    size_t _players_count;
};