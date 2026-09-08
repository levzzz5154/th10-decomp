#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040B920..0x0040B93B: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040b920() {
    __asm {
    L_0040b920:
        mov eax,esi
    L_0040b922:
        call asm_FUN_0040b3a0_0040b3a0
    L_0040b927:
        test byte ptr [esp+4],1
    L_0040b92c:
        je short L_0040b937
    L_0040b92e:
        push esi
    L_0040b92f:
        call asm_free_004524a1
    L_0040b934:
        add esp,4
    L_0040b937:
        mov eax,esi
    L_0040b939:
        ret 4
    }
}
