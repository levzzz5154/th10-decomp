// 0x004506D0..0x004506F8: pop the current value from the ECL scratch stack.
// The interpreter passes &vm->frame in EAX and supplies no stack arguments.
#include <stdint.h>

#include "ecl_scratch_frame_00450690.hpp"

#pragma code_seg(".text$02pop")
extern "C" __attribute__((noinline, regparm(1)))
int EclPopScratchValue_004506d0(EclFrame_00450690* frame) {
    // The retail ADD is 32-bit wrapping arithmetic followed by a sign test.
    // Keep that behavior defined for every bit pattern in sp.
    const unsigned int offset = static_cast<unsigned int>(frame->sp) - 4u;
    const int previous_frame_base = frame->frame_base;
    if (offset < 0x80000000u) {
        frame->sp = static_cast<int>(offset);
        const uintptr_t address = reinterpret_cast<uintptr_t>(frame) +
                                  static_cast<uintptr_t>(offset);
        frame->frame_base = *reinterpret_cast<int*>(address);
    }
    frame->sp = previous_frame_base;
    return 0;
}
#pragma code_seg()
