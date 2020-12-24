#include "AnimationCreator.h"

#include <memory>

#include "A-Blackhole.h"
#include "A-Bullet.h"
#include "A-Comet.h"
#include "A-Explosion.h"
#include "A-IcePlanet.h"
#include "A-Portal.h"
#include "A-Ship.h"
#include "A-Space.h"
#include "A-Maul.h"

namespace animation {

Creator::Creator() {
  std::function<std::unique_ptr<Manager>(const Creator*)> ptr;
  ptr = &Creator::make_ship;
  _method_map.push_back(ptr);
  ptr = &Creator::make_space;
  _method_map.push_back(ptr);
  ptr = &Creator::make_blackhole;
  _method_map.push_back(ptr);
  ptr = &Creator::make_bullet;
  _method_map.push_back(ptr);
  ptr = &Creator::make_portal;
  _method_map.push_back(ptr);
  ptr = &Creator::make_iceplanet;
  _method_map.push_back(ptr);
  ptr = &Creator::make_comet;
  _method_map.push_back(ptr);
  ptr = &Creator::make_explosion;
  _method_map.push_back(ptr);
  ptr = &Creator::make_maul;
  _method_map.push_back(ptr);
}

std::unique_ptr<Manager> Creator::get_animation(Id id) const {
  return _method_map[static_cast<size_t>(id)](this);
}

std::unique_ptr<Manager> Creator::make_ship() const {
  // Исходный размер: 480 128
  auto ship = std::make_unique<Ship>(_holder.get(Id::MF));
  return ship;
}

std::unique_ptr<Manager> Creator::make_space() const {
  // Исходный размер: 450 450
  auto space = std::make_unique<Space>(_holder.get(Id::SPACE));
  return space;
}

std::unique_ptr<Manager> Creator::make_blackhole() const {
  // Исходный размер: 1346 1346
  auto blackhole = std::make_unique<Blackhole>(_holder.get(Id::BLACKHOLE));
  return blackhole;
}

std::unique_ptr<Manager> Creator::make_bullet() const {
  // Исходный размер 640 160
  auto bullet = std::make_unique<Bullet>(_holder.get(Id::BULLET));
  return bullet;
}

std::unique_ptr<Manager> Creator::make_portal() const {
  // Исходный размер 728 824
  auto portal = std::make_unique<Portal>(_holder.get(Id::PORTAL));
  return portal;
}

std::unique_ptr<Manager> Creator::make_iceplanet() const {
  // Исходный размер 1346 1346
  auto iceplanet = std::make_unique<IcePlanet>(_holder.get(Id::ICE_PLANET));
  return iceplanet;
}

std::unique_ptr<Manager> Creator::make_comet() const {
  // Исходный размер 3072 512
  auto comet = std::make_unique<Comet>(_holder.get(Id::COMET));
  return comet;
}

std::unique_ptr<Manager> Creator::make_explosion() const {
  // Исходный размер 3072 512
  auto comet = std::make_unique<Explosion>(_holder.get(Id::EXPLOSION));
  return comet;
}

std::unique_ptr<Manager> Creator::make_maul() const {
  // Исходный размер 353 499
  auto maul = std::make_unique<Maul>(_holder.get(Id::MAUL));
  return maul;
}

}  // namespace animation
