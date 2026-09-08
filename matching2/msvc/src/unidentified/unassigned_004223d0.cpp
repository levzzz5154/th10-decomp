#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004223D0..0x004223E1: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004223d0() {
    __asm {
    L_004223d0:
        test esi,esi
    L_004223d2:
        je short L_004223e1
    L_004223d4:
        push esi
    L_004223d5:
        call asm_FUN_00422220_00422220
    L_004223da:
        push esi
    L_004223db:
        call asm_free_004524a1
    L_004223e0:
        pop ecx
    L_004223e1:
        ret
    }
}
