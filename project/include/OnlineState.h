#pragma once

#include "GameStateBase.h"
#include "Client.h"
#include "Container.h"

class OnlineState : public GameStateBase {
 public:
    OnlineState(StateStack& stack, Context context);
    ~OnlineState() = default;

    void draw() override;
    bool update(sf::Time dt) override;
    bool handle_event(const sf::Event& event) override;

 private:
    network::Client _client;

    sf::RectangleShape _background;
    GUI::Container _container;
};
