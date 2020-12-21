#pragma once

#include "Bullet.h"
#include "Engine.h"
#include "Massive.h"

namespace space {

class IcePlanet : public space::Massive {
 private:
  void collision(space::Bullet& bullet);
};

}  // namespace space