#include "Holder.h"

namespace animation {

Holder::Holder() {
  sf::Texture tmp;
  tmp.loadFromFile("project/media/MF.png");
  _resource_map.push_back(tmp);  // TODO(ANDY) дополнять
  tmp.loadFromFile("project/media/space.jpg");
  _resource_map.push_back(tmp);
  tmp.loadFromFile("project/media/planet-15.png");
  _resource_map.push_back(tmp);
  tmp.loadFromFile("project/media/bullet-2.png");
  _resource_map.push_back(tmp);
  tmp.loadFromFile("project/media/portall.png");
  _resource_map.push_back(tmp);
  tmp.loadFromFile("project/media/planet-14.png");
  _resource_map.push_back(tmp);
  tmp.loadFromFile("project/media/comet.png");
  _resource_map.push_back(tmp);
  tmp.loadFromFile("project/media/explosion-1.png");
  _resource_map.push_back(tmp);
  tmp.loadFromFile("project/media/Maul.png");
  _resource_map.push_back(tmp);
}

const sf::Texture* Holder::get(Id id) const {
  return &_resource_map[static_cast<size_t>(id)];
}

}  // namespace animation

namespace fonts {

Holder::Holder() {
  sf::Font tmp;
  tmp.loadFromFile("project/media/Biff.ttf");
  _resource_map.push_back(tmp);  // TODO(ANDY) дополнять
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
  tmp.loadFromFile("project/media/NormalButton.png");
  _resource_map.push_back(tmp);
  tmp.loadFromFile("project/media/PushedButton.png");
  _resource_map.push_back(tmp);
  tmp.loadFromFile("project/media/SelectedButton.png");
  _resource_map.push_back(tmp);
  tmp.loadFromFile("project/media/Menu.jpg", sf::IntRect(0, 0, 3840, 2880));
  _resource_map.push_back(tmp);
}

const sf::Texture* Holder::get(Id id) const {
  return &_resource_map[static_cast<size_t>(id)];
}

}  // namespace textures

namespace sounds {

  Holder::Holder() {
  sf::SoundBuffer tmp;
  tmp.loadFromFile("project/media/explosion.wav");
  _resource_map.push_back(tmp);
  tmp.loadFromFile("project/media/playershoot.wav");
  _resource_map.push_back(tmp);
  tmp.loadFromFile("project/media/enemyshoot.wav");
  _resource_map.push_back(tmp);
  tmp.loadFromFile("project/media/icerefraction.wav");
  _resource_map.push_back(tmp);
}

const sf::SoundBuffer* Holder::get(Id id) const {
  return &_resource_map[static_cast<size_t>(id)];
}

}  // namespace sound
