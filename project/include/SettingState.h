#pragma once

#include <array>
#include <string>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "State.h"
#include "Player.h"
#include "Container.h"
#include "Button.h"
#include "Label.h"

class SettingsState : public State {
 public:
    SettingsState(StateStack& stack, Context context);
    ~SettingsState() = default;

    void draw() override;
    bool update(sf::Time dt) override;
    bool handleEvent(const sf::Event& event) override;


 private:
    void updateLabels();
    void addButtonLabel(Player::Action action, float y, const std::string& text, Context context);

 private:
    sf::Sprite _BackgroundSprite;
    GUI::Container _GUIContainer;
    std::array<GUI::Button::Ptr, Player::COUNT> _BindingButtons;
    std::array<GUI::Label::Ptr, Player::COUNT> _BindingLabels;
};
