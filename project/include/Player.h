#pragma once

#include <SFML/Window/Event.hpp>
#include <map>
#include <queue>

class Player {
 public:
  enum Action {
    MOVE_LEFT = 0,
    MOVE_RIGHT,
    MOVE_FORWARD,
    MOVE_BACKWARD,
    FIRE,
    COUNT
  };
  enum MissionStatus {
			MissionRunning = 0,
			MissionSuccess,
			MissionFailure
	};
 public:
  Player();
  void handle_event(const sf::Event &event, std::queue<Action> &actions);
  void handle_realtime_event(std::queue<Player::Action> &commands);
  void assign_key(Player::Action action, sf::Keyboard::Key key);
  sf::Keyboard::Key get_key(Player::Action action) const;

  MissionStatus get_mission_status() const;
  void set_mission_status(MissionStatus status);
  // Action send_action();

 private:
  static bool is_realtime(Player::Action action);

  std::map<sf::Keyboard::Key, Player::Action> _key_binding;

  MissionStatus _current_status;
};
