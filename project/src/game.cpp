#include "game.h"

#include <string>

const sf::Time Game::_time_per_frame = sf::seconds(1.0/60.0);

Game::Game() : _window(sf::VideoMode(640, 480), "Input", sf::Style::Close),
               _render(_window),
               _frames(0) {
    _window.setKeyRepeatEnabled(false);

    _statistic_font.loadFromFile("Media/Sansation.ttf");
    _statistic_text.setFont(_statistic_font);
    _statistic_text.setPosition(5.f, 5.f);
    _statistic_text.setCharacterSize(10);
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
        }

        update_statistic(current_time);
        render(current_time);
    }
}

bool Game::update(sf::Time dt) {
    _world.update(dt);
}

void Game::update_statistic(sf::Time time) {
    _update_time += time;
    _frames += 1;

    if (_update_time >= sf::seconds(1.0f)) {
        _statistic_text.setString(
            "Frames / Second = " + std::to_string(_frames) + "\n" +
            "Time / Update = " + std::to_string(_update_time.asMicroseconds() / _frames) + "us");

        _update_time -= sf::seconds(1.0f);
        _frames = 0;
    }
}

void Game::render(sf::Time dt) {
    _window.clear();
    // Обмен данными между _render и _world
    _render.update(dt);
    _render.draw();
    _window.setView(_window.getDefaultView());
    _window.draw(_statistic_text);
    _window.display();
}

void Game::get_input() {
    std::queue<Action> &actions = _world.get_actions();
    sf::Event event;

    while (_window.pollEvent(event)) {
        _player.handle_event(event, actions);

        if (event.type == sf::Event::Closed) {
            _window.close();
        }
    }

    _player.handle_realtime_event(actions);
}