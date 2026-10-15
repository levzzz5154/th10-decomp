// 0x00441F30..0x00441F38: out-of-line copy of the float cosine wrapper.
//
// The body is the MSVC x87 intrinsic expansion of cosf; the argument stays on
// the stack (/Gz).
#include <math.h>

float FloatCos(float value) {
    return cosf(value);
}
