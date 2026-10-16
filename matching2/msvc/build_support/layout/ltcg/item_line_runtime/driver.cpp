// Complete allocator/animation graph reached by the two actual line callers.
// These ordinary polar bodies retain their public member ABI. Their FCOS/FSIN
// output is unselected; production has separate exact FSINCOS recoveries.
#include "allocator.cpp"
#include "../../../../src/game/laser/fun.cpp"
#include "types/line_sweeps.hpp"
#include "dependencies.cpp"
#include "loader.cpp"
#include "configure.cpp"
#include "create.cpp"
#include <math.h>
#pragma intrinsic(cos,sin)
#pragma code_seg(".text$35itempolar")
__declspec(noinline) ItemPolarVelocity2* ItemPolarVelocity2::SetPolar(float angle,float speed) {
    x=static_cast<float>(cos(angle)*speed);
    y=static_cast<float>(sin(angle)*speed);
    return this;
}
#pragma code_seg()
#pragma code_seg(".text$55linepolar")
__declspec(noinline) LinePolarVelocity2* LinePolarVelocity2::SetPolar(float angle,float speed) {
    x=static_cast<float>(cos(angle)*speed);
    y=static_cast<float>(sin(angle)*speed);
    return this;
}
#pragma code_seg()

