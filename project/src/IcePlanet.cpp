#include "IcePlanet.h"

namespace space {

void IcePlanet::collision(space::Bullet & bullet){
    engine::Vector radius;

    if (bullet.get_x() > get_x()){
        radius = engine::Vector(bullet.get_x() - get_x(), bullet.get_y() - get_y());
    }
    else{        
        radius = engine::Vector(- bullet.get_x() + get_x(), - bullet.get_y() + get_y());
    }

    float angle = radius.compute_angle(bullet.get_orientation());  // rad

    bullet.rotate(angle * 2);
}  // протестировать не могём

}