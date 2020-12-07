#include "engine.h"

namespace engine {

float as_radian(float degrees) {
    constexpr static float coef = PI / 180;
    return degrees * coef;
}

float as_degree(float radian){
    constexpr static float coef = 180 / PI;
    return radian * coef;
}



Vector::Vector(float x, float y) {
    _x = x;
    _y = y;
}

Vector::Vector(const Vector & other) {
    this->_x = other._x;
    this->_y = other._y;
}

float Vector::get_x() const {
    return _x;
}

float Vector::get_y() const {
    return _y;
}

void Vector::set_x(float x) {
    _x = x;
}

void Vector::set_y(float y) {
    _y = y;
}

float Vector::get_abs() const {
    return sqrt((_x * _x) + (_y * _y));
}

void Vector::rotate(float angle) {
    _x = _x * cos(angle) - _y * sin(angle);
    _y = _x * sin(angle) + _y * cos(angle);
}

Vector Vector::get_normal() {
    float _abs = get_abs();
    Vector normal_vector(0, 0);
    if (_abs != 0) {
        normal_vector.set_x(_x / _abs);
        normal_vector.set_y(_y / _abs);
    }

    return normal_vector;
}


Vector Vector::operator+(const Vector & other) const {
    Vector tmp(this->_x, this->_y);
    tmp.set_x(this->_x + other._x);
    tmp.set_y(this->_y + other._y);
    return tmp;
}

Vector Vector::operator-(const Vector & other) const {
    return Vector(this->_x - other._x, this->_y - other._y);
}

Vector Vector::operator*(float coef) const {
    return Vector(coef * _x, coef * _y);
}

Vector Vector::operator/(float coef) const {
    return Vector(_x / coef, _y / coef);
}

Vector Vector::operator+=(const Vector & other) {
    this->_x += other._x;
    this->_y += other._y;
    return *this;
}

Vector Vector::operator-=(const Vector & other) {
    this->_x -= other._x;
    this->_y -= other._y;
    return *this;
}

Vector Vector::operator*=(float coef) {
    _x *= coef;
    _y *= coef;
    return *this;
}

Vector Vector::operator/=(float coef) {
    _x /= coef;
    _y /= coef;
    return *this;
}

Vector& Vector::operator=(const Vector &other) {
    if (this == &other) {
        return *this;
    }

    this->_x = other._x;
    this->_y = other._y;

    return *this;
}

sf::Vector2f Vector::get_sf() {
    return sf::Vector2f(_x, _y);
}



size_t Entity::_count = 0;  // static - член класса Entity

Entity::Entity() : _orientation(1.0f, 0.0f) {
    _id = _count++;
}

size_t Entity::get_id() {
    return _id;
}

float Entity::get_x() const {
    return _position.x;
}

float Entity::get_y() const {
    return _position.y;
}

void Entity::set_x(float x) {
    _position.x = x;
}

void Entity::set_y(float y) {
    _position.y = y;
}

float Entity::get_angle() {  // [-pi, pi]
    float angle = acos(_orientation.get_x() / _orientation.get_abs());
    if (_orientation.get_y() < 0) {
        angle *= -1;
    }
    return angle;
}

sf::Vector2f Entity::get_position() {
    return _position;
}

void Entity::set_position(sf::Vector2f position) {
    _position = position;
}

std::vector<bool> Entity::get_state() {
    return _state;
}

void Entity::rotate_orientation(float angle) {
    _orientation.rotate(angle);
}



MoveAble::MoveAble(float thrust) : _engine_thrust(thrust), _speed_limit(90) {}  // TODO(Tony): define values

void MoveAble::give_acceleration(Vector acceleration) {
    _acceleration += acceleration;
}

void MoveAble::give_acceleration(Way direction) {
    (direction == Way::CONTRA) ? (_acceleration = _orientation * (- _engine_thrust)) : (_acceleration = _orientation * _engine_thrust);
}

MassiveObject::MassiveObject(int mass, float range) : _mass(mass), _range(range) {}

Vector MassiveObject::gravitate(sf::Vector2f position){

    Vector tmp(this->get_x() - position.x, this->get_y() - position.y);

    float radius = tmp.get_abs();
    float current_component_a = G * _mass / (radius * radius);

    tmp.get_normal();
    tmp *= current_component_a;

    return tmp;
}

}  // namespace engine
