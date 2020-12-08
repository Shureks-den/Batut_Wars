#include "engine.h"

#include <cmath>

#define _USE_MATH_DEFINES

namespace engine {

float to_radian(float degrees) {
  constexpr static float coef = M_PI / 180;
  return degrees * coef;
}

Vector::Vector(float x, float y) {
  _x = x;
  _y = y;
}

Vector::Vector(const Vector& other) {
  this->_x = other._x;
  this->_y = other._y;
}

float Vector::get_x() const { return _x; }

float Vector::get_y() const { return _y; }

void Vector::set_x(float x) { _x = x; }

void Vector::set_y(float y) { _y = y; }

float Vector::get_abs() const { return sqrt((_x * _x) + (_y * _y)); }

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

Vector Vector::operator+(const Vector& other) const {
  Vector tmp(this->_x, this->_y);
  tmp.set_x(this->_x + other._x);
  tmp.set_y(this->_y + other._y);
  return tmp;
}

Vector Vector::operator-(const Vector& other) const {
  return Vector(this->_x - other._x, this->_y - other._y);
}

Vector Vector::operator*(float coef) const {
  return Vector(coef * _x, coef * _y);
}

Vector Vector::operator/(float coef) const {
  return Vector(_x / coef, _y / coef);
}

Vector Vector::operator+=(const Vector& other) {
  this->_x += other._x;
  this->_y += other._y;
  return *this;
}

Vector Vector::operator-=(const Vector& other) {
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

Vector& Vector::operator=(const Vector& other) {
  if (this == &other) {
    return *this;
  }

  this->_x = other._x;
  this->_y = other._y;

  return *this;
}

sf::Vector2f Vector::get_sf() { return sf::Vector2f(_x, _y); }

size_t Entity::_count = 0;  // static - член класса Entity

Entity::Entity() { _id = _count++; }

size_t Entity::get_id() { return _id; }

float Entity::get_x() const { return _position.x; }

float Entity::get_y() const { return _position.y; }

void Entity::set_x(float x) { _position.x = x; }

void Entity::set_y(float y) { _position.y = y; }

sf::Vector2f Entity::get_position() { return _position; }

void Entity::set_position(sf::Vector2f position) { _position = position; }

std::vector<bool> Entity::get_state() { return _state; }

MoveAble::MoveAble() : _speed(0.0f, -1.0f), _acceleration(0.0f, -1.0f) {}

void MoveAble::rotate(float angle) {
  float x = _speed.get_x() * cos(angle) - _speed.get_y() * sin(angle);
  float y = _speed.get_x() * sin(angle) + _speed.get_y() * cos(angle);
  _speed.set_x(x);
  _speed.set_y(y);
  x = _acceleration.get_x() * cos(angle) - _acceleration.get_y() * sin(angle);
  y = _acceleration.get_x() * sin(angle) + _acceleration.get_y() * cos(angle);
  _acceleration.set_x(x);
  _acceleration.set_y(y);
}

void MoveAble::give_acceleration(Vector acceleration) {
  _acceleration += acceleration;
}

void MoveAble::give_acceleration(Direction direction, float d_acceleration) {
  Vector delta = _speed.get_normal();
  delta *=
      (direction == Direction::BACKWARD) ? -d_acceleration : d_acceleration;

  if (direction == Direction::RIGHT) {
    delta.rotate(to_radian(M_PI / 2));
  } else if (direction == Direction::LEFT) {
    delta.rotate(to_radian(-M_PI / 2));
  }

  _acceleration += delta;
  if (_acceleration.get_abs() <= ACCELERETION_LIMIT) {
    _acceleration = _acceleration.get_normal() * ACCELERETION_LIMIT;
  }
}

}  // namespace engine
