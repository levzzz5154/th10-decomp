#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004190E0..0x004190FA: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004190e0() {
    __asm {
    L_004190e0:
        push esi
    L_004190e1:
        call asm_FUN_00418ee0_00418ee0
    L_004190e6:
        test byte ptr [esp+4],1
    L_004190eb:
        je short L_004190f6
    L_004190ed:
        push esi
    L_004190ee:
        call asm_free_004524a1
    L_004190f3:
        add esp,4
    L_004190f6:
        mov eax,esi
    L_004190f8:
        ret 4
    }
}
