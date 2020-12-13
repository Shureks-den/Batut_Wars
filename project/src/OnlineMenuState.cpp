#include "OnlineMenuState.h"

#include <memory>
#include <iostream>

#include "Textbox.h"
#include "Button.h"
#include "Server.h"

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
        //requestStackPush(States::Id::CLIENT_WAITING);
    });
    // TODO(ANDY) по нажанию - запуск сервера в отдельном потоке, вывод ip и port в текстбоксы,
    // запись ip и port в context.network_info (мб бесполезное поле - убрать)
    // запуск server в context.server_thread
    // context.client->connetc(ip, port)
    // Скорее всего, отдельный стейт на ожидние подключений

    auto connect_button = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    connect_button->setPosition(size.x * 0.5f - 100.f, size.y * 0.5f + 25);
    connect_button->set_text("Connect");
    connect_button->set_callback([this] () {
        start_client();
        //requestStackPush(States::Id::CLIENT_WAITING);
    });
    // TODO(ANDY) по нажанию - считать ip и port, client->connect(ip, port)
    // Запустить стейт ожидания онлайн игры

    auto back_button = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    back_button->setPosition(size.x * 0.5f - 100.f, size.y * 0.5f + 75);
    back_button->set_text("Back");
    back_button->set_callback([this] () {
        requestStackPop();
    });

    _container.pack(ip_textbox);
    _container.pack(port_textbox);
    _container.pack(server_button);
    _container.pack(connect_button);
    _container.pack(back_button);
}

bool OnlineMenuState::update(sf::Time) {
    return true;
}

void OnlineMenuState::draw() {
    sf::RenderWindow& window = *getContext().window;

    window.draw(_background);
    window.draw(_container);
}

bool OnlineMenuState::handle_event(const sf::Event& event) {
    _container.handle_event(event);
    return false;
}

void OnlineMenuState::start_client() {
    std::cout << "Before connect1";
    getContext().network_info->first = ip_textbox->get_text();  // TODO(ANDY) ловить исключения
    std::cout << "Before connect2";
    getContext().network_info->second = static_cast<uint16_t>(std::stoi(port_textbox->get_text()));
    std::cout << "Before connect3";
    if (getContext().client->connect(*getContext().network_info)) {
        requestStackPush(States::Id::ONLINE);
        std::cout << "Connect is good";

    } else {
        std::cout << "ACCESS DENIED" << std::endl;  // TODO(ANDY) визуальный вывод
    }
}

void OnlineMenuState::start_server() {
    *getContext().server_thread = std::thread([this]() {
        getContext().server->run();
    });
    getContext().server_thread->detach();
    *getContext().network_info = getContext().server->get_adress();
    std::cout << "START SERVER" << std::endl;
    std::cout << getContext().network_info->first << std::endl;
    std::cout << getContext().network_info->second << std::endl;
    if (getContext().client->connect(*getContext().network_info)) {
        requestStackPush(States::Id::ONLINE);
    } else {
        std::cout << "ACCESS DENIED" << std::endl;  // TODO(ANDY) визуальный вывод
    }
}