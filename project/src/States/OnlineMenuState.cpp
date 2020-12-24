#include "States/OnlineMenuState.h"

#include <iostream>
#include <memory>

#include "Button.h"
#include "Server.h"
#include "Textbox.h"

static constexpr int FAIL = 0;
static constexpr int SUCCESS = 1;

OnlineMenuState::OnlineMenuState(StateStack& stack, Context context)
            : State(stack, context),
              _container() {
    const sf::Texture* texture = context.textures->get(textures::Id::MENU_BACKGROUND);
    _background.setTexture(texture);
    sf::Vector2u size = context.window->getSize();
    sf::Vector2f menu_size;
    menu_size.x = size.x * 1.f;
    menu_size.y = size.y * 1.f;
    _background.setSize(menu_size);
    _background.setPosition(0, 0);

    ip_textbox = std::make_shared<GUI::Textbox>(*context.fonts, *context.textures);
    ip_textbox->setPosition(size.x * 0.5f - 100.f, size.y * 0.5f - 125);
    ip_textbox->set_toggle(true);
    ip_textbox->set_opening("ip: ");

    port_textbox = std::make_shared<GUI::Textbox>(*context.fonts, *context.textures);
    port_textbox->setPosition(size.x * 0.5f - 100.f, size.y * 0.5f - 75);
    port_textbox->set_toggle(true);
    port_textbox->set_opening("port: ");

    auto server_button = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    server_button->setPosition(size.x * 0.5f - 100.f, size.y * 0.5f - 25);
    server_button->set_text("Create server");
    server_button->set_callback([this] () {
        start_server();
        if (start_client() == SUCCESS) {
            requestStackPush(States::Id::SERVER_WAITING);
        }
    });

    auto connect_button = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    connect_button->setPosition(size.x * 0.5f - 100.f, size.y * 0.5f + 25);
    connect_button->set_text("Connect");
    connect_button->set_callback([this] () {
        if (start_client() == SUCCESS) {
            requestStackPush(States::Id::WAITING);
        }
    });

    auto back_button = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    back_button->setPosition(size.x * 0.5f - 100.f, size.y * 0.5f + 75);
    back_button->set_text("Back");
    back_button->set_callback([this] () {
        requestStackPop();
        requestStackPush(States::Id::MENU);
    });

    _container.pack(ip_textbox);
    _container.pack(port_textbox);
    _container.pack(server_button);
    _container.pack(connect_button);
    _container.pack(back_button);
}

bool OnlineMenuState::update(sf::Time) { return true; }

void OnlineMenuState::draw() {
    sf::RenderWindow& window = *getContext().window;
    // window.setView(window.getDefaultView());

  window.draw(_background);
  window.draw(_container);
}

bool OnlineMenuState::handle_event(const sf::Event& event) {
  _container.handle_event(event);
  return false;
}

int OnlineMenuState::start_client() {
    getContext().network_info->first = ip_textbox->get_text();  // TODO(ANDY) ловить исключения
    getContext().network_info->second = static_cast<uint16_t>(std::stoi(port_textbox->get_text()));

    bool is_connected = getContext().client->connect(*getContext().network_info);
    if (!is_connected) {
        return FAIL;
    }

    *getContext().client_thread = std::thread([this]() {
        getContext().client->run();
    });
    getContext().client_thread->detach();

    return SUCCESS;
}

void OnlineMenuState::start_server() {
    *getContext().server_thread = std::thread([this]() {
        getContext().server->run();
    });
    getContext().server_thread->detach();
    sf::sleep(sf::seconds(1));
    *getContext().network_info = getContext().server->get_adress();
    ip_textbox->set_string(getContext().network_info->first.toString());
    port_textbox->set_string(std::to_string(getContext().network_info->second));
    std::cout << "START SERVER" << std::endl;
    std::cout << getContext().network_info->first << std::endl;
    std::cout << getContext().network_info->second << std::endl;
}