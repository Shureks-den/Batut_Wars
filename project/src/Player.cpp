#include "Player.h"

#include <algorithm>

Player::Player() {
  _key_binding[sf::Keyboard::W] = Action::MOVE_FORWARD;
  _key_binding[sf::Keyboard::A] = Action::MOVE_LEFT;
  _key_binding[sf::Keyboard::S] = Action::MOVE_BACKWARD;
  _key_binding[sf::Keyboard::D] = Action::MOVE_RIGHT;
  _key_binding[sf::Keyboard::Space] = FIRE;
}

void Player::handle_event(const sf::Event &event, std::queue<Action> &actions) {
  if (event.type == sf::Event::KeyPressed) {
    const auto &found = _key_binding.find(event.key.code);
    if (found != _key_binding.end() && !is_realtime(found->second)) {
      actions.push(found->second);
    }
  }
}

void Player::handle_realtime_event(std::queue<Action> &actions) {
  for (const auto &it : _key_binding) {
    if (sf::Keyboard::isKeyPressed(it.first) && is_realtime(it.second)) {
      actions.push(it.second);
    }
  }
}

void Player::assign_key(Action action, sf::Keyboard::Key key) {
  for (auto it = _key_binding.begin(); it != _key_binding.end(); it++) {
    if (it->second == action) {
      _key_binding.erase(it);
    }
  }

  _key_binding[key] = action;
}

sf::Keyboard::Key Player::get_key(Action action) const {
  for (auto &it : _key_binding) {
    if (it.second == action) {
      return it.first;
    }
  }

  return sf::Keyboard::Unknown;
}

bool Player::is_realtime(Action action) {
  switch (action) {
    case Action::MOVE_LEFT:
    case Action::MOVE_RIGHT:
    case Action::MOVE_BACKWARD:
    case Action::MOVE_FORWARD:
    case Action::FIRE:
      return true;

    default:
      return false;
  }
}

