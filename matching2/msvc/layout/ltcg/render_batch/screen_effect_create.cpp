// Copy compiled into the render batch link so the stage background task sees
// the screen effect factory's private entry convention.
#include "th10/core/screen.hpp"

#pragma code_seg(".text$03w6effect")

// The native closure supplies the draw priority in EBX and the five effect
// parameters on the stack. The inline constructor retains the original
// timer flag access before the complete state wipe.
Screen* __stdcall Screen_Create(
        int priority, int mode, int first, int second, int third, int fourth) {
    Screen* owner = new Screen;
    if (owner) {
        owner->Configure(priority, mode, first, second, third, fourth);
    }
    return owner;
}

#pragma code_seg()
