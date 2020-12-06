#ifndef BOOK_GAMESTATE_HPP
#define BOOK_GAMESTATE_HPP

#include "State.h"
#include "world.h"
#include "player.h"
#include "render.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class GameState : public State {
public:
    GameState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

private:
    void update_statistic(sf::Time time);

    World _world;
    Render _render;
    Player&	mPlayer;

    sf::Time _update_time;
    size_t _frames;
    sf::Font _statistic_font;
    sf::Text _statistic_text;
};

#endif // BOOK_GAMESTATE_HPP