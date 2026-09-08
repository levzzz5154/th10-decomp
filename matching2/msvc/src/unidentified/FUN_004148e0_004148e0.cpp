#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004148E0..0x004148F1: FUN_004148e0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004148e0_004148e0() {
    __asm {
    L_004148e0:
        test esi,esi
    L_004148e2:
        je short L_004148f1
    L_004148e4:
        push esi
    L_004148e5:
        call asm_FUN_004145f0_004145f0
    L_004148ea:
        push esi
    L_004148eb:
        call asm_free_004524a1
    L_004148f0:
        pop ecx
    L_004148f1:
        ret
    }
}
