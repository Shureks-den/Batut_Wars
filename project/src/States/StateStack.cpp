#include "States/StateStack.h"

#include <cassert>

StateStack::StateStack(State::Context context)
    : _stack(), _pending_list(), _context(context), _factories() {}

void StateStack::update(sf::Time dt) {
  for (auto it = _stack.rbegin(); it != _stack.rend(); ++it) {
    if (!(*it)->update(dt)) {
      break;
    }
  }

  apply_pending_changes();
}

void StateStack::draw() {
  for (auto &it : _stack) {
    it->draw();
  }
}

void StateStack::handle_event(const sf::Event &event) {
  for (auto it = _stack.rbegin(); it != _stack.rend(); ++it) {
    if (!(*it)->handle_event(event)) {
      break;
    }
  }

  apply_pending_changes();
}

void StateStack::push(States::Id state_id) {
  _pending_list.push_back(PendingChange(PUSH, state_id));
}

void StateStack::pop() { _pending_list.push_back(PendingChange(POP)); }

void StateStack::clear_states() {
  _pending_list.push_back(PendingChange(CLEAR));
}

bool StateStack::is_empty() const { return _stack.empty(); }

State::Ptr StateStack::create_state(States::Id state_id) {
  auto found = _factories.find(state_id);
  assert(found != _factories.end());

  return found->second();
}

void StateStack::apply_pending_changes() {
  for (auto &it : _pending_list) {
    switch (it.action) {
      case PUSH:
        _stack.push_back(create_state(it.state_id));
        break;

      case POP:
        _stack.pop_back();
        break;

      case CLEAR:
        _stack.clear();
        break;
    }
  }

  _pending_list.clear();
}

StateStack::PendingChange::PendingChange(Action action, States::Id state_id)
    : action(action), state_id(state_id) {}
