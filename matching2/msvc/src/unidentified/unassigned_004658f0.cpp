#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004658F0..0x00465909: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004658f0() {
    __asm {
    L_004658f0:
        push esi
    L_004658f1:
        mov esi,491C28h
    L_004658f6:
        call asm_Recovery_InitializeLargeState_00421f00
    L_004658fb:
        push 4659F0h
    L_00465900:
        call asm_atexit_00452e0a
    L_00465905:
        add esp,4
    L_00465908:
        pop esi
    L_00465909:
        ret
    }
}
