#include "States/GameOverState.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Holder.h"
#include "Utility.h"

GameOverState::GameOverState(StateStack& stack, Context context)
: State(stack, context)
, _gameovertext()
, _ElapsedTime(sf::Time::Zero) {

	const sf::Texture* texture = context.textures->get(textures::Id::MENU_BACKGROUND);
    _background.setTexture(texture);
    sf::Vector2u size = context.window->getSize();
    sf::Vector2f menu_size;
    menu_size.x = size.x * 1.f;
    menu_size.y = size.y * 1.f;
    _background.setSize(menu_size);
    _background.setPosition(0, 0);
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
    window.draw(_background);
    window.draw(_gameovertext);
}

bool GameOverState::update(sf::Time dt) {
    _ElapsedTime += dt;
	if (_ElapsedTime > sf::seconds(5)) {
		requestStateClear();
		requestStackPush(States::MENU);
	}
	return false;
}

bool GameOverState::handle_event(const sf::Event&) {
    return false;
}