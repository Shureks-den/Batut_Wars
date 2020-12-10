#include "GameState.h"

#include "Ship.h"
#include "Massive.h"

#include <memory>

GameState::GameState(StateStack& stack, Context context) : GameStateBase(stack, context),
                                                           _world() {
    _world.set_player_count(1);
    // ИГРОК
    auto main_ship = std::unique_ptr<engine::MoveAble>(new space::Ship);  // TODO(ANDY) инициализация карты
    main_ship->set_position(sf::Vector2f(1000, 1000));
    main_ship->set_id(0);
    _render.set_player_id(main_ship->get_id());
    _world.push_player(std::move(main_ship));

    // ЧЕРНАЯ ДЫРОЧКА
    auto blackhole = std::unique_ptr<engine::ImmoveAble>(new space::Massive(100, 125.0f));
    blackhole->set_position(sf::Vector2f(600, 700));
    blackhole->set_id(0);
    _world.push_back(std::move(blackhole));
    auto blackhole_2 = std::unique_ptr<engine::ImmoveAble>(new space::Massive(100, 125.0f));
    blackhole_2->set_position(sf::Vector2f(1300, 1300));
    blackhole_2->set_id(1);
    _world.push_back(std::move(blackhole_2));

    // ТУПОЙ БОТ
    auto bot = std::unique_ptr<engine::MoveAble>(new space::Ship);
    bot->set_position(sf::Vector2f(1200, 1000));
    bot->give_acceleration(Direction::FORWARD);
    bot->set_id(0);
    _world.push_back(std::move(bot));

    _render.inicilize(_world.get_status());
}

bool GameState::update(sf::Time dt) {
    _world.update(dt);
    _render.set_status(_world.get_status());  // Обмен данными между _render и _world
    _render.update(dt);
    update_statistic(dt);

    std::queue<Player::Action> &actions = _world.get_actions();
    _player.handle_realtime_event(actions);
    return !_world.is_over();
}

bool GameState::handle_event(const sf::Event& event) {
    std::queue<Player::Action> &actions = _world.get_actions();
    _player.handle_event(event, actions);

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        requestStackPush(States::PAUSE);
    }

    return true;
}
