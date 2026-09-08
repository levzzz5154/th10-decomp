#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042BFA0..0x0042BFB1: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042bfa0() {
    __asm {
    L_0042bfa0:
        test esi,esi
    L_0042bfa2:
        je short L_0042bfb1
    L_0042bfa4:
        push esi
    L_0042bfa5:
        call asm_FUN_0042bc30_0042bc30
    L_0042bfaa:
        push esi
    L_0042bfab:
        call asm_free_004524a1
    L_0042bfb0:
        pop ecx
    L_0042bfb1:
        ret
    }
}
