#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004296D0..0x004296EA: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004296d0() {
    __asm {
    L_004296d0:
        push esi
    L_004296d1:
        call asm_FUN_004294a0_004294a0
    L_004296d6:
        test byte ptr [esp+4],1
    L_004296db:
        je short L_004296e6
    L_004296dd:
        push esi
    L_004296de:
        call asm_free_004524a1
    L_004296e3:
        add esp,4
    L_004296e6:
        mov eax,esi
    L_004296e8:
        ret 4
    }
}
