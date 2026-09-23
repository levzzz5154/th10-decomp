#include <float.h>

namespace {

int sign_extend_x87_word(unsigned int value) {
    const unsigned int word = value & 0xffffu;
    return (word & 0x8000u) != 0
        ? static_cast<int>(word) - 0x10000
        : static_cast<int>(word);
}

} // namespace

// 0x0045ED70..0x0045ED7A: __statfp
// FSTSW observes the x87 status word after waiting for pending x87 exceptions.
// _status87 provides that x87-only status; preserve MOVSX's signed 16-bit EAX
// result instead of the public API's unsigned int presentation.
extern "C" int __cdecl asm_statfp_0045ed70(void) {
    return sign_extend_x87_word(_status87());
}
