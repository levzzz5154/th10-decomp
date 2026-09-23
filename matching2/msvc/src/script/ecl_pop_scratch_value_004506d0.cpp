// 0x004506D0..0x004506F8: pop the current value from the ECL scratch stack.
// The interpreter passes &vm->frame in EAX and supplies no stack arguments.
#include "th10/script/ecl_scratch_frame_00450690.hpp"

#pragma code_seg(".text$02pop")
int EclFrame_00450690::PopScratchValue() {
    int offset = -4 + sp;
    int previous_frame_base = frame_base;
    if (offset >= 0) {
        sp = offset;
        frame_base = *(int*)((unsigned char*)this + offset);
    }
    sp = previous_frame_base;
    return 0;
}
#pragma code_seg()
