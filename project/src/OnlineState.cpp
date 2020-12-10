#include "OnlineState.h"

#include <memory>

OnlineState::OnlineState(StateStack& stack, Context context)
            : GameStateBase(stack, context),
              _container() {
    const sf::Texture* texture = context.textures->get(textures::Id::MENU_BACKGROUND);
    _background.setTexture(texture);
    sf::Vector2u size = context.window->getSize();
    sf::Vector2f menu_size;
    menu_size.x = size.x * 1.f;
    menu_size.y = size.y * 1.f;
    _background.setSize(menu_size);
    _background.setPosition(0, 0);

    


}

bool OnlineState::update(sf::Time dt) {
    if (!_client.is_connected()) {
        return true;
    }


    _render.set_status(_client.get_status());
    _render.update(dt);
    update_statistic(dt);

    std::queue<Player::Action> &actions = _client.get_actions();
    _player.handle_realtime_event(actions);
    return true;
}

void OnlineState::draw() {
    if (_client.is_connected()) {
        _render.draw();
        return;
    }

    sf::RenderWindow& window = *getContext().window;

    window.draw(_background);
    window.draw(_container);
}

bool OnlineState::handle_event(const sf::Event& event) {
    if (!_client.is_connected()) {
        _container.handle_event(event);
        return true;
    }

    std::queue<Player::Action> &actions = _client.get_actions();
    _player.handle_event(event, actions);

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        requestStackPush(States::PAUSE);
    }

    return true;
}
