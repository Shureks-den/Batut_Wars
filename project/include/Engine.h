#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "Status.h"

constexpr float SPEED_LIMIT = 130.0;
constexpr float ACCELERETION_LIMIT = 10.0;

enum class Direction {
    FORWARD = 0,
    BACKWARD,
    LEFT,
    RIGHT
};

namespace engine {

float to_radian(float degrees);

class Vector {
 public:
    Vector() = default;
    Vector(float x, float y);
    Vector(const Vector &other);
    ~Vector() = default;
    float get_x() const;
    float get_y() const;
    void set_x(float x);
    void set_y(float y);
    float get_abs() const;
    void rotate(float angle);
    Vector get_normal() const;
    Vector operator+(const Vector &other) const;
    Vector operator-(const Vector &other) const;
    Vector operator*(float coef) const;
    Vector operator/(float coef) const;
    Vector operator+=(const Vector &other);
    Vector operator-=(const Vector &other);
    Vector operator*=(float coef);
    Vector operator/=(float coef);
    Vector& operator=(const Vector &other);
    sf::Vector2f get_sf() const;

 private:
    float _x;
    float _y;
};

class Entity {
 public:
    Entity();
    virtual ~Entity() = default;
    float get_x() const;
    float get_y() const;
    void set_x(float x);
    void set_y(float y);

    sf::Vector2f get_position() const;
    void set_position(sf::Vector2f position);

    size_t get_id() const;
    std::vector<bool> get_state() const;

    virtual animation::Id get_animation_id() const = 0;
    virtual void update(sf::Time dt) = 0;

 protected:
    sf::Vector2f _position;
    std::vector<bool> _state;
    size_t _id;
    static size_t _count;
};

class MoveAble : public Entity {
 public:
    MoveAble();
    virtual ~MoveAble() = default;
    // virtual void update(sf::Time dt) = 0;
    // virtual animation::Id get_animation_id() = 0;
    void rotate(float angle);
    void give_acceleration(Vector acceleration);
    void give_acceleration(Direction direction, float d_acceleration);

 protected:
    Vector _speed;
    Vector _acceleration;
};

}  // end namespace engine
