// 0x00441F10..0x00441F1A: out-of-line copy of the float arc-tangent wrapper.
//
// The body is the MSVC x87 intrinsic expansion of atanf: /O2 folds the call into
// fld/fld1/fpatan, and the single float argument stays on the stack (/Gz).
#include <math.h>

float FloatAtan(float value) {
    return atanf(value);
}
