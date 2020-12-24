#include "States/MenuState.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Network/IpAddress.hpp>

#include "Button.h"
#include "Holder.h"
#include "Utility.h"

MenuState::MenuState(StateStack& stack, Context context)
    : State(stack, context), _container() {
  context.music->play(Music::MenuTheme);
  const sf::Texture* texture =
      context.textures->get(textures::Id::MENU_BACKGROUND);
  _background.setTexture(texture);
  sf::Vector2u size = context.window->getSize();
  sf::Vector2f menu_size;
  menu_size.x = size.x * 1.f;
  menu_size.y = size.y * 1.f;
  _background.setSize(menu_size);
  _background.setPosition(0, 0);

  auto play_button =
      std::make_shared<GUI::Button>(*context.fonts, *context.textures);
  play_button->setPosition(size.x * 0.5f - 100.f,
                           size.y * 0.5f - 100);  // TODO(ANDY) размеры
  play_button->set_text("Play");
  play_button->set_callback([this]() {
    requestStackPop();
    requestStackPush(States::GAME);
  });

    auto client_button = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    client_button->setPosition(size.x * 0.5f - 100.f, size.y * 0.5f - 50);
    client_button->set_text("Online game");
    client_button->set_callback([this] () {
        requestStackPop();
        requestStackPush(States::ONLINE_MENU);
    });

  auto settings_button =
      std::make_shared<GUI::Button>(*context.fonts, *context.textures);
  settings_button->setPosition(size.x * 0.5f - 100.f, size.y * 0.5f);
  settings_button->set_text("Settings");
  settings_button->set_callback(
      [this]() { requestStackPush(States::SETTINGS); });

  auto exit_button =
      std::make_shared<GUI::Button>(*context.fonts, *context.textures);
  exit_button->setPosition(size.x * 0.5f - 100.f, size.y * 0.5f + 50);
  exit_button->set_text("Exit");
  exit_button->set_callback([this]() { requestStackPop(); });

  _container.pack(play_button);
  _container.pack(client_button);
  _container.pack(settings_button);
  _container.pack(exit_button);
}

void MenuState::draw() {
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

  window.draw(_background);
  window.draw(_container);
}

bool MenuState::update(sf::Time) { return true; }

bool MenuState::handle_event(const sf::Event& event) {
  _container.handle_event(event);
  return false;
}
