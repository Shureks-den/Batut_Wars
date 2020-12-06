#pragma once

#include "world.h"
#include "player.h"
#include "render.h"
#include "StateStack.h"
#include "holder.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class Game : sf::NonCopyable {
 public:
    Game();
    ~Game() = default;
    void run();

 private:
    void draw();
    bool update(sf::Time dt);
    void render(sf::Time dt);
    bool handle_event(const sf::Event& event);
    void get_input();

    void update_statistic(sf::Time time);

    void registerStates();

    sf::RenderWindow _window;
    Player _player;  // Читать команды игрока

    StateStack mStateStack;
    texture::Holder mHolder;
    fonst::Holder mFonts;

    static const sf::Time _time_per_frame;
};
