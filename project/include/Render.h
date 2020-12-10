#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "Animation.h"
#include "Status.h"
#include "Layer.h"
#include "AnimationCreator.h"

class Render: private sf::NonCopyable {
 public:
    explicit Render(sf::RenderWindow& window);
    void update(sf::Time dt);
    void set_status(const std::vector<std::vector<Status>> &status);
    void draw();
    void inicilize(const std::vector<std::vector<Status>> &status);
    sf::View& get_view();
    void set_player_id(size_t id);

 private:
    void build_scene();
    void add_animation(size_t lay, Status &status);

 private:
    sf::RenderWindow &_window;
    sf::View _view;
    std::vector<animation::Layer> _animation_layers;
    std::vector<std::vector<Status>> _status;
    animation::Creator _creator;
    size_t _player_id;

    sf::Vector2f _extra_size;
};
