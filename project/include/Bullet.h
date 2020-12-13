#pragma once
#include "Engine.h"

#include <SFML/Graphics/Sprite.hpp>

class Bullet : public engine::MoveAble {
 public:
    Bullet();
    float getMaxSpeed() const;
	int getDamage() const;
    void collusion(Entity &object);
    animation::Id get_animation_id() const override;

 private:
	void update(sf::Time dt) override;

 private:
    sf::Vector2f _bounds;
    int _dmg;
    float _maxSpeed;
}