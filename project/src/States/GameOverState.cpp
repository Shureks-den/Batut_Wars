#include "States/GameOverState.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include "Holder.h"
#include "Utility.h"

GameOverState::GameOverState(StateStack& stack, Context context)
              : State(stack, context) {
    _background.setFillColor(sf::Color(0, 0, 0, 150));
    sf::Vector2u size = context.window->getSize();
    sf::Vector2f position = context.window->getView().getCenter();
    sf::Vector2f menu_size;
    menu_size.x = size.x * 1.f;
    menu_size.y = size.y * 1.f;
    _background.setSize(menu_size);
    _background.setOrigin(menu_size / 2.f);
    _background.setPosition(position);

    const sf::Font* font = context.fonts->get(fonts::Id::MAIN);

    _mission.setFont(*font);
    _mission.setCharacterSize(70);

    if (*context.mission_status == Mission::FAIL) {
        _mission.setString("Mission failed!");
    } else if (*context.mission_status == Mission::SUCCESS) {
        _mission.setString("Mission successful!");
    }
    
    centerOrigin(_mission);

    _info.setFont(*font);
    _info.setString("Press ENTER to continue");
    _info.setCharacterSize(30);
    centerOrigin(_info);


    _mission.setPosition(position - sf::Vector2f(0, 70));
    _info.setPosition(position + sf::Vector2f(0, 70));
}

void GameOverState::draw() {
    sf::RenderWindow& window = *getContext().window;

    window.draw(_background);

    window.draw(_mission);
    window.draw(_info);
}

bool GameOverState::update(sf::Time) {
    return false;
}

bool GameOverState::handle_event(const sf::Event &event) {
    if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter) {
        requestStateClear();
        *getContext().mission_status = Mission::AWAITING;
        requestStackPush(States::MENU);
    }
    return false;
}