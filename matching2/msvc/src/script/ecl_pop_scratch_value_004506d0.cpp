// 0x004506D0: leave the current scratch frame. The stack pointer returns to
// the frame base, and the caller's frame base is popped back from the word
// below the current stack pointer when there is one. The frame arrives in EAX.
#include "th10/script/ecl_frame.hpp"

#pragma code_seg(".text$01fn")
int EclFrame_00450690::Pop() {
    int base = frame_base;
    if (sp - (int)sizeof(int) >= 0) {
        sp -= sizeof(int);
        frame_base = *(int*)(scratch + sp);
    }
    sp = base;
    return 0;
}
#pragma code_seg()
