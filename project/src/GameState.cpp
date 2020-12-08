#include "GameState.h"

#include "Ship.h"

#include <memory>

GameState::GameState(StateStack& stack, Context context) : GameStateBase(stack, context),
                                                           _world() {
    auto main_ship = std::unique_ptr<engine::Entity>(new space::Ship);  // TODO(ANDY) инициализация карты
    main_ship->set_position(sf::Vector2f(1000, 1000));
    _render.set_player_id(main_ship->get_id());
    _world.push_back(std::move(main_ship));
    // space::Ship *other_ship = new space::Ship;  // тупой бот
    // other_ship->set_position(sf::Vector2f(1100, 1000));
    // _world.push_back(*other_ship);
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
