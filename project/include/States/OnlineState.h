#pragma once

#include "GameStateBase.h"
#include "Client.h"

class OnlineState : public GameStateBase {
 public:
    OnlineState(StateStack& stack, Context context);
    ~OnlineState();

    bool update(sf::Time dt) override;
    bool handle_event(const sf::Event& event) override;

 private:
    network::Client *_client;
};
