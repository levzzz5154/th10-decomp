// 0x004423C0: one saturated colour channel product, scaled by 1/128.
//
// The sprite pipelines pass the channel in AL and the manager's fade byte in
// CL; both callers and this definition have to share one native compiler scope
// for that private convention to be reproduced.
#include "th10/render/quad_batch.hpp"

#pragma code_seg(".text$04amult")
unsigned int AnimationColor_MultiplyChannel(unsigned char value, unsigned char scale) {
    unsigned int result = (value * (unsigned int)scale) >> 7;
    if (result >= 0x100) {
        result = 0xFF;
    }
    return result;
}
#pragma code_seg()
