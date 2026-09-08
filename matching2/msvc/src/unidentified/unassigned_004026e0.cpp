#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004026E0..0x004026FA: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004026e0() {
    __asm {
    L_004026e0:
        push esi
    L_004026e1:
        call asm_DestroyGameState_00402440
    L_004026e6:
        test byte ptr [esp+4],1
    L_004026eb:
        je short L_004026f6
    L_004026ed:
        push esi
    L_004026ee:
        call asm_free_004524a1
    L_004026f3:
        add esp,4
    L_004026f6:
        mov eax,esi
    L_004026f8:
        ret 4
    }
}
