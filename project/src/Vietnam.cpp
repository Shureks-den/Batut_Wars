#include "Vietnam.h"

#include <utility>
#include <memory>

void welcome_to_vietnam(World &world){
    // ЧЕРНАЯ ДЫРОЧКА
    auto blackhole = std::make_unique<space::Massive>(100, 115.0f);
    blackhole->set_position(sf::Vector2f(600, 700));
    world.push_back(std::move(blackhole));
    auto blackhole_2 = std::make_unique<space::Massive>(100, 115.0f);
    blackhole_2->set_position(sf::Vector2f(1300, 1300));
    world.push_back(std::move(blackhole_2));
    auto blackhole_3 = std::make_unique<space::Massive>(100, 115.0f);
    blackhole_3->set_position(sf::Vector2f(4000, 400));
    world.push_back(std::move(blackhole_3));
    auto blackhole_4 = std::make_unique<space::Massive>(100, 115.0f);
    blackhole_4->set_position(sf::Vector2f(200, 3000));
    world.push_back(std::move(blackhole_4));
    auto blackhole_5 = std::make_unique<space::Massive>(100, 115.0f);
    blackhole_5->set_position(sf::Vector2f(2000, 2000));
    world.push_back(std::move(blackhole_5));
    auto blackhole_6 = std::make_unique<space::Massive>(100, 115.0f);
    blackhole_6->set_position(sf::Vector2f(3500, 3400));
    world.push_back(std::move(blackhole_6));
    auto blackhole_7 = std::make_unique<space::Massive>(100, 115.0f);
    blackhole_7->set_position(sf::Vector2f(1000, 600));
    world.push_back(std::move(blackhole_7));
    auto blackhole_8 = std::make_unique<space::Massive>(100, 115.0f);
    blackhole_8->set_position(sf::Vector2f(3500, 3400));
    world.push_back(std::move(blackhole_8));

    // ХОЛОДНОЕ СЕРДЦЕ
    auto ice_planet_1 = std::make_unique<space::IcePlanet>(115.0f);
    ice_planet_1->set_position(sf::Vector2f(1600, 1600));
    world.push_back(std::move(ice_planet_1));
    auto ice_planet_2 = std::make_unique<space::IcePlanet>(115.0f);
    ice_planet_2->set_position(sf::Vector2f(100, 2000));
    world.push_back(std::move(ice_planet_2));
    auto ice_planet_3 = std::make_unique<space::IcePlanet>(115.0f);
    ice_planet_3->set_position(sf::Vector2f(2000, 1000));
    world.push_back(std::move(ice_planet_3));
    auto ice_planet_4 = std::make_unique<space::IcePlanet>(115.0f);
    ice_planet_4->set_position(sf::Vector2f(3000, 3000));
    world.push_back(std::move(ice_planet_4));
    auto ice_planet_5 = std::make_unique<space::IcePlanet>(115.0f);
    ice_planet_5->set_position(sf::Vector2f(1456, 500));
    world.push_back(std::move(ice_planet_5));
    auto ice_planet_6 = std::make_unique<space::IcePlanet>(115.0f);
    ice_planet_6->set_position(sf::Vector2f(2666, 3500));
    world.push_back(std::move(ice_planet_6));
    auto ice_planet_7 = std::make_unique<space::IcePlanet>(115.0f);
    ice_planet_7->set_position(sf::Vector2f(400, 3500));
    world.push_back(std::move(ice_planet_7));
    auto ice_planet_8 = std::make_unique<space::IcePlanet>(115.0f);
    ice_planet_8->set_position(sf::Vector2f(3500, 4000));
    world.push_back(std::move(ice_planet_8));

    // КОМЕТЫ
    auto comet_1 = std::make_unique<space::Comet>(engine::Vector(50, 50));
    comet_1->set_position(sf::Vector2f(2200, 1000));
    world.push_back(std::move(comet_1));
    auto comet_2 = std::make_unique<space::Comet>(engine::Vector(70, 70));
    comet_2->set_position(sf::Vector2f(2300, 1000));
    world.push_back(std::move(comet_2));
    auto comet_3 = std::make_unique<space::Comet>(engine::Vector(100, 100));
    comet_3->set_position(sf::Vector2f(2400, 1000));
    world.push_back(std::move(comet_3));
    auto comet_4 = std::make_unique<space::Comet>(engine::Vector(- 50, 50));
    comet_4->set_position(sf::Vector2f(0, 0));
    world.push_back(std::move(comet_4));
    auto comet_5 = std::make_unique<space::Comet>(engine::Vector(80, 0));
    comet_5->set_position(sf::Vector2f(10, 100));
    world.push_back(std::move(comet_5));
    auto comet_6 = std::make_unique<space::Comet>(engine::Vector(0, 100));
    comet_6->set_position(sf::Vector2f(200, 1040));
    world.push_back(std::move(comet_6));
    auto comet_7 = std::make_unique<space::Comet>(engine::Vector(50, 50));
    comet_7->set_position(sf::Vector2f(600, 3000));
    world.push_back(std::move(comet_7));
    auto comet_8 = std::make_unique<space::Comet>(engine::Vector(100, -30));
    comet_8->set_position(sf::Vector2f(2000, 540));
    world.push_back(std::move(comet_8));
    auto comet_9 = std::make_unique<space::Comet>(engine::Vector(30, 30));
    comet_9->set_position(sf::Vector2f(50, 600));
    world.push_back(std::move(comet_9));
    auto comet_10 = std::make_unique<space::Comet>(engine::Vector(100, 100));
    comet_10->set_position(sf::Vector2f(300, 666));
    world.push_back(std::move(comet_10));
    auto comet_11 = std::make_unique<space::Comet>(engine::Vector(-50, 100));
    comet_11->set_position(sf::Vector2f(2000, 1500));
    world.push_back(std::move(comet_11));
    auto comet_12 = std::make_unique<space::Comet>(engine::Vector(0, 100));
    comet_12->set_position(sf::Vector2f(2000, 2500));
    world.push_back(std::move(comet_12));
    auto comet_13 = std::make_unique<space::Comet>(engine::Vector(100, -70));
    comet_13->set_position(sf::Vector2f(100, 3400));
    world.push_back(std::move(comet_13));

    // ТУПОЙ БОТ
    auto bot1 = std::make_unique<space::Enemy>();
    bot1->set_position(sf::Vector2f(1500, 1000));
    world.push_back(std::move(bot1));

    auto bot2 = std::make_unique<space::Enemy>();
    bot2->set_position(sf::Vector2f(2000, 2500));
    world.push_back(std::move(bot2));

    auto bot3 = std::make_unique<space::Enemy>();
    bot3->set_position(sf::Vector2f(3750, 1000));
    world.push_back(std::move(bot3));

    auto bot4 = std::make_unique<space::Enemy>();
    bot4->set_position(sf::Vector2f(4000, 500));
    world.push_back(std::move(bot4));

    auto bot5 = std::make_unique<space::Enemy>();
    bot5->set_position(sf::Vector2f(200, 200));
    world.push_back(std::move(bot5));

    auto bot6 = std::make_unique<space::Enemy>();
    bot6->set_position(sf::Vector2f(100, 4000));
    world.push_back(std::move(bot6));

    auto bot7 = std::make_unique<space::Enemy>();
    bot7->set_position(sf::Vector2f(4230, 4140));
    world.push_back(std::move(bot7));

    auto bot8 = std::make_unique<space::Enemy>();
    bot8->set_position(sf::Vector2f(3333, 660));
    world.push_back(std::move(bot8));

    auto bot9 = std::make_unique<space::Enemy>();
    bot9->set_position(sf::Vector2f(1500, 2345));
    world.push_back(std::move(bot9));

    auto bot10 = std::make_unique<space::Enemy>();
    bot10->set_position(sf::Vector2f(1500, 3042));
    world.push_back(std::move(bot10));

    auto bot11 = std::make_unique<space::Enemy>();
    bot11->set_position(sf::Vector2f(125, 3126));
    world.push_back(std::move(bot11));

    auto bot12 = std::make_unique<space::Enemy>();
    bot12->set_position(sf::Vector2f(2532, 3864));
    world.push_back(std::move(bot12));

    auto bot13 = std::unique_ptr<space::Enemy>(new space::Enemy);
    bot13->set_position(sf::Vector2f(222, 3264));
    world.push_back(std::move(bot13));
}