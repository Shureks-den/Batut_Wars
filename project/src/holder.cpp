#include "holder.h"

namespace animation {

Holder::Holder() {
    sf::Texture tmp;
    tmp.loadFromFile("project/media/MF_test.png");
    _resource_map.push_back(tmp);  // TODO(ANDY) дополнять
    tmp.loadFromFile("project/media/space.jpg");
    _resource_map.push_back(tmp);
}

const sf::Texture* Holder::get_texture(Id id) const {
    return &_resource_map[static_cast<size_t>(id)];
}

}  // namespace animation
