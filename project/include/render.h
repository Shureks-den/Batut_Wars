#pragma once

#include <SFML/Graphics.hpp>

#include "animation.h"
#include "status.h"
#include "layer.h"
#include "holder.h"

class Render: private sf::NonCopyable {
 public:
    explicit Render(sf::RenderWindow& window);
    void update(sf::Time dt);
    void set_status(const std::vector<Status> &status);
    void draw();
    void inicilize(const std::vector<Status> &status);
    sf::View& get_view();

 private:
//    void loadTextures();
    void build_scene();

 private:
    sf::RenderWindow &_window;
    sf::View _view;
    std::vector<animation::Layer> _animation_layers;
    std::vector<Status> _status;
    animation::Holder _holder;

    void add_animation(size_t lay, Status &status);
};
