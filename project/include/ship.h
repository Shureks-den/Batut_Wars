#pragma once

#include "engine.h"

namespace space {

class Ship : public engine::MoveAble {
 public:
    Ship();
    Ship(const Ship &) = delete;
    void update(sf::Time dt) override;  // Вычислить новые значения coordinate(speed), speed(acceleretion)

 protected:
};

}  // end namespace space
