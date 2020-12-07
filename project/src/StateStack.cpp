#include <cassert>

#include "StateStack.h"
#include "Foreach.h"

StateStack::StateStack(State::Context context)
        : _Stack()
        , _PendingList()
        , _Context(context)
        , _Factories() {
}

void StateStack::update(sf::Time dt) {
    // Iterate from top to bottom, stop as soon as update() returns false
    for (auto itr = _Stack.rbegin(); itr != _Stack.rend(); ++itr) {
        if (!(*itr)->update(dt))
            break;
    }
    applyPendingChanges();
}

void StateStack::draw() {
    //  Draw all active states from bottom to top
    FOREACH(State::Ptr& state, _Stack) {
        state->draw();
    }
}

void StateStack::handleEvent(const sf::Event& event) {
    //  Iterate from top to bottom, stop as soon as handleEvent() returns false
    for (auto itr = _Stack.rbegin(); itr != _Stack.rend(); ++itr) {
        if (!(*itr)->handleEvent(event))
            break;
    }

    applyPendingChanges();
}

void StateStack::pushState(States::ID stateID) {
    _PendingList.push_back(PendingChange(Push, stateID));
}

void StateStack::popState() {
    _PendingList.push_back(PendingChange(Pop));
}

void StateStack::clearStates() {
    _PendingList.push_back(PendingChange(Clear));
}

bool StateStack::isEmpty() const {
    return _Stack.empty();
}

State::Ptr StateStack::createState(States::ID stateID) {
    auto found = _Factories.find(stateID);
    assert(found != _Factories.end());

    return found->second();
}

void StateStack::applyPendingChanges() {
    FOREACH(PendingChange change, _PendingList) {
        switch (change.action) {
            case Push:
                _Stack.push_back(createState(change.stateID));
                break;

            case Pop:
                _Stack.pop_back();
                break;

            case Clear:
                _Stack.clear();
                break;
        }
    }

    _PendingList.clear();
}

StateStack::PendingChange::PendingChange(Action action, States::ID stateID)
        : action(action)
        , stateID(stateID) {
}
