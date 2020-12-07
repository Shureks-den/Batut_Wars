#pragma once

#include "engine.h"

namespace space {

class Ship : public engine::MoveAble {
 public:
    Ship();
    ~Ship() = default;
    Ship(const Ship &) = delete;
    animation::Id get_animation_id() override;
    void update(sf::Time dt) override;  // Вычислить новые значения coordinate(speed), speed(acceleretion)

 protected:
};

}  // end namespace space
