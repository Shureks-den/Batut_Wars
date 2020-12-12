#include "OnlineMenuState.h"

#include "Textbox.h"
#include "Button.h"

#include <memory>

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

    auto ip_textbox = std::make_shared<GUI::Textbox>(*context.fonts, *context.textures);
    ip_textbox->setPosition(size.x * 0.5f - 100.f, size.y * 0.5f - 125);

    auto port_textbox = std::make_shared<GUI::Textbox>(*context.fonts, *context.textures);
    port_textbox->setPosition(size.x * 0.5f - 100.f, size.y * 0.5f - 75);

    auto server_button = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    server_button->setPosition(size.x * 0.5f - 100.f, size.y * 0.5f - 25);
    server_button->set_text("Create server");
    // TODO(ANDY) по нажанию - запуск сервера в отдельном потоке, вывод ip и port в текстбоксы,
    // запись ip и port в context.network_info (мб бесполезное поле - убрать)
    // запуск server в context.server_thread
    // context.client->connetc(ip, port)
    // Скорее всего, отдельный стейт на ожидние подключений

    auto connect_button = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    connect_button->setPosition(size.x * 0.5f - 100.f, size.y * 0.5f + 25);
    connect_button->set_text("Connect");
    // TODO(ANDY) по нажанию - считать ip и port, client->connect(ip, port)
    // Запустить стейт ожидания онлайн игры

    auto back_button = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    back_button->setPosition(size.x * 0.5f - 100.f, size.y * 0.5f + 75);
    back_button->set_text("Back");
    //back_button->set_callback(std::bind(&OnlineMenuState::requestStackPop, this));

    // sf::String ip = dynamic_cast<<std::shared_ptr<GUI::Textbox>>>(_container[0])->get_text();

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
    return true;
}
