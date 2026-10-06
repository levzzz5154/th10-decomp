#include "th10/game/item_spawn_0041bb00.hpp"
#include <math.h>
#pragma intrinsic(cos,sin)
#pragma code_seg(".text$35itempolar")
ItemPolarVelocity_0041bb00* ItemPolarVelocity_0041bb00::SetPolar(float angle,float speed) {
 x=static_cast<float>(cos(angle)*speed);y=static_cast<float>(sin(angle)*speed);return this;
}
#pragma code_seg()
