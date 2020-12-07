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
    ~Animation() = default;

    void update(int row, sf::Time d_time, bool is_forward);
    void set_switch_time(sf::Time switch_time);
    void set_image_count(sf::Vector2u image_count);

    sf::IntRect uv_rect;

 private:
    sf::Vector2u _image_count;
    sf::Vector2u _current_image;

    sf::Time _total_time;
    sf::Time _switch_time;
};

class Manager {
 public:
    Manager(Animation animation, sf::Vector2f position);
    Manager(const sf::Texture *texture, sf::Vector2f position, float angle);  // Переписать на status
    Manager(Id id, sf::Vector2f position, float angle);
    ~Manager() = default;

    void update(sf::Time d_time);
    void draw(sf::RenderWindow &window);
    void set_states(const std::vector<bool> &states);
    void set_position(const sf::Vector2f &position);
    void set_angle(const float angle);
    sf::Vector2f get_size();

 protected:
    sf::RectangleShape _body;
    Animation _animation;
    size_t _current;

    static Holder _holder;

    float _angle;

    void set_switch_time(sf::Time switch_time);
    void set_image_count(sf::Vector2u image_count);
};

}  // namespace animation
