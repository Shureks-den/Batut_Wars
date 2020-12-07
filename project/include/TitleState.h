#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "State.h"

class TitleState : public State {
 public:
    TitleState(StateStack &stack, Context context);
    ~TitleState() = default;

    void draw() override;
    bool update(sf::Time dt) override;
    bool handle_event(const sf::Event& event) override;

 private:
    sf::Sprite _background;
    sf::Text _text;
    bool _ShowText;
    sf::Time _textEffectTime;
};
