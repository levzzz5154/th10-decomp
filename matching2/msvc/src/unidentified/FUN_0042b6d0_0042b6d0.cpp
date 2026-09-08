#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042B6D0..0x0042B6E1: FUN_0042b6d0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042b6d0_0042b6d0() {
    __asm {
    L_0042b6d0:
        test esi,esi
    L_0042b6d2:
        je short L_0042b6e1
    L_0042b6d4:
        push esi
    L_0042b6d5:
        call asm_FUN_0042b570_0042b570
    L_0042b6da:
        push esi
    L_0042b6db:
        call asm_free_004524a1
    L_0042b6e0:
        pop ecx
    L_0042b6e1:
        ret
    }
}
