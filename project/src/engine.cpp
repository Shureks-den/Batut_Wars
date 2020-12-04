#include "engine.h"

#include <cmath>

namespace engine {
engine::Vector::Vector(double x, double y) {  // TODO(ANDY) убрать engine::
}

double engine::Vector::get_x() const {
    return _x;
}

double engine::Vector::get_y() const {
    return _y;
}

void engine::Vector::set_x(double x) {
    _x = x;
}

void engine::Vector::set_y(double y) {
    _y = y;
}

float engine::Vector::get_abs() const {
    return sqrt((_x * _x) + (_y * _y));
}

void engine::Vector::rotate(double angle) {
    x = _x * cos(angle) - _y * sin(angle);
    y = _x * sin(angle) + _y * cos(angle);
    _x = x;
    _y = y;
}

engine::Vetor engine::Vector::get_normal() {
    float _abs = this->get_abs();
    Vector normal_vector(_x() / _abs, _y() / _abs);
    return normal_vector;
}


engine::Vector engine::Vector::operator+(const Vector &other) const {
    Vector tmp(this->_x, this->_y);
    tmp.set_x(this->_x + other._x);
    tmp.set_y(this->_y + other._y);
    return tmp;
}

engine::Vector engine::Vector::operator-(const Vector &other) const {
    return Vector(this->_x - other._x, this->_y - other._y);
}

engine::Vector engine::Vector::operator*(double coef) const {
    return Vector(coef * _x, coef * _y);
}

engine::Vector engine::Vector::operator/(double coef) const {
    return Vector(_x / coef, _y / coef);
}

engine::Vector engine::Vector::operator+=(const Vector &other) {
    this->_x += other._x;
    this->_y += other._y;
    return *this;
}

engine::Vector engine::Vector::operator-=(const Vector &other) {
    this->_x -= other._x;
    this->_y -= other._y;
    return *this;
}

engine::Vector engine::Vector::operator*=(double coef) {
    _x *= coef;
    _y *= coef;
    return *this;
}

engine::Vector engine::Vector::operator/=(double coef) {
    _x /= coef;
    _y /= coef;
    return *this;
}

float engine::Entity::get_x() const {
    return _coordinate.x;
}

float engine::Entity::get_y() const {
    return _coordinate.y;
}

float engine::Entity::set_x(float x) {
    _coordinate.x = x;
    return _coordinate.x;
}

float engine::Entity::set_y(float y) {
    _coordinate.y = y;
    return _coordinate.y;
}


void MoveAble::rotate(float angle) {
    double x = _speed.get_x() * cos(angle) - _speed.get_y() * sin(angle);
    double y = _speed.get_x() * sin(angle) + _speed.get_y() * cos(angle);
    _speed.set_x(x);
    _speed.set_y(y);
}

void MoveAble::give_acceleration(Vector acceleration) {
    _acceleration += acceleration;
}

Vector MoveAble::d_acceleration(Direction direction, float d_acceleration) {
    Vector delta(this->get_normal);
    if (direction == Direction::RIGHT) {  // TODO(ANDY) Этот код можно сократить.
        delta.rotate(-90);                // И тогда он будет достаточно коротким, чтобы
        delta *= d_acceleration;          // запихать его целиком в give_acceleration()
    } else if (direction == Direction::LEFT) {  // и удалить этот метод.
        delta.rotate(90);
        delta *= d_acceleration;
    } else if (direction == Direction::BACKWARD) {
        delta *= - d_acceleration;
    } else {
        delta *= d_acceleration;
    }
    return delta;
}

void MoveAble::give_acceleration(Direction direction, float d_acceleration) {
    float speed_abs = _speed.get_abs();  // Это больше не нужно
        Vector delta(this->d_acceleration(direction, d_acceleration));  // Не уверен, что нужен отдельный метод d_acceleration
        _acceleration += delta;                                                    // И он уж точне не public
    }
}  // namespace engine
