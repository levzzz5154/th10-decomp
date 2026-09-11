#include "asm_symbols.hpp"

// 0x00415AE0 - forward the object pointer into the still-assembly routine at
// 0x00414900 and return its result. The argument is passed on the stack, so the
// callee's prototype is __stdcall (one stack word, callee cleans).
typedef int(__stdcall* RuntimeDispatchFn)(void* self);

int __fastcall FUN_00415ae0_00415ae0(void* self) {
    return ((RuntimeDispatchFn)asm_FUN_00414900_00414900)(self);
}
