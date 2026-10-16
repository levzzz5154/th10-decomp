#include "th10/game/pause_choice/state.hpp"
// 0x0040AC90. Publish the requested input mode on a state object, unless the
// object's +0x3CC flag word has bit 0x1000 set, in which case the mode is
// forced to 2. Retail passes the object in EAX and the mode on the stack, and
// the callee pops it:
//
//   L6: mov  ecx,[eax+3CCh]        ; 8b 88 cc 03 00 00
//               test ch,10h                ; f6 c5 10
//               jne  L7            ; 75 0d
//               mov  ecx,[esp+4]           ; 8b 4c 24 04
//               mov  [eax+390h],ecx        ; 89 88 90 03 00 00
//               ret  4                     ; c2 04 00
//   L7: mov  dword ptr [eax+390h],2
//               ret  4
//
// The complete pause updater calls this helper with the global state object
// and the requested mode; native LTCG recovers the same register boundary.



__declspec(noinline) void SetInputMode(InputState* state, int mode);

#pragma code_seg(".text$07inputmode")
void SetInputMode(InputState* state, int mode) {
    if ((state->flags_3CC & 0x1000) == 0) {
        state->mode_390 = mode;
    } else {
        state->mode_390 = 2;
    }
}
#pragma code_seg()
