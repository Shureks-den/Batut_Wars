#include "ServerWaitingState.h"

#include <memory>

#include "Utility.h"
#include "Holder.h"
#include "Button.h"

ServerWaitingState::ServerWaitingState(StateStack& stack, Context context)
            : State(stack, context),
            _players_count(context.server->get_players()) {
    const sf::Texture* texture = context.textures->get(textures::Id::MENU_BACKGROUND);
    _background.setTexture(texture);
    sf::Vector2u size = context.window->getSize();
    sf::Vector2f menu_size;
    menu_size.x = size.x * 1.f;
    menu_size.y = size.y * 1.f;
    _background.setSize(menu_size);
    _background.setPosition(0, 0);

    const sf::Font* font = context.fonts->get(fonts::Id::MAIN);

    _ip.setFont(*font);
    _ip.setString("ip: " + getContext().network_info->first.toString());
    centerOrigin(_ip);
    _ip.setPosition(menu_size / 2.f - sf::Vector2f(0, 75));

    _port.setFont(*font);
    _port.setString("port: " + std::to_string(getContext().network_info->second));
    centerOrigin(_port);
    _port.setPosition(menu_size / 2.f - sf::Vector2f(0, 25));

    _text.setFont(*font);
    _text.setString("PLAYERS CONNECTED: " + std::to_string(_players_count));
    centerOrigin(_text);
    _text.setPosition(menu_size / 2.f + sf::Vector2f(0, 25));

    auto start = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    start->setPosition(menu_size / 2.f + sf::Vector2f(- 100, 75));
    start->set_text("Start game");
    start->set_callback([this] () {
        getContext().server->start_game();
    });

    _container.pack(start);
}

bool ServerWaitingState::update(sf::Time) {
    _players_count = getContext().server->get_players();
    _text.setString("PLAYERS CONNECTED: " + std::to_string(_players_count));

    if (getContext().client->is_game_started()) {
        requestStackPop();
        requestStackPush(States::Id::ONLINE);
    }

    return true;
}

void ServerWaitingState::draw() {
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    window.draw(_background);

    window.draw(_ip);
    window.draw(_port);
    window.draw(_text);

    window.draw(_container);
}

bool ServerWaitingState::handle_event(const sf::Event &event) {
    _container.handle_event(event);
    return false;
}
