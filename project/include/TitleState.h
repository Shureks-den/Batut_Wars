#pragma once

#include "State.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class TitleState : public State {
public:
    TitleState(StateStack &stack, Context context);
    ~TitleState() = default;

    void draw() override;
    bool update(sf::Time dt) override;
    bool handleEvent(const sf::Event& event) override;


private:
    sf::Sprite _BackgroundSprite;
    sf::Text _Text;
    bool mShowText;
    sf::Time mTextEffectTime;
};
