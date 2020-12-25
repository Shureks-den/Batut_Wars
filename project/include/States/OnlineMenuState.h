#pragma once

#include "Container.h"
#include "State.h"
#include "Textbox.h"

class OnlineMenuState : public State {
 public:
    OnlineMenuState(StateStack& stack, Context context);
    ~OnlineMenuState() = default;

    void draw() override;
    bool update(sf::Time dt) override;
    bool handle_event(const sf::Event& event) override;

 private:
    sf::RectangleShape _background;
    GUI::Container _container;

    std::shared_ptr<GUI::Textbox> ip_textbox;
    std::shared_ptr<GUI::Textbox> port_textbox;

    int start_client();
    void start_server();
};
