// 0x004452D0..0x004452D8: out-of-line copy of the float square root.
//
// The body is the MSVC x87 intrinsic expansion of sqrtf; the argument stays on
// the stack (/Gz).
#include <math.h>

float FloatSqrt(float value) {
    return sqrtf(value);
}
