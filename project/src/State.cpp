#include "State.h"
#include "StateStack.h"


State::Context::Context(sf::RenderWindow& window, textures::Holder& textures, fonts::Holder& fonts, Player& player)
        : window(&window), textures(&textures), fonts(&fonts), player(&player)
{
}

State::State(StateStack& stack, Context context)
        : mStack(&stack)
        , mContext(context)
{
}

State::~State() {
}

void State::requestStackPush(States::ID stateID) {
    mStack->pushState(stateID);
}

void State::requestStackPop() {
    mStack->popState();
}

void State::requestStateClear() {
    mStack->clearStates();
}

State::Context State::getContext() const {
    return mContext;
}