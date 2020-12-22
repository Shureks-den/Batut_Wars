#include "States/GameState.h"

#include "Ship.h"
#include "Enemy.h"
#include "Massive.h"
#include "Bullet.h"

#include <memory>

GameState::GameState(StateStack& stack, Context context) : GameStateBase(stack, context),
                                                           _world() {
    // ИГРОК
    context.music->play(Music::MissionTheme);
    auto main_ship = std::unique_ptr<engine::MoveAble>(new space::Ship);  // TODO(ANDY) инициализация карты
    main_ship->set_position(sf::Vector2f(1000, 1000));
    main_ship->rotate(engine::as_radian(- 90));
    _world.push_player(std::move(main_ship));
    _render.set_player_id(0);

    // ЧЕРНАЯ ДЫРОЧКА
    auto blackhole = std::unique_ptr<space::Massive>(new space::Massive(100, 125.0f));
    blackhole->set_position(sf::Vector2f(600, 700));
    _world.push_back(std::move(blackhole));
  

    // ТУПОЙ БОТ
    auto bot = std::unique_ptr<space::Enemy>(new space::Enemy);
    bot->set_position(sf::Vector2f(1500, 1000));
    _world.push_back(std::move(bot));

    _render.inicilize(_world.get_status());
}

bool GameState::update(sf::Time dt) {
    _world.update(dt);
    _render.set_status(_world.get_status());  // Обмен данными между _render и _world
    _render.update(dt);
    update_statistic(dt);

    std::queue<Player::Action> actions;
    _player.handle_realtime_event(actions);

    auto &world_actions = _world.get_actions();
    while (!actions.empty()) {
        world_actions.push(std::make_pair(0, actions.front()));
        actions.pop();
    }

    return !_world.is_over();
}

bool GameState::handle_event(const sf::Event& event) {
    std::queue<Player::Action> actions;
    _player.handle_event(event, actions);

    auto &world_actions = _world.get_actions();
    while (!actions.empty()) {
        world_actions.push(std::make_pair(0, actions.front()));
        actions.pop();
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        requestStackPush(States::PAUSE);
    }

    return true;
}
