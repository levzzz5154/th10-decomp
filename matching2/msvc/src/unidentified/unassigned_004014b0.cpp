#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004014B0..0x004014C1: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004014b0() {
    __asm {
    L_004014b0:
        test esi,esi
    L_004014b2:
        je short L_004014c1
    L_004014b4:
        push esi
    L_004014b5:
        call asm_DestroyGameThread_00401260
    L_004014ba:
        push esi
    L_004014bb:
        call asm_free_004524a1
    L_004014c0:
        pop ecx
    L_004014c1:
        ret
    }
}
