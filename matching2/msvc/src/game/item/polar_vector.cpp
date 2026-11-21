// 0x0041BEB0: ItemPolarVelocity2::SetPolar
#include "th10/game/item_velocity.hpp"
#include "th10/math/scaled_polar.hpp"

ItemPolarVelocity2* ItemPolarVelocity2::SetPolar(float angle, float speed) {
    return SetScaledPolar(this, angle, speed, speed);
}
