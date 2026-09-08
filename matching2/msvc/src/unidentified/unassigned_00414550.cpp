#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00414550..0x0041456D: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00414550() {
    __asm {
    L_00414550:
        push esi
    L_00414551:
        mov esi,eax
    L_00414553:
        call asm_AnimationSlot_ReleaseRetail_004136c0
    L_00414558:
        test byte ptr [esp+8],1
    L_0041455d:
        je short L_00414568
    L_0041455f:
        push esi
    L_00414560:
        call asm_free_004524a1
    L_00414565:
        add esp,4
    L_00414568:
        mov eax,esi
    L_0041456a:
        pop esi
    L_0041456b:
        ret 4
    }
}
