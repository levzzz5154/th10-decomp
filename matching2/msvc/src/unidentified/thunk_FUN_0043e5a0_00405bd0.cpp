#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405BD0..0x00405BD4: thunk_FUN_0043e5a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_thunk_FUN_0043e5a0_00405bd0() {
    __asm {
    L_00405bd0:
        jmp asm_AnimationObject_ConfigureFromResource_0043e5a0
    }
}
