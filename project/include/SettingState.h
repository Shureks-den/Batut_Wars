#pragma once

#include <array>
#include <string>

#include <SFML/Graphics/RectangleShape.hpp>
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
    bool handle_event(const sf::Event& event) override;


 private:
    void update_labels();
    void add_button_label(Player::Action action, float y, const std::string& text, Context context);

 private:
    sf::RectangleShape _background;
    sf::IntRect _uv_rect;
    GUI::Container _container;
    std::array<GUI::Button::Ptr, Player::COUNT> _binding_buttons;
    std::array<GUI::Label::Ptr, Player::COUNT> _binding_labels;
};
