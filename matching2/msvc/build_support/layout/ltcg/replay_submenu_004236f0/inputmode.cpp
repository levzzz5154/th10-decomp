#include "th10/game/replay_submenu_004236f0/state.hpp"
// 0x0040AC90. Publish the requested input mode on a state object, unless the
// object's +0x3CC flag word has bit 0x1000 set, in which case the mode is
// forced to 2. Retail passes the object in EAX and the mode on the stack,
// and the callee pops it (RET 4).
#pragma code_seg(".text$00f")
void SubSetInputMode(InputState* state, int mode) {
    if ((state->flags_3CC & 0x1000) == 0) {
        state->mode_390 = mode;
    } else {
        state->mode_390 = 2;
    }
}
#pragma code_seg()
