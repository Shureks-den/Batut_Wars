#pragma once

#include "State.h"
#include "Container.h"

class GameOverState : public State {
 public:
	GameOverState(StateStack& stack, Context context);

	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);

 private:
    sf::RectangleShape _background;
	sf::Text _gameovertext;
	sf::Time _ElapsedTime;
};
