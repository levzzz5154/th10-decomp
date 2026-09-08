#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040AFF0..0x0040B00A: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040aff0() {
    __asm {
    L_0040aff0:
        push esi
    L_0040aff1:
        call asm_BulletManager_Release_0040af00
    L_0040aff6:
        test byte ptr [esp+4],1
    L_0040affb:
        je short L_0040b006
    L_0040affd:
        push esi
    L_0040affe:
        call asm_free_004524a1
    L_0040b003:
        add esp,4
    L_0040b006:
        mov eax,esi
    L_0040b008:
        ret 4
    }
}
