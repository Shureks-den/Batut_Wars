#include "State.h"
#include "StateStack.h"


State::Context::Context(sf::RenderWindow& window, textures::Holder& textures, fonts::Holder& fonts, Player& player)
        : window(&window), textures(&textures), fonts(&fonts), player(&player)
{
}

State::State(StateStack& stack, Context context)
        : _Stack(&stack)
        , _Context(context)
{
}

State::~State() {
}

void State::requestStackPush(States::ID stateID) {
    _Stack->pushState(stateID);
}

void State::requestStackPop() {
    _Stack->popState();
}

void State::requestStateClear() {
    _Stack->clearStates();
}

State::Context State::getContext() const {
    return _Context;
}