#pragma once

#include "Engine.h"
#include "Massive.h"
#include "Bullet.h"

namespace space {

class IcePlanet: public space::Massive {
   private:
    void collision(space::Bullet & bullet);
};

}  // namespace space