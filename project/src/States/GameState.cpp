#include "States/GameState.h"

#include <memory>

#include "Ally.h"

#include "Vietnam.h"

GameState::GameState(StateStack& stack, Context context) : GameStateBase(stack, context),
                                                           _world() {
    context.music->play(Music::MissionTheme);

    *context.mission_status = Mission::RUN;
    // ИГРОК
    auto main_ship = std::unique_ptr<engine::MoveAble>(new space::Ally);  // TODO(ANDY) инициализация карты
    main_ship->set_position(sf::Vector2f(1000, 1000));
    main_ship->rotate(engine::as_radian(- 90));
    _world.push_player(std::move(main_ship));
    _render.set_player_id(0);

    welcome_to_vietnam(_world);

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

    if (_world.is_over()) {
        _game_over += dt;
        _mission_status = _world.get_mission()[0];
    }

    if (_game_over.asSeconds() >= ENDING_TIME) {
        requestStackPush(States::Id::ENDGAME);
    }

    return (_game_over.asSeconds() >= ENDING_TIME);
}

bool GameState::handle_event(const sf::Event& event) {
  std::queue<Player::Action> actions;
  _player.handle_event(event, actions);

  auto& world_actions = _world.get_actions();
  while (!actions.empty()) {
    world_actions.push(std::make_pair(0, actions.front()));
    actions.pop();
  }

  if (event.type == sf::Event::KeyPressed &&
      event.key.code == sf::Keyboard::Escape) {
    requestStackPush(States::PAUSE);
  }

  return true;
}
