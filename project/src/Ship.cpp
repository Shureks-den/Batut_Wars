#include "Ship.h"

namespace space {

Ship::Ship(const sf::Time recharge)
    : engine::MoveAble(35, 150),
      _recharge(recharge),
      _countdown(_recharge) {
      set_size(sf::Vector2f(50.0f, 64.0f));
}

void Ship::collision(engine::MoveAble &) {}

void Ship::trigger(MoveAble &) {}

}  // namespace space
