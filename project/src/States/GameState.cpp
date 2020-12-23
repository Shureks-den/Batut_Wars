#include "States/GameState.h"

#include "Ship.h"
#include "Enemy.h"
#include "Massive.h"
#include "Bullet.h"
#include "Comet.h"
#include "IcePlanet.h"

#include <memory>

GameState::GameState(StateStack& stack, Context context) : GameStateBase(stack, context),
                                                           _world() {
    // ИГРОК
    context.music->play(Music::MissionTheme);
    auto main_ship = std::unique_ptr<engine::MoveAble>(new space::Ship);  // TODO(ANDY) инициализация карты
    main_ship->set_position(sf::Vector2f(1000, 1000));
    main_ship->rotate(engine::as_radian(- 90));
    _world.push_player(std::move(main_ship));
    _render.set_player_id(0);

    // ЧЕРНАЯ ДЫРОЧКА
    auto blackhole = std::unique_ptr<space::Massive>(new space::Massive(100, 125.0f));
    blackhole->set_position(sf::Vector2f(600, 700));
    _world.push_back(std::move(blackhole));
    auto blackhole_2 = std::unique_ptr<space::Massive>(new space::Massive(100, 125.0f));
    blackhole_2->set_position(sf::Vector2f(1300, 1300));
    _world.push_back(std::move(blackhole_2));

    // ХОЛОДНОЕ СЕРДЦЕ
    auto ice_planet_1 = std::unique_ptr<space::IcePlanet>(new space::IcePlanet(125.0f));
    ice_planet_1->set_position(sf::Vector2f(1600, 1600));
    _world.push_back(std::move(ice_planet_1));
    auto ice_planet_2 = std::unique_ptr<space::IcePlanet>(new space::IcePlanet(125.0f));
    ice_planet_2->set_position(sf::Vector2f(100, 2000));
    _world.push_back(std::move(ice_planet_2));

    // КОМЕТЫ
    auto comet_1 = std::unique_ptr<space::Comet>(new space::Comet(engine::Vector(50, 50)));
    comet_1->set_position(sf::Vector2f(2200, 1000));
    _world.push_back(std::move(comet_1));
    auto comet_2 = std::unique_ptr<space::Comet>(new space::Comet(engine::Vector(70, 70)));
    comet_2->set_position(sf::Vector2f(2300, 1000));
    _world.push_back(std::move(comet_2));
    auto comet_3 = std::unique_ptr<space::Comet>(new space::Comet(engine::Vector(100, 100)));
    comet_3->set_position(sf::Vector2f(2400, 1000));
    _world.push_back(std::move(comet_3));
    auto comet_4 = std::unique_ptr<space::Comet>(new space::Comet(engine::Vector(-50, 50)));
    comet_4->set_position(sf::Vector2f(0, 0));
    _world.push_back(std::move(comet_4));
    auto comet_5 = std::unique_ptr<space::Comet>(new space::Comet(engine::Vector(80, 0)));
    comet_5->set_position(sf::Vector2f(10, 100));
    _world.push_back(std::move(comet_5));
    auto comet_6 = std::unique_ptr<space::Comet>(new space::Comet(engine::Vector(0, 100)));
    comet_6->set_position(sf::Vector2f(200, 1040));
    _world.push_back(std::move(comet_6));

    // ТУПОЙ БОТ
    auto bot1 = std::unique_ptr<space::Enemy>(new space::Enemy);
    bot1->set_position(sf::Vector2f(1500, 1000));
    _world.push_back(std::move(bot1));

    auto bot2 = std::unique_ptr<space::Enemy>(new space::Enemy);
    bot2->set_position(sf::Vector2f(2000, 2500));
    _world.push_back(std::move(bot2));

    auto bot3 = std::unique_ptr<space::Enemy>(new space::Enemy);
    bot3->set_position(sf::Vector2f(3750, 1000));
    _world.push_back(std::move(bot3));

    auto bot4 = std::unique_ptr<space::Enemy>(new space::Enemy);
    bot4->set_position(sf::Vector2f(4000, 500));
    _world.push_back(std::move(bot4));

    _render.inicilize(_world.get_status());
}

bool GameState::update(sf::Time dt) {
    _world.update(dt);
    _render.set_status(_world.get_status());  // Обмен данными между _render и _world
    _render.update(dt);
    update_statistic(dt);
    
    if (!_world.has_alive_player()) {
        _player.set_mission_status(Player::MissionStatus::MissionFailure);
        requestStackPush(States::ENDGAME);
    } else if (_world.finished_mission()) {
        _player.set_mission_status(Player::MissionStatus::MissionSuccess);
        requestStackPush(States::ENDGAME);
    }
    std::queue<Player::Action> actions;
    _player.handle_realtime_event(actions);

    auto &world_actions = _world.get_actions();
    while (!actions.empty()) {
        world_actions.push(std::make_pair(0, actions.front()));
        actions.pop();
    }

    return !_world.is_over();
}

bool GameState::handle_event(const sf::Event& event) {
    std::queue<Player::Action> actions;
    _player.handle_event(event, actions);

    auto &world_actions = _world.get_actions();
    while (!actions.empty()) {
        world_actions.push(std::make_pair(0, actions.front()));
        actions.pop();
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        requestStackPush(States::PAUSE);
    }

    return true;
}
