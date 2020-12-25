#pragma once

#include "State.h"
#include "World.h"
#include "Player.h"
#include "Render.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

constexpr float ENDING_TIME = 5.f;  // В секундах

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
    Mission &_mission_status;

    sf::Time _game_over;

    sf::Time _update_time;
    size_t _frames;
    sf::Text _statistic_text;
};
