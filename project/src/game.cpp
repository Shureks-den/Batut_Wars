#include "game.h"

#include <string>

#include "State.h"
#include "TitleState.h"
#include "MenuState.h"
#include "GameState.h"
#include "SettingState.h"
#include "GameState.h"
#include "PauseState.h"

const sf::Time Game::_time_per_frame = sf::seconds(1.0 / 60.0);

Game::Game() : _window(sf::VideoMode(640, 480), "Input", sf::Style::Close),
               mTextures(),
               mFonts(),
               _player()
               mStateStack(State::Context(_window, mTextures, mFonts, _player)),
               _frames(0) {
    _window.setKeyRepeatEnabled(false);
    _window.setVerticalSyncEnabled(true);
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

        update_statistic(current_time);
        render(current_time);
    }
}

bool Game::update(sf::Time dt) {
    mStateStack.update(dt);
    return true;
}

void Game::render(sf::Time dt) {
    _window.clear();
    mStateStack.draw();
    _window.setView(mStateStack.get_view());  // Вид устанавливается в _render.set_status
    _window.display();
}

void Game::get_input() {
    // std::queue<Player::Action> &actions = _world.get_actions();
    // sf::Event event;

    // while (_window.pollEvent(event)) {
    //     _player.handle_event(event, actions);

    //     if (event.type == sf::Event::Closed) {
    //         _window.close();
    //     }
    // }

    // _player.handle_realtime_event(actions);


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
