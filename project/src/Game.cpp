#include "Game.h"

#include <iostream>
#include <string>

#include "StateIdentifiers.h"
#include "TitleState.h"
#include "MenuState.h"
#include "GameState.h"
#include "SettingState.h"
#include "GameState.h"
#include "PauseState.h"

const sf::Time Game::_time_per_frame = sf::seconds(1.0 / 60.0);

Game::Game() : _window(sf::VideoMode(640, 480), "Input", sf::Style::Close),
               _player(),
               mTextures(),
               mFonts(),
               mStateStack(State::Context(_window, mTextures, mFonts, _player)) {
    _window.setKeyRepeatEnabled(false);
    _window.setVerticalSyncEnabled(true);
    registerStates();
    mStateStack.pushState(States::ID::Title);
}


void Game::run() {
    sf::Clock clock;
    sf::Time total_time = sf::Time::Zero;

    while (_window.isOpen()) {
        sf::Time current_time = clock.restart();
        total_time += current_time;

        while (total_time > _time_per_frame) {
            total_time -= _time_per_frame;

            get_input();
            update(_time_per_frame);

            if (mStateStack.isEmpty()) {
                _window.close();
            }
        }

        render();
    }
}

bool Game::update(sf::Time dt) {
    mStateStack.update(dt);
    return true;
}

void Game::render() {
    _window.clear();
    mStateStack.draw();
    //_window.setView(_window.getDefaultView());  // Вид устанавливается в _render.set_status
    _window.display();
}

void Game::get_input() {
    sf::Event event;

    while (_window.pollEvent(event)) {
        mStateStack.handleEvent(event);

        if (event.type == sf::Event::Closed) {
            _window.close();
        }
    }
}

void Game::registerStates() {
    mStateStack.registerState<TitleState>(States::Title);
    mStateStack.registerState<MenuState>(States::Menu);
    mStateStack.registerState<GameState>(States::Game);
    mStateStack.registerState<PauseState>(States::Pause);
    mStateStack.registerState<SettingsState>(States::Settings);
}
