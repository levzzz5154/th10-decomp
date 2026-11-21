// 0x00415AE0: Front_OnUpdate
#include "th10/runtime/asm_symbols.hpp"

// 0x00415AE0: the HUD's update task. Forward the object pointer into the still-assembly routine at
// 0x00414900 and return its result. The argument is passed on the stack, so the
// callee's prototype is __stdcall (one stack word, callee cleans).
typedef int(__stdcall* RuntimeDispatchFn)(void* self);

int __fastcall Front_OnUpdate(void* self) {
    return ((RuntimeDispatchFn)Front_UpdateHudState)(self);
}
