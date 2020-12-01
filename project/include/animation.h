#pragma once

#include <SFML/Graphics.hpp>

class Animation {
 public:
    Animation(sf::Texture *texture, sf::Vector2u image_count, sf::Time switch_time);
    ~Animation() = default;

    void update(int row, sf::Time d_time, bool is_forward);

    sf::IntRect uv_rect;

 private:
    sf::Vector2u _image_count;
    sf::Vector2u _current_image;

    sf::Time _total_time;
    sf::Time _switch_time;
};

class AnimationManager {
 public:
    AnimationManager(std::vector<Animation> &animations, sf::Vector2f position);
    ~AnimationManager() = default;

    void update(sf::Time d_time);
    void draw(sf::RenderWindow &window);

 private:
    sf::RectangleShape _body;
    std::vector<Animation> _animations;
    size_t _current;
};

struct State {        // TODO(ANDY) придумать содержание структуры
    bool is_moveing;  // Реализовать таблицу перехода состояние -> индекс анимации
    bool is_fireing;
    double angle;
};