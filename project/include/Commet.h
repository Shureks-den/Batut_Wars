#pragma once

#include "Engine.h"

#define COMMET_DAMAGE 55

namespace space {
class Commet : public engine::MoveAble {
  Commet(engine::Vector speed);
  void collision(engine::MoveAble& moveable);
};
}  // namespace space