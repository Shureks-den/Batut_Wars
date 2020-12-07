#include "SettingState.h"
#include "Holder.h"
#include "Utility.h"

#include <SFML/Graphics/RenderWindow.hpp>


SettingsState::SettingsState(StateStack& stack, Context context)
        : State(stack, context)
        , _GUIContainer()
{
    _BackgroundSprite.setTexture(*context.textures->get(textures::Id::MENU_BACKGROUND));

    // Build key binding buttons and labels
    addButtonLabel(Player::MOVE_LEFT,  150.f, "Rotate Left", context);  // TODO(ANDY) позиция
    addButtonLabel(Player::MOVE_RIGHT, 200.f, "Rotate Right", context);
    addButtonLabel(Player::MOVE_FORWARD,    250.f, "Move Up", context);
    addButtonLabel(Player::MOVE_BACKWARD,  300.f, "Move Down", context);

    updateLabels();

    auto backButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    backButton->setPosition(20.f, 20.f);
    backButton->setText("Back");
    backButton->setCallback(std::bind(&SettingsState::requestStackPop, this));

    _GUIContainer.pack(backButton);
}

void SettingsState::draw()
{
    sf::RenderWindow& window = *getContext().window;

    window.draw(_BackgroundSprite);
    window.draw(_GUIContainer);
}

bool SettingsState::update(sf::Time)
{
    return true;
}

bool SettingsState::handleEvent(const sf::Event& event)
{
    bool isKeyBinding = false;

    // Iterate through all key binding buttons to see if they are being pressed, waiting for the user to enter a key
    for (std::size_t action = 0; action < Player::COUNT; ++action)
    {
        if (_BindingButtons[action]->isActive())
        {
            isKeyBinding = true;
            if (event.type == sf::Event::KeyReleased)
            {
                getContext().player->assign_key(static_cast<Player::Action>(action), event.key.code);
                _BindingButtons[action]->deactivate();
            }
            break;
        }
    }

    // If pressed button changed key bindings, update labels; otherwise consider other buttons in container
    if (isKeyBinding)
        updateLabels();
    else
        _GUIContainer.handleEvent(event);

    return false;
}

void SettingsState::updateLabels() {
    Player& player = *getContext().player;

    for (std::size_t i = 0; i < Player::COUNT; ++i) {
        sf::Keyboard::Key key = player.get_key(static_cast<Player::Action>(i));
        _BindingLabels[i]->setText(toString(key));
    }
}

void SettingsState::addButtonLabel(Player::Action action, float y, const std::string& text, Context context) {
    _BindingButtons[action] = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    _BindingButtons[action]->setPosition(40, y); // TODO(ANDY) позиция
    _BindingButtons[action]->setText(text);
    _BindingButtons[action]->setToggle(true);

    _BindingLabels[action] = std::make_shared<GUI::Label>("", *context.fonts);
    _BindingLabels[action]->setPosition(40.f + 150.f, y + 15.f); // TODO(ANDY) позиция

    _GUIContainer.pack(_BindingButtons[action]);
    _GUIContainer.pack(_BindingLabels[action]);
}

