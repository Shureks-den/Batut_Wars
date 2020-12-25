#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <queue>

#include "Player.h"
#include "Status.h"
#include "MissionStatus.h"

sf::Packet& operator<<(sf::Packet& packet, animation::Id &id);
sf::Packet& operator>>(sf::Packet& packet, animation::Id &id);


sf::Packet& operator<<(sf::Packet& packet, std::queue<Player::Action>& actions);
sf::Packet& operator>>(sf::Packet& packet, std::queue<Player::Action>& actions);

sf::Packet& operator<<(sf::Packet& packet, std::vector<bool>& bool_vector);
sf::Packet& operator>>(sf::Packet& packet, std::vector<bool>& bool_vector);

sf::Packet& operator<<(sf::Packet& packet, Mission &mission);
sf::Packet& operator>>(sf::Packet& packet, Mission &mission);

sf::Packet& operator<<(sf::Packet& packet, std::vector<Mission> &mission);
sf::Packet& operator>>(sf::Packet& packet, std::vector<Mission> &mission);

sf::Packet& operator<<(sf::Packet& packet, Status& status);
sf::Packet& operator>>(sf::Packet& packet, Status& status);

sf::Packet& operator<<(sf::Packet& packet, std::vector<Status>& status);
sf::Packet& operator>>(sf::Packet& packet, std::vector<Status>& status);

sf::Packet& operator<<(sf::Packet& packet, std::vector<std::vector<Status>>& status);
sf::Packet& operator>>(sf::Packet& packet, std::vector<std::vector<Status>>& status);
