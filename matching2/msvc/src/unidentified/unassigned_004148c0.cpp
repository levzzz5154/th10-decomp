#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004148C0..0x004148DA: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004148c0() {
    __asm {
    L_004148c0:
        push esi
    L_004148c1:
        call asm_FUN_004145f0_004145f0
    L_004148c6:
        test byte ptr [esp+4],1
    L_004148cb:
        je short L_004148d6
    L_004148cd:
        push esi
    L_004148ce:
        call asm_free_004524a1
    L_004148d3:
        add esp,4
    L_004148d6:
        mov eax,esi
    L_004148d8:
        ret 4
    }
}
