#pragma once

#include <SFML/Graphics.hpp>

#define SPEED_LIMIT 30.0 // speed и acceleretion не могут быть выше, чем
#define ACCELERETION_LIMIT 4.0

enum class Direction {
    FORWARD = 0,
    BACKWARD,
    LEFT,
    RIGHT
};

namespace engine {

class Vector {
 public:
    Vector() = default;
    Vector(double x, double y);
    Vector(const Vector & other) = default;
    ~Vector() = default;
    double get_x() const;
    double get_y() const;
    void set_x(double x);
    void set_y(double y);
    float get_abs() const;
    void rotate(double angle);
    Vector operator+(const Vector & other) const;
    Vector operator-(const Vector & other) const;
    Vector operator*(double coef) const;
    Vector operator/(double coef) const;
    Vector operator+=(const Vector & other);
    Vector operator-=(const Vector & other);
    Vector operator*=(double coef);
    Vector operator/=(double coef);

 private:
    double _x;
    double _y;
};

class Entity {
 public:
    Entity() = default;
    virtual ~Entity();
    float get_x() const;
    float get_y() const;
    float set_x(float x);
    float set_y(float y);
    virtual void update(sf::Time dt);

 protected:
    sf::Vector2f _coordinate;
};

class MoveAble : public Entity {
 public:
    MoveAble() = default;
    virtual ~MoveAble();
    virtual void update(sf::Time dt) = 0;
    void rotate(float angle);
    void give_acceleration(Vector acceleration);
    Vector d_acceleration(Direction direction, float abs_, float d_acceleration);
    void give_acceleration(Direction direction, float d_acceleration);

 protected:
      Vector _speed;
      Vector _acceleration;
};

}  // end namespace engine
