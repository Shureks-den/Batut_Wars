#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "Holder.h"
#include "Status.h"
#include "Identificators.h"

namespace animation {

class Animation {
 public:
     Animation() = default;
     Animation(const sf::Texture *texture, sf::Vector2u image_count, sf::Time switch_time);
     Animation(const Animation&) = default;
     ~Animation() = default;

     void update(int row, sf::Time d_time, bool is_forward);
     void set_switch_time(sf::Time switch_time);
     void set_image_count(sf::Vector2u image_count);

     sf::Vector2u get_current() const;

     sf::IntRect uv_rect;

 private:
     sf::Vector2u _image_count;
     sf::Vector2u _current_image;

     sf::Time _total_time;
     sf::Time _switch_time;
};

class Manager {
 public:
    explicit Manager(const sf::Texture *texture, sf::Vector2f position = sf::Vector2f(0, 0), float angle = 0);
    Manager(const Manager&) = default;
    ~Manager() = default;

    virtual void update(sf::Time d_time);
    void draw(sf::RenderWindow &window);
    void set_states(const std::vector<bool> &states);
    void set_position(const sf::Vector2f &position);
    void set_angle(const float angle);
    void set_start_angle(float start_angle);
    sf::Vector2f get_size() const;
    void set_size(sf::Vector2f size);
    void set_origin(sf::Vector2f center);

    void set_switch_time(sf::Time switch_time);
    void set_image_count(sf::Vector2u image_count);

 protected:
    sf::Vector2u _image_count;
    sf::Vector2u _current_image;

    sf::Time _total_time;
    sf::Time _switch_time;

    sf::IntRect _uv_rect;
    sf::RectangleShape _body;

    float _angle;
    float _start_angle;  // Угол между анимацией и OX
};



}  // namespace animation
