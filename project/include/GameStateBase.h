#pragma once

#include "State.h"
#include "World.h"
#include "Player.h"
#include "Render.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class GameStateBase : public State {
 public:
    GameStateBase(StateStack& stack, Context context);
    virtual ~GameStateBase() = default;

    void draw() override;
    virtual bool update(sf::Time dt) = 0;
    bool handle_event(const sf::Event& event) = 0;

 protected:
    void update_statistic(sf::Time time);

    Render _render;
    Player &_player;

    sf::Time _update_time;
    size_t _frames;
    sf::Text _statistic_text;
};
