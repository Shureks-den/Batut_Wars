#include "Holder.h"

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

namespace fonts {

Holder::Holder() {
    sf::Font tmp;
    tmp.loadFromFile("project/media/Sansation.ttf");
    _resource_map.push_back(tmp);  // TODO(ANDY) дополнять
}

const sf::Font* Holder::get(Id id) const {
    return &_resource_map[static_cast<size_t>(id)];
}

}  // namespace fonts

namespace textures {

Holder::Holder() {
    sf::Texture tmp;
    tmp.loadFromFile("project/media/ButtonNormal.png");
    _resource_map.push_back(tmp);
    tmp.loadFromFile("project/media/ButtonPressed.png");
    _resource_map.push_back(tmp);
    tmp.loadFromFile("project/media/ButtonSelected.png");
    _resource_map.push_back(tmp);
    tmp.loadFromFile("project/media/MainMenu.jpg");
    _resource_map.push_back(tmp);
}

const sf::Texture* Holder::get(Id id) const {
    return &_resource_map[static_cast<size_t>(id)];
}

}  // namespace textures
