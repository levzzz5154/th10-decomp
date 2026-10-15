// Complete allocator/animation graph reached by the two actual line callers.
// These ordinary polar bodies retain their public member ABI. Their FCOS/FSIN
// output is unselected; production has separate exact FSINCOS recoveries.
#include "allocator.cpp"
#include "bounded.cpp"
#include "types/line_sweeps.hpp"
#include "dependencies.cpp"
#include "loader.cpp"
#include "configure.cpp"
#include "create.cpp"
#include "../../../contexts/legacy/game/item_convert_genuine_0041ba50.cpp"
#include "resource_configure.cpp"
#include "update_helpers.cpp"
#include "update.cpp"
#include <math.h>
#pragma intrinsic(cos,sin)
#pragma code_seg(".text$f0041beb0F")
__declspec(noinline) ItemPolarVelocity_0041bb00* ItemPolarVelocity_0041bb00::SetPolar(float angle,float speed) {
    x=static_cast<float>(cos(angle)*speed);
    y=static_cast<float>(sin(angle)*speed);
    return this;
}
#pragma code_seg()
#pragma code_seg(".text$f0041f800F")
__declspec(noinline) LinePolarVelocity_0041f800* LinePolarVelocity_0041f800::SetPolar(float angle,float speed) {
    x=static_cast<float>(cos(angle)*speed);
    y=static_cast<float>(sin(angle)*speed);
    return this;
}
#pragma code_seg()

