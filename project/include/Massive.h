#include "Engine.h"

namespace space {

class Massive : public engine::ImmoveAble
{
 public:
    Massive(int mass, float range);
    ~Massive() = default;
    void smash(engine::MoveAble &moveable) override;  // TODO(Tony)
    void component_acceleration(engine::MoveAble &moveable);
    float get_zone();
   

    float get_range();
    engine::Vector gravitate(sf::Vector2f position);

    animation::Id get_animation_id() const override;
    void update(sf::Time dt) override;

 protected:
    const int _mass;
    const float _range;
};

}  // namespace space


