#include "engine.h"

#include <cmath>

engine::Vector::Vector(double x, double y) {  // TODO(ANDY) Так не надо.
    _x = x;                                   // Давайте напишем namespace engine { ... реализация ... }
    _y = y;                                   // Как внизу крч
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
    this->_x = this->_x * cos(angle) - this->_y * sin(angle);  // TODO(ANDY) Давайте this использовать,
    this->_y = this->_x * sin(angle) + this->_y * cos(angle);  // только когда есть other. Иначе писать просто _x, _y
}

engine::Vector engine::Vector::operator+(const Vector & other) const {
    Vector tmp(this->_x, this->_y);
    tmp.set_x(this->_x + other._x);
    tmp.set_y(this->_y + other._y);
    return tmp;
}

engine::Vector engine::Vector::operator-(const Vector & other) const {
    return Vector(this->_x -other._x, this->_y-other._y);
}

engine::Vector engine::Vector::operator*(double coef) const {
    return Vector(coef*this->_x,coef*this->_y);
}

engine::Vector engine::Vector::operator/(double coef) const {
    return Vector(this->_x/coef, this->_y/coef);
}

engine::Vector engine::Vector::operator+=(const Vector & other) {
    this->_x += other._x;
    this->_y += other._y;
    return *this;
}

engine::Vector engine::Vector::operator-=(const Vector & other) {
    this->_x -= other._x;
    this->_y -= other._y;
    return *this;
}

engine::Vector engine::Vector::operator*=(double coef) {
    this->_x *= coef;
    this->_y *= coef;
    return *this;
}

engine::Vector engine::Vector::operator/=(double coef) {
    this->_x /= coef;
    this->_y /= coef;
    return *this;
}

float engine::Entity::get_x() const {
    return this->_coordinate.x;
}

float engine::Entity::get_y() const {
    return this->_coordinate.y;
}

float engine::Entity::set_x(float x) {
    this->_coordinate.x = x;
    return this->_coordinate.x;
}

float engine::Entity::set_y(float y) {
    this->_coordinate.y = y;
    return this->_coordinate.y;
}

namespace engine {

void MoveAble::rotate(float angle) {
    double x = _speed.get_x() * cos(angle) - _speed.get_y() * sin(angle);
    double y = _speed.get_x() * sin(angle) + _speed.get_y() * cos(angle);
    _speed.set_x(x);
    _speed.set_y(y);
}

void MoveAble::give_acceleration(Vector acceleration) {
    _acceleration += acceleration;
}

Vector MoveAble::d_acceleration(Direction direction, float speed_abs, float d_acceleration) { // Зачем speed_abs как параметр? Его можно вычислить внутри метода
    Vector delta(_speed.get_x() / speed_abs, _speed.get_y() / speed_abs);  // Это надо сделать public-методом в Vector
        if (direction == Direction::RIGHT) {
            double x = delta.get_y();
            double y = -delta.get_x();
            delta.set_x(x * d_acceleration);
            delta.set_x(y * d_acceleration);
        } else if (direction == Direction::LEFT) {  // TODO(ANDY) По возможности сократить
            double x = -delta.get_y();
            double y = delta.get_x();
            delta.set_x(x * d_acceleration);
            delta.set_x(y * d_acceleration);
        } else if (direction == Direction::BACKWARD) {
            delta.set_x(-delta.get_x() * d_acceleration);
            delta.set_x(-delta.get_y() * d_acceleration);
        } else {
            delta.set_x(delta.get_x() * d_acceleration);
            delta.set_x(delta.get_y() * d_acceleration);
        }
        return delta;
}

void MoveAble::give_acceleration(Direction direction, float d_acceleration) { 
    float speed_abs = _speed.get_abs();
        Vector delta(this->d_acceleration(direction, speed_abs, d_acceleration));  // Не уверен, что нужен отдельный метод d_acceleration
        _acceleration += delta;                                                    // И он уж точне не public
    }
}
