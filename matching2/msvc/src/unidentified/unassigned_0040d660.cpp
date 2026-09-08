#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040D660..0x0040D67D: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040d660() {
    __asm {
    L_0040d660:
        push esi
    L_0040d661:
        mov esi,eax
    L_0040d663:
        call asm_BulletEntity_ReleaseResource_0040d680
    L_0040d668:
        test byte ptr [esp+8],1
    L_0040d66d:
        je short L_0040d678
    L_0040d66f:
        push esi
    L_0040d670:
        call asm_free_004524a1
    L_0040d675:
        add esp,4
    L_0040d678:
        mov eax,esi
    L_0040d67a:
        pop esi
    L_0040d67b:
        ret 4
    }
}
