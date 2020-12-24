#include "Network.h"

sf::Packet& operator<<(sf::Packet& packet, animation::Id &id) {
    return packet << static_cast<int>(id);
}

sf::Packet& operator>>(sf::Packet& packet, animation::Id &id) {
    int tmp;
    packet >> tmp;
    id = static_cast<animation::Id>(tmp);
    return packet;
}

sf::Packet& operator<<(sf::Packet& packet, std::queue<Player::Action>& actions) {
    packet << static_cast<int>(actions.size());
    while (!actions.empty()) {
        packet << static_cast<int>(actions.front());
        actions.pop();
    }
    return packet;
}

sf::Packet& operator>>(sf::Packet& packet, std::queue<Player::Action>& actions) {
    int tmp;
    int size;
    packet >> size;
    for (int i = 0; i < size; ++i) {
        packet >> tmp;
        actions.push(static_cast<Player::Action>(tmp));
    }
    return packet;
}

sf::Packet& operator<<(sf::Packet& packet, std::vector<bool>& bool_vector) {
  packet << static_cast<int>(bool_vector.size());
  for (auto it : bool_vector) {
    packet << it;
  }
  return packet;
}

sf::Packet& operator>>(sf::Packet& packet, std::vector<bool>& bool_vector) {
  int size;
  packet >> size;
  bool_vector.resize(size);
  for (size_t i = 0; i < static_cast<size_t>(size); ++i) {
    bool data;
    packet >> data;
    bool_vector[i] = data;
  }
  return packet;
}

sf::Packet& operator<<(sf::Packet& packet, Mission &mission) {
    return packet << static_cast<int>(mission);
}

sf::Packet& operator>>(sf::Packet& packet, Mission &mission) {
    int data;
    packet >> data;
    mission = static_cast<Mission>(data);
    return packet;
}

sf::Packet& operator<<(sf::Packet& packet, std::vector<Mission> &mission) {
    packet << static_cast<int>(mission.size());
    for (auto &it : mission) {
        packet << it;
    }
    return packet;
}

sf::Packet& operator>>(sf::Packet& packet, std::vector<Mission> &mission) {
    int size;
    packet >> size;
    mission.resize(size);
    for (size_t i = 0; i < static_cast<size_t>(size); ++i) {
        Mission data;
        packet >> data;
        mission[i] = data;
    }
    return packet;
}

sf::Packet& operator<<(sf::Packet& packet, Status& status) {
  return packet << status.angle << status.states << status.animation_id
                << static_cast<int>(status.id) << status.is_removed
                << static_cast<int>(status.lay_id) << status.position.x
                << status.position.y;
}

sf::Packet& operator>>(sf::Packet& packet, Status& status) {
  int id;
  int lay_id;
  packet >> status.angle >> status.states >> status.animation_id >> id >>
      status.is_removed >> lay_id >> status.position.x >> status.position.y;

  status.id = static_cast<size_t>(id);
  status.lay_id = static_cast<size_t>(lay_id);
  return packet;
}

sf::Packet& operator<<(sf::Packet& packet, std::vector<Status>& status) {
  packet << static_cast<int>(status.size());
  for (auto& it : status) {
    packet << it;
  }
  return packet;
}

sf::Packet& operator>>(sf::Packet& packet, std::vector<Status>& status) {
  int size;
  packet >> size;
  status.resize(size);
  for (size_t i = 0; i < static_cast<size_t>(size); ++i) {
    Status tmp;
    packet >> tmp;
    status[i] = tmp;
  }
  return packet;
}

sf::Packet& operator<<(sf::Packet& packet,
                       std::vector<std::vector<Status>>& status) {
  packet << static_cast<int>(status.size());
  for (auto& it : status) {
    packet << it;
  }
  return packet;
}

sf::Packet& operator>>(sf::Packet& packet,
                       std::vector<std::vector<Status>>& status) {
  int size;
  packet >> size;
  status.resize(size);
  for (size_t i = 0; i < static_cast<size_t>(size); ++i) {
    std::vector<Status> tmp;
    packet >> tmp;
    status[i].assign(tmp.begin(), tmp.end());
  }
  return packet;
}
