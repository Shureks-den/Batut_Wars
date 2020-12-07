#pragma once

#include "State.h"
#include "World.h"
#include "Player.h"
#include "Render.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class GameState : public State {
public:
    GameState(StateStack& stack, Context context);
    ~GameState() = default;

    void draw() override;
    bool update(sf::Time dt) override;
    bool handleEvent(const sf::Event& event) override;

private:
    void update_statistic(sf::Time time);

    World _world;
    Render _render;
    Player &mPlayer;

    sf::Time _update_time;
    size_t _frames;
    sf::Font _statistic_font;
    sf::Text _statistic_text;
};
