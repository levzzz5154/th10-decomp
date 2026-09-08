#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00406120..0x0040613A: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00406120() {
    __asm {
    L_00406120:
        push esi
    L_00406121:
        call asm_ItemManager_DestroyRetail_00405f70
    L_00406126:
        test byte ptr [esp+4],1
    L_0040612b:
        je short L_00406136
    L_0040612d:
        push esi
    L_0040612e:
        call asm_free_004524a1
    L_00406133:
        add esp,4
    L_00406136:
        mov eax,esi
    L_00406138:
        ret 4
    }
}
