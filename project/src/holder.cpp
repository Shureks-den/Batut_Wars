#include "holder.h"

#include <iostream>

namespace animation {

Holder::Holder() {
    sf::Texture tmp;
    tmp.loadFromFile("project/media/smallfreighterspr.png");
    _resource_map.push_back(tmp);  // TODO(ANDY) дополнять
}

const sf::Texture* Holder::get_texture(Id id) const {
    return &_resource_map[static_cast<size_t>(id)];
}

}  // namespace animation
