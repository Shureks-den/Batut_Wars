#pragma once

#include "Engine.h"

namespace space {

class Ship : public engine::MoveAble {
 public:
    Ship();
    ~Ship() = default;

    void update(sf::Time dt) override;
    animation::Id get_animation_id() const override;

 protected:
};

}  // end namespace space
