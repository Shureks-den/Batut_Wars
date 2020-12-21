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
    std::unique_ptr<Manager> get_animation(Id id) const;

 private:
    Holder _holder;
    std::vector<std::function<std::unique_ptr<Manager>(const Creator*)>> _method_map;

    std::unique_ptr<Manager> make_ship() const;
    std::unique_ptr<Manager> make_space() const;
    std::unique_ptr<Manager> make_blackhole() const;
    std::unique_ptr<Manager> make_bullet() const;
    std::unique_ptr<Manager> make_portal() const;
};

}  // namespace animation
