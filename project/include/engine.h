#pragma once

#include <SFML/Graphics.hpp>

constexpr float SPEED_LIMIT = 3.0;
constexpr float ACCELERETION_LIMIT = 1.0;

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
    Vector get_normal();
    Vector operator+(const Vector &other) const;
    Vector operator-(const Vector &other) const;
    Vector operator*(float coef) const;
    Vector operator/(float coef) const;
    Vector operator+=(const Vector &other);
    Vector operator-=(const Vector &other);
    Vector operator*=(float coef);
    Vector operator/=(float coef);
    Vector operator=(const Vector &other);
    sf::Vector2f get_sf();

 private:
    float _x;
    float _y;
};

class Entity {
 public:
    Entity() = default;
    virtual ~Entity() = default;
    float get_x() const;
    float get_y() const;
    void set_x(float x);
    void set_y(float y);
    sf::Vector2f get_position();
    void set_position(sf::Vector2f position);
    virtual void update(sf::Time dt) = 0;

 protected:
    sf::Vector2f _position;
};

class MoveAble : public Entity {
 public:
    MoveAble();
    virtual ~MoveAble() = default;
    virtual void update(sf::Time dt) = 0;
    void rotate(float angle);
    void give_acceleration(Vector acceleration);
    void give_acceleration(Direction direction, float d_acceleration);

 protected:
    Vector _speed;
    Vector _acceleration;
};

}  // end namespace engine
