#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00408D20..0x00408D3A: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00408d20() {
    __asm {
    L_00408d20:
        push esi
    L_00408d21:
        call asm_FUN_00408af0_00408af0
    L_00408d26:
        test byte ptr [esp+4],1
    L_00408d2b:
        je short L_00408d36
    L_00408d2d:
        push esi
    L_00408d2e:
        call asm_free_004524a1
    L_00408d33:
        add esp,4
    L_00408d36:
        mov eax,esi
    L_00408d38:
        ret 4
    }
}
