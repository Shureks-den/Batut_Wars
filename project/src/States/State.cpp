#include "States/State.h"

#include "States/StateStack.h"

State::Context::Context(sf::RenderWindow &window, textures::Holder &textures,
                        fonts::Holder &fonts, Player &player,
                        std::pair<sf::IpAddress, uint16_t> &network_info,
                        network::Client &client,
                        network::Server &server,
                        std::thread &server_thread,
                        std::thread &client_thread,
                        MusicPlayer &music,
                        Mission &mission_status)

                      : window(&window),
                        textures(&textures),
                        fonts(&fonts),
                        player(&player),
                        network_info(&network_info),
                        client(&client),
                        server(&server),
                        server_thread(&server_thread),
                        client_thread(&client_thread),
                        music(&music),
                        mission_status(&mission_status) {}

State::State(StateStack& stack, Context context)
      : _stack(&stack),
        _context(context) {}

void State::requestStackPush(States::Id state_id) {
    _stack->push(state_id);
}

void State::requestStackPop() {
    _stack->pop();
}

void State::requestStateClear() {
    _stack->clear_states();
}

State::Context State::getContext() const {
    return _context;
}
