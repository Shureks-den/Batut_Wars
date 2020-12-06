#ifndef SFML_LESSON_5_STATE_H
#define SFML_LESSON_5_STATE_H

#include "StateIdentifiers.h"
#include "ResourceIdentifiers.h"

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>


namespace sf
{
    class RenderWindow;
}

class StateStack;
class Player;

class State {
public:
    typedef std::unique_ptr<State> Ptr;

    struct Context {
        Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Player& player); // тут заменить нашей загрузкой текстур
        sf::RenderWindow* window;
        TextureHolder* textures;
        FontHolder* fonts;
        Player*	 player;
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
    StateStack *mStack;
    Context mContext;
};


#endif //SFML_LESSON_5_STATE_H
