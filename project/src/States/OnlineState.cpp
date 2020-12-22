#include "States/OnlineState.h"

#include <memory>
#include <iostream>

OnlineState::OnlineState(StateStack& stack, Context context)
            : GameStateBase(stack, context),
              _client(context.client) {
    std::cout << "ONLINE STATE CONSTRUCTOR" << std::endl;
    _render.set_player_id(_client->get_id());
    _render.inicilize(_client->get_status());
}

bool OnlineState::update(sf::Time dt) {
    std::cout << "ONLINE UPDATE 1" << std::endl;
    _render.set_status(_client->get_status());
    std::cout << "ONLINE UPDATE 2" << std::endl;
    _render.update(dt);
    std::cout << "ONLINE UPDATE 3" << std::endl;
    update_statistic(dt);

    std::queue<Player::Action> &actions = _client->get_actions();
    // std::cout << "ONLINE UPDATE 4" << std::endl;
    _player.handle_realtime_event(actions);
    // std::cout << "ONLINE UPDATE 5" << std::endl;
    // _client->send_actions();
    // std::cout << "ONLINE UPDATE 6" << std::endl;
    return true;
}

bool OnlineState::handle_event(const sf::Event& event) {
    std::queue<Player::Action> &actions = _client->get_actions();
    _player.handle_event(event, actions);

    // // if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
    // //     requestStackPush(States::PAUSE);
    // // }
    return false;  // Запрет переадрессации команды другим стейтам
}
