#pragma once

#include  <functional>

#include "Animation.h"
#include "Holder.h"

namespace animation {

// typedef Manager (*ptr)();

class Creator {
 public:
    Creator();
    ~Creator() = default;
    Manager get_animation(Id id) const;

 private:
    Holder _holder;
    std::vector<std::function<Manager(const Creator*)>> _method_map;

    Manager make_ship() const;
    Manager make_space() const;
    Manager make_blackhole() const;
};

}  // namespace animation