#pragma once

#include <memory>
#include <utility>
#include <thread>

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include "StateIdentifiers.h"
#include "Holder.h"
#include "Player.h"
#include "Client.h"
#include "Server.h"
#include "Music.h"
#include "MissionStatus.h"

class StateStack;

class State {
 public:
    typedef std::unique_ptr<State> Ptr;

    class Context {
     public:
        Context(sf::RenderWindow &window,
                textures::Holder &textures,
                fonts::Holder &fonts,
                Player &player,
                std::pair<sf::IpAddress, uint16_t> &network_info,
                network::Client &client,
                network::Server &server,
                std::thread &server_thread,
                std::thread &client_thread,
                MusicPlayer &music,
                Mission &mission_status);
        
        sf::RenderWindow *window;
        textures::Holder *textures;
        fonts::Holder *fonts;
        Player* player;
        std::pair<sf::IpAddress, uint16_t> *network_info;
        network::Client *client;
        network::Server *server;
        std::thread *server_thread;
        std::thread *client_thread;
        MusicPlayer *music;
        Mission *mission_status;
    };

 public:
    State(StateStack& stack, Context context);
    virtual ~State() = default;
    virtual void draw() = 0;
    virtual bool update(sf::Time dt) = 0;
    virtual bool handle_event(const sf::Event& event) = 0;

 protected:
    void requestStackPush(States::Id state_id);
    void requestStackPop();
    void requestStateClear();
    Context getContext() const;

 private:
    StateStack *_stack;
    Context _context;
};
