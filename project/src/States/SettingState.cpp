#include "States/SettingState.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Holder.h"
#include "Utility.h"

SettingsState::SettingsState(StateStack& stack, Context context)
              : State(stack, context),
                _container() {
    const sf::Texture* texture = context.textures->get(textures::Id::MENU_BACKGROUND);
    _background.setTexture(texture);
    sf::Vector2u size = context.window->getSize();
    sf::Vector2f menu_size;
    menu_size.x = static_cast<float>(size.x);
    menu_size.y = static_cast<float>(size.y);
    _background.setSize(menu_size);
    _background.setPosition(0, 0);

    float y_start = (menu_size.y - 50 * 6) / 2;

    add_button_label(Player::MOVE_LEFT, y_start, "Rotate Left", context);  // TODO(ANDY) позиция
    add_button_label(Player::MOVE_RIGHT, y_start + 50, "Rotate Right   ", context);  // TODO(SOMEONE) пофиксить шрифты
    add_button_label(Player::MOVE_FORWARD, y_start + 100, "Move Up", context);
    add_button_label(Player::MOVE_BACKWARD, y_start + 150, "Move Down", context);
    add_button_label(Player::FIRE, y_start + 200.f, "Fire", context);

    auto back_button = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    back_button->setPosition(context.window->getSize().x * 0.5f - 100.f, y_start + 300);
    back_button->set_text("Back");
    back_button->set_callback(std::bind(&SettingsState::requestStackPop, this));

    _container.pack(back_button);

    update_labels();
}

void SettingsState::draw() {
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    window.draw(_background);
    window.draw(_container);
}

bool SettingsState::update(sf::Time) { return true; }

bool SettingsState::handle_event(const sf::Event& event) {
  bool isKeyBinding = false;

  for (size_t action = 0; action < Player::COUNT; ++action) {
    if (_binding_buttons[action]->is_active()) {
      isKeyBinding = true;
      if (event.type == sf::Event::KeyReleased) {
        getContext().player->assign_key(static_cast<Player::Action>(action),
                                        event.key.code);
        _binding_buttons[action]->deactivate();
      }
      break;
    }
  }

  if (isKeyBinding) {
    update_labels();
  } else {
    _container.handle_event(event);
  }

  return false;
}

void SettingsState::update_labels() {
  Player& player = *getContext().player;

  for (size_t i = 0; i < Player::COUNT; ++i) {
    sf::Keyboard::Key key = player.get_key(static_cast<Player::Action>(i));
    _binding_labels[i]->set_text(toString(key));
  }
}

void SettingsState::add_button_label(Player::Action action, float y,
                                     const std::string& text, Context context) {
  _binding_buttons[action] =
      std::make_shared<GUI::Button>(*context.fonts, *context.textures);
  _binding_buttons[action]->setPosition(
      context.window->getSize().x * 0.5f - 100.f, y);  // TODO(ANDY) позиция
  _binding_buttons[action]->set_text(text);
  _binding_buttons[action]->set_toggle(true);

  _binding_labels[action] = std::make_shared<GUI::Label>("", *context.fonts);
  _binding_labels[action]->setPosition(
      context.window->getSize().x * 0.5f + 50.f,
      y + 15.f);  // TODO(ANDY) позиция

  _container.pack(_binding_buttons[action]);
  _container.pack(_binding_labels[action]);
}
