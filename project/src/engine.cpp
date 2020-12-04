#include "engine.h"

namespace engine
{
	Vector::Vector(double x, double y)
	{
		_x = x;
		_y = y;
	}

	Vector::Vector(const Vector & other)
	{
		this->_x = other._x;
		this->_y = other._y;
	}

	double Vector::get_x() const
	{
		return _x;
	}

	double Vector::get_y() const
	{
		return _y;
	}

	void Vector::set_x(double x)
	{
		_x = x;
	}

	void Vector::set_y(double y)
	{
		_y = y;
	}

	float Vector::get_abs() const
	{
		return sqrt((_x * _x) + (_y * _y));
	}

	void Vector::rotate(double angle)
	{
		_x = _x * cos(angle) - _y * sin(angle);
		_y = _x * sin(angle) + _y * cos(angle);
	}

	Vector Vector::get_normal()
	{
		float _abs = this->get_abs();
		Vector normal_vector(0, 0);
		if (_abs != 0)
		{
			normal_vector.set_x(_x / _abs);
			normal_vector.set_y(_y / _abs);
		}

		return normal_vector;
	}


	Vector Vector::operator+(const Vector & other) const
	{
		Vector tmp(this->_x, this->_y);
		tmp.set_x(this->_x + other._x);
		tmp.set_y(this->_y + other._y);
		return tmp;
	}

	Vector Vector::operator-(const Vector & other) const
	{
		return Vector(this->_x - other._x, this->_y - other._y);
	}

	Vector Vector::operator*(double coef) const
	{
		return Vector(coef * _x, coef * _y);
	}

	Vector Vector::operator/(double coef) const
	{
		return Vector(_x / coef, _y / coef);
	}

	Vector Vector::operator+=(const Vector & other)
	{
		this->_x += other._x;
		this->_y += other._y;
		return *this;
	}

	Vector Vector::operator-=(const Vector & other)
	{
		this->_x -= other._x;
		this->_y -= other._y;
		return *this;
	}

	Vector Vector::operator*=(double coef)
	{
		_x *= coef;
		_y *= coef;
		return *this;
	}

	Vector Vector::operator/=(double coef)
	{
		_x /= coef;
		_y /= coef;
		return *this;
	}

	float Entity::get_x() const
	{
		return _coordinate.x;
	}

	float Entity::get_y() const
	{
		return _coordinate.y;
	}

	float Entity::set_x(float x)
	{
		_coordinate.x = x;
		return _coordinate.x;
	}

	float Entity::set_y(float y)
	{
		_coordinate.y = y;
		return _coordinate.y;
	}


	void MoveAble::rotate(float angle)
	{
		double x = _speed.get_x() * cos(angle) - _speed.get_y() * sin(angle);
		double y = _speed.get_x() * sin(angle) + _speed.get_y() * cos(angle);
		_speed.set_x(x);
		_speed.set_y(y);
	}

	void MoveAble::give_acceleration(Vector acceleration)
	{
		_acceleration += acceleration;
	}

	void MoveAble::give_acceleration(Direction direction, float d_acceleration) {
		Vector delta = _speed.get_normal();
		delta *= (direction == Direction::BACKWARD) - d_acceleration : d_acceleration;

		if (direction == Direction::RIGHT) {
			delta.rotate(- M_PI / 2);
		} else if (direction == Direction::LEFT) {
            delta.rotate(M_PI / 2);
        }
        
        _acceleration += delta;
        if (_acceleration.get_abs() <= ACCELERETION_LIMIT) {
            _acceleration = _acceleration.get_normal() * ACCELERETION_LIMIT;
        }
	}

}  // namespace engine
