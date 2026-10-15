// 0x00441F20..0x00441F2B: out-of-line copy of the float arc-sine wrapper.
//
// asinf has no single FPU instruction, so MSVC passes the argument on the x87
// stack and calls the CRT helper __CIasin (bound to retail's 0x00463BF0).
#include <math.h>

float FloatAsin_00441f20(float value) {
    return asinf(value);
}
