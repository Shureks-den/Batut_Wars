#pragma once

#include <SFML/Graphics.hpp>

#include "status.h"
// #include "physics.h"
#include <cmath>
#define _USE_MATH_DEFINES

#define PI M_PI
#define G 6.67e-11  // система СИ

enum class Direction {
    FORWARD = 0,
    BACKWARD,
    LEFT,
    RIGHT
};

namespace engine {

float as_radian(float degrees);

float as_degree(float radian);

class Vector {
 public:
    Vector() = default;
    Vector(float x, float y);
    Vector(const Vector& other);
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
    Vector& operator=(const Vector &other);
    sf::Vector2f get_sf();

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
    float get_angle();

    sf::Vector2f get_position();
    void set_position(sf::Vector2f position);

    size_t get_id();
    std::vector<bool> get_state();  // TODO: change to be useful

    virtual animation::Id get_animation_id() = 0;
    virtual void update(sf::Time dt) = 0;

 protected:
    sf::Vector2f _position;
    std::vector<bool> _state;
    size_t _id;
    static size_t _count;
    float _angle = 180;  // Угол между передом объекта и положительным направлением Оу (в sfml) [град]
};

class MoveAble : public Entity {
 public:
    MoveAble(float thrust);
    virtual ~MoveAble() = default;
    virtual void update(sf::Time dt) = 0;
    void rotate(float angle);
    void give_acceleration(Vector acceleration);
    void give_acceleration(Direction direction);

 protected:
    Vector _speed;
    Vector _acceleration;  // Суммарное ускорение
    const float _engine_thrust;  // ускорение, предаваемое двигателем
    float _speed_limit;
};

class ImmoveAble : public Entity
{
    
};

class MassiveObject : public ImmoveAble
{
 public:
    MassiveObject(int M, float range);
    engine::Vector gravitate(sf::Vector2f position);

 protected:
    const int _mass;
    const float _range;
};

}  // end namespace engine
