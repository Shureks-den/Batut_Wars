#include "ship.h"

using namespace space;

void space::Ship::update(sf::Time dt)
{
	_speed += _acceleration * dt.asSeconds();
	sf::Vector2f movement(0.f, 0.f);
	if (mIsMovingUp)
		movement.y -= _speed.get_y();
	if (mIsMovingDown)
		movement.y += _speed.get_y();
	if (mIsMovingLeft)
		movement.x -= _speed.get_x();
	if (mIsMovingRight)
		movement.x += _speed.get_x();

	mPlayer.move(movement * dt.asSeconds());
}
