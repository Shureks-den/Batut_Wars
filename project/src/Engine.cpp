#include "Engine.h"

#include <cmath>

#define _USE_MATH_DEFINES

namespace engine {

float as_radian(float degrees) {
  constexpr static float coef = PI / 180;
  return degrees * coef;
}

float as_degree(float radian) {
  constexpr static float coef = 180 / PI;
  return radian * coef;
}

float Vector::compute_angle(const Vector& other) {
  return acos((_x * other._x + _y * other._y) / (get_abs() * other.get_abs()));
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
  float x = _x;
  float y = _y;
  _x = x * cos(angle) - y * sin(angle);
  _y = x * sin(angle) + y * cos(angle);
}

Vector Vector::get_normal() const {
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

sf::Vector2f Vector::get_sf() const { return sf::Vector2f(_x, _y); }

Entity::Entity()
    : _orientation(1.0f, 0.0f),
      _is_destroyed(false) {}  // TODO(Tony) сделать сеттер ориентации

void Entity::set_id(size_t id) { _id = id; }

sf::Vector2f Entity::get_size() const { return _size; }

void Entity::set_size(sf::Vector2f size) { _size = size; }

size_t Entity::get_id() const { return _id; }

float Entity::get_x() const { return _position.x; }

float Entity::get_y() const { return _position.y; }

void Entity::set_x(float x) { _position.x = x; }

void Entity::set_y(float y) { _position.y = y; }

void Entity::set_is_destroyed(bool value) { _is_destroyed = value; }

float Entity::get_angle() const {  // [-pi, pi]
  return (_orientation.get_y() < 0) ? -acos(_orientation.get_x())
                                    : acos(_orientation.get_x());
}

sf::Vector2f Entity::get_position() const { return _position; }

void Entity::set_position(sf::Vector2f position) { _position = position; }

std::vector<bool> Entity::get_state() const { return _state; }

void Entity::rotate_orientation(float angle) {
  _orientation.rotate(angle);
  _orientation = _orientation.get_normal();  // Убираем накопившуюся погрешность
}

bool Entity::is_destroyed() const { return _is_destroyed; }

MoveAble::MoveAble(float thrust, int dmg)
    : _engine_thrust(thrust),
      _speed_limit(90),
      _HP(100),
      _dmg(dmg) {}  // TODO(Tony) сеттер для seed_limit

MoveAble::MoveAble(float thrust, float speed, int dmg)
    : _engine_thrust(thrust), _speed_limit(speed), _HP(100), _dmg(dmg) {}

void MoveAble::set_dictated_speed(engine::Vector other_dictated_speed) {
  this->_dictated_speed = other_dictated_speed;
}

Vector MoveAble::get_dictated_speed() { return this->_dictated_speed; }

void MoveAble::give_acceleration(Vector acceleration) {
  _dictated_acceleration += acceleration;
}

void MoveAble::give_acceleration(Direction direction) {
  _engine_acceleration +=
      _orientation *
      ((direction == Direction::FORWARD) ? _engine_thrust : -_engine_thrust);
}

void MoveAble::rotate(float angle) {
  _engine_speed.rotate(angle);
  _orientation.rotate(angle);
  _orientation = _orientation.get_normal();  // Убираем накопившуюся погрешность
}

Vector Entity::get_orientation() { return _orientation; }

void MoveAble::set_hp(int value) { _HP = value; }

int MoveAble::get_hp() { return _HP; }

void MoveAble::collision(engine::MoveAble&) {}

void MoveAble::set_engine_speed(Vector other_speed) {
  this->_engine_speed = other_speed;
}
Vector MoveAble::get_engine_speed() { return this->_engine_speed; }

void MoveAble::take_damage(int dmg) {
  _HP -= dmg;
  // std::cout << "> " << _HP << "\t" << this->get_id() << std::endl;
  if (_HP <= 0) {
    _HP = 0;
    _is_destroyed = true;
  }
}

int MoveAble::get_damage() { return _dmg; }

}  // namespace engine
