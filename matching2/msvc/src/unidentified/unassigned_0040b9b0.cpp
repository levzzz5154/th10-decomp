#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040B9B0..0x0040B9CA: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040b9b0() {
    __asm {
    L_0040b9b0:
        push esi
    L_0040b9b1:
        call asm_FUN_0040b7b0_0040b7b0
    L_0040b9b6:
        test byte ptr [esp+4],1
    L_0040b9bb:
        je short L_0040b9c6
    L_0040b9bd:
        push esi
    L_0040b9be:
        call asm_free_004524a1
    L_0040b9c3:
        add esp,4
    L_0040b9c6:
        mov eax,esi
    L_0040b9c8:
        ret 4
    }
}
