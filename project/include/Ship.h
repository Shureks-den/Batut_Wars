#pragma once

#include "Engine.h"

#define SHIPE_WIDTH 48

namespace space {

class Ship : public engine::MoveAble {
 public:
    Ship();
    ~Ship() = default;

    void update(sf::Time dt) override;
    animation::Id get_animation_id() const override;

 protected:
    int _HP;
    float armor;
};

}  // end namespace space
