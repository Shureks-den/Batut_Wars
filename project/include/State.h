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
    virtual ~State();
    virtual void draw() = 0;
    virtual bool update(sf::Time dt) = 0;
    virtual bool handleEvent(const sf::Event& event) = 0;

 protected:
    void requestStackPush(States::ID stateID);
    void requestStackPop();
    void requestStateClear();
    Context getContext() const;

 private:
    StateStack *_Stack;
    Context _Context;
};
