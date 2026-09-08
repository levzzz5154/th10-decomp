#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042B6B0..0x0042B6CA: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042b6b0() {
    __asm {
    L_0042b6b0:
        push esi
    L_0042b6b1:
        call asm_FUN_0042b570_0042b570
    L_0042b6b6:
        test byte ptr [esp+4],1
    L_0042b6bb:
        je short L_0042b6c6
    L_0042b6bd:
        push esi
    L_0042b6be:
        call asm_free_004524a1
    L_0042b6c3:
        add esp,4
    L_0042b6c6:
        mov eax,esi
    L_0042b6c8:
        ret 4
    }
}
