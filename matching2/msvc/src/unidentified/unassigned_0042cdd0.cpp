#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042CDD0..0x0042CDEA: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042cdd0() {
    __asm {
    L_0042cdd0:
        push esi
    L_0042cdd1:
        call asm_FUN_0042cb60_0042cb60
    L_0042cdd6:
        test byte ptr [esp+4],1
    L_0042cddb:
        je short L_0042cde6
    L_0042cddd:
        push esi
    L_0042cdde:
        call asm_free_004524a1
    L_0042cde3:
        add esp,4
    L_0042cde6:
        mov eax,esi
    L_0042cde8:
        ret 4
    }
}
