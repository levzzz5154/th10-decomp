#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042BDD0..0x0042BE07: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042bdd0() {
    __asm {
    L_0042bdd0:
        mov eax,dword ptr [esi+8Ch]
    L_0042bdd6:
        test eax,eax
    L_0042bdd8:
        mov dword ptr [esi],46D0F0h
    L_0042bdde:
        je short L_0042bdf3
    L_0042bde0:
        push eax
    L_0042bde1:
        call asm_free_00452422
    L_0042bde6:
        add esp,4
    L_0042bde9:
        mov dword ptr [esi+8Ch],0
    L_0042bdf3:
        test byte ptr [esp+4],1
    L_0042bdf8:
        je short L_0042be03
    L_0042bdfa:
        push esi
    L_0042bdfb:
        call asm_free_004524a1
    L_0042be00:
        add esp,4
    L_0042be03:
        mov eax,esi
    L_0042be05:
        ret 4
    }
}
