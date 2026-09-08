#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043C890..0x0043C8AA: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0043c890() {
    __asm {
    L_0043c890:
        push esi
    L_0043c891:
        call asm_Recovery_ReleaseRawPair_0043cb00
    L_0043c896:
        test byte ptr [esp+4],1
    L_0043c89b:
        je short L_0043c8a6
    L_0043c89d:
        push esi
    L_0043c89e:
        call asm_free_004524a1
    L_0043c8a3:
        add esp,4
    L_0043c8a6:
        mov eax,esi
    L_0043c8a8:
        ret 4
    }
}
