#pragma once

#include "GameStateBase.h"
#include "World.h"

class GameState : public GameStateBase {
 public:
    GameState(StateStack& stack, Context context);
    ~GameState() = default;

    bool update(sf::Time dt) override;
    bool handle_event(const sf::Event& event) override;

 private:
    World _world;
};
