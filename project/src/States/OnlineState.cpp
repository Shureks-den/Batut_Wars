#include "States/OnlineState.h"

#include <iostream>
#include <memory>

OnlineState::OnlineState(StateStack& stack, Context context)
    : GameStateBase(stack, context), _client(context.client) {
  std::cout << "ONLINE STATE CONSTRUCTOR" << std::endl;
  _render.set_player_id(_client->get_id());
  _render.inicilize(_client->get_status());
}

OnlineState::~OnlineState() {
    if (getContext().client_thread->joinable()) {
        getContext().client_thread->join();
    }
    if (getContext().server_thread->joinable()) {
        getContext().server_thread->join();
    }
}

bool OnlineState::update(sf::Time dt) {
    _render.set_status(_client->get_status());
    _mission_status = _client->get_mission();
    _render.update(dt);

  update_statistic(dt);

  std::queue<Player::Action>& actions = _client->get_actions();
  _player.handle_realtime_event(actions);

    if (_mission_status == Mission::FAIL || _mission_status == Mission::SUCCESS) {
        _game_over += dt;
    }

    if (_game_over.asSeconds() >= ENDING_TIME) {
        requestStackPush(States::Id::ENDGAME);
    }

    return true;
}

bool OnlineState::handle_event(const sf::Event& event) {
  std::queue<Player::Action>& actions = _client->get_actions();
  _player.handle_event(event, actions);

  // // if (event.type == sf::Event::KeyPressed && event.key.code ==
  // sf::Keyboard::Escape) {
  // //     requestStackPush(States::PAUSE);
  // // }
  return false;  // Запрет переадрессации команды другим стейтам
}
