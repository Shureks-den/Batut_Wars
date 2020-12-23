#include "States/GameOverState.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include "Holder.h"
#include "Utility.h"

GameOverState::GameOverState(StateStack& stack, Context context)
: State(stack, context)
, _gameovertext()
, _ElapsedTime(sf::Time::Zero) {

    const sf::Font* font = context.fonts->get(fonts::Id::MAIN);
    _gameovertext.setFont(*font);

	if (context.player->get_mission_status() == Player::MissionStatus::MissionFailure) {
        _gameovertext.setString("Mission failed!");
    }

	else if (context.player->get_mission_status() == Player::MissionStatus::MissionSuccess) {
        _gameovertext.setString("Mission successful!");
    }

	_gameovertext.setCharacterSize(70);
	centerOrigin(_gameovertext);
	_gameovertext.setPosition(context.window->getView().getSize() / 2.f);
}

void GameOverState::draw() {
	sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    backgroundShape.setSize(window.getView().getSize());

    window.draw(backgroundShape);
    window.draw(_gameovertext);
}

bool GameOverState::update(sf::Time dt) {
    _ElapsedTime += dt;
	if (_ElapsedTime > sf::seconds(3)) {
        requestStateClear();
        requestStackPush(States::MENU);
	}
	return false;
}

bool GameOverState::handle_event(const sf::Event&) {
    return false;
}