#pragma once
#include "Engine.h"

#include <SFML/Graphics/Sprite.hpp>

namespace space {
class Bullet : public engine::MoveAble {
 public:
    Bullet();
    float getMaxSpeed() const;
	int getDamage() const;
    void collision(engine::MoveAble &object);
    animation::Id get_animation_id() const override;

	void update(sf::Time dt) override;

 private:
    sf::Vector2f _bounds;
    int _dmg;
    float _maxSpeed;
};

}  // namespace space