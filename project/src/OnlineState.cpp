#include "OnlineState.h"

#include <memory>

OnlineState::OnlineState(StateStack& stack, Context context)
            : GameStateBase(stack, context),
              _client(context.client) {}

bool OnlineState::update(sf::Time dt) {
    _render.set_status(_client->get_status());
    _render.update(dt);
    update_statistic(dt);

    std::queue<Player::Action> &actions = _client->get_actions();
    _player.handle_realtime_event(actions);
    return true;
}

void OnlineState::draw() {
    _render.draw();
}

bool OnlineState::handle_event(const sf::Event& event) {
    std::queue<Player::Action> &actions = _client->get_actions();
    _player.handle_event(event, actions);

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        requestStackPush(States::PAUSE);
    }
    return true;
}
