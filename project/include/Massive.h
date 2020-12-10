#include "Engine.h"

namespace space {

class Massive : public engine::ImmoveAble
{
 public:
    Massive(int mass, float range);
    ~Massive() = default;
    void collision(engine::MoveAble &moveable) override;  // TODO(Tony)

    float get_range();
    engine::Vector gravitate(sf::Vector2f position);

    animation::Id get_animation_id() const override;
    void update(sf::Time dt) override;

 protected:
    const int _mass;
    const float _range;
};

}  // namespace space


