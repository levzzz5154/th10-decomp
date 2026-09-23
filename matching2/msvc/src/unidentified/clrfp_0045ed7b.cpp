#include <float.h>

namespace {

int sign_extend_x87_word(unsigned int value) {
    const unsigned int word = value & 0xffffu;
    return (word & 0x8000u) != 0
        ? static_cast<int>(word) - 0x10000
        : static_cast<int>(word);
}

} // namespace

// 0x0045ED7B..0x0045ED86: __clrfp
// The retail sequence snapshots the x87 status word without waiting, then
// clears the x87 exception state. _clear87 expresses that x87-only operation;
// keep the signed 16-bit return observed in EAX.
extern "C" int __cdecl asm_clrfp_0045ed7b(void) {
    return sign_extend_x87_word(_clear87());
}
