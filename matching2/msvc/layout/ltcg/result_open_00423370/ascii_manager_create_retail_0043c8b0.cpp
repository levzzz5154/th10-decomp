#include "th10/game/runtime_selector_0043c970.hpp"

#pragma code_seg(".text$0043c8b0_fn")

// The native closure supplies the draw priority in EBX and the five effect
// parameters on the stack. The inline constructor retains the original
// timer flag access before the complete state wipe.
ScreenEffectController_0043c970* __stdcall CreateScreenEffect_0043c8b0(
        int priority, int mode, int first, int second, int third, int fourth) {
    ScreenEffectController_0043c970* owner = new ScreenEffectController_0043c970;
    if (owner) {
        owner->Configure(priority, mode, first, second, third, fourth);
    }
    return owner;
}

#pragma code_seg()
