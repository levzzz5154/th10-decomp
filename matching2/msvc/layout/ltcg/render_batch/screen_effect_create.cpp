// Copy compiled into the render batch link so the stage background task sees
// the screen effect factory's private entry convention.
#include "th10/render/screen_effect_controller.hpp"

#pragma code_seg(".text$03w6effect")

// The native closure supplies the draw priority in EBX and the five effect
// parameters on the stack. The inline constructor retains the original
// timer flag access before the complete state wipe.
ScreenEffectController* __stdcall CreateScreenEffect_0043c8b0(
        int priority, int mode, int first, int second, int third, int fourth) {
    ScreenEffectController* owner = new ScreenEffectController;
    if (owner) {
        owner->Configure(priority, mode, first, second, third, fourth);
    }
    return owner;
}

#pragma code_seg()
