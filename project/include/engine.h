#pragma once

#include <SFML/Graphics.hpp>

#define SPEED_LIMIT 30.0 //  speed и acceleretion не могут быть выше, чем
#define ACCELERETION_LIMIT 4.0

enum class Direction {
    FORWARD = 0,
    DOWN,
    RIGHT,
    BACK
};

namespace engine {

class Vector {
 public:
    Vector() = default;
    Vector(double x, double y);
    Vector(const Vector &other) = default;
    ~Vector() = default;
    double get_x() const;
    double get_y() const;
    double set_x();
    double set_y();
    float get_abs() const;
    void rotate(double angle);
    Vector operator+(const Vector &other) const;
    Vector operator-(const Vector &other) const;
    Vector operator*(double coef) const;
    Vector operator/(double coef) const;
    Vector operator+=(const Vector &other);
    Vector operator-=(const Vector &other);
    Vector operator*=(double coef);
    Vector operator/=(double coef);

 private:
    double _x;
    double _y;
};

class SpaceObject {
 public:
    SpaceObject() = default;
    virtual ~SpaceObject();
    float get_x() const;
    float get_y() const;
    float set_x(int x);
    float set_y(int y);
    virtual void update(sf::Time dt);

 protected:
    sf::Vector2f _coordinate;
};

class MoveAble : SpaceObject {
 public:
    MoveAble() = default;
    virtual ~MoveAble();
    virtual void update(sf::Time dt) = 0;
    void rotate(Direction direction, float angle);  // Повернуть вектор скорости на angle в сторону direction (FORWARD
    // сонаправленно со speed_)
    void give_acceleretion(Vector acceleration);  // Изменить ускорение на acceleration (сумма)
    void give_acceleretion(Direction direction, float d_acceleration);  // Изменить ускорение на d_acceleration в сторону direction

 protected:
    Vector _speed;
    Vector _acceleretion;
};

