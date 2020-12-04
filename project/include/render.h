#pragma once

#include <SFML/Graphics.hpp>

#include "animation.h"
#include "status.h"
#include "layer.h"

class Render: private sf::NonCopyable {
 public:
    explicit Render(sf::RenderWindow& window);
    void update(sf::Time dt);
    void set_status(std::vector<Status> &status);
    void draw();

 private:
    void inicilize_status(std::vector<Status> &status);
    void loadTextures();
    void build_scene();

 private:
    sf::RenderWindow &_window;
    sf::View _view;
    std::vector<animation::Layer> _animation_layers;
    std::vector<Status> _status;

    void add_animation(size_t lay, Status &status);
};
