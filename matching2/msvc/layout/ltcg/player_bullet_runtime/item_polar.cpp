#include "item_spawn.hpp"
#include <math.h>
#pragma intrinsic(cos,sin)
#pragma code_seg(".text$f0041beb0F")
ItemPolarVelocity_0041bb00* ItemPolarVelocity_0041bb00::SetPolar(float angle,float speed) {
    x=static_cast<float>(cos(angle)*speed);
    y=static_cast<float>(sin(angle)*speed);
    return this;
}
#pragma code_seg()
