#include "State.h"
#include "StateStack.h"


State::Context::Context(sf::RenderWindow& window, textures::Holder& textures, fonts::Holder& fonts, Player& player)
      : window(&window), textures(&textures), fonts(&fonts), player(&player) {
}

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
