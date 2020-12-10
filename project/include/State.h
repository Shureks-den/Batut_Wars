#pragma once

#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include "StateIdentifiers.h"
#include "Holder.h"
#include "Player.h"

class StateStack;

class State {
 public:
    typedef std::unique_ptr<State> Ptr;

    class Context {
     public:
        Context(sf::RenderWindow &window, textures::Holder &textures, fonts::Holder &fonts, Player &player);  // тут заменить нашей загрузкой текстур
        sf::RenderWindow *window;
        textures::Holder *textures;
        fonts::Holder *fonts;
        Player* player;
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
