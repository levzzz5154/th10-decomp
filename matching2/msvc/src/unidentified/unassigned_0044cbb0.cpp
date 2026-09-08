#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044CBB0..0x0044CBE1: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044cbb0() {
    __asm {
    L_0044cbb0:
        cmp dword ptr [esi+78h],1
    L_0044cbb4:
        jne short L_0044cbcd
    L_0044cbb6:
        mov eax,dword ptr [esi+8Ch]
    L_0044cbbc:
        push eax
    L_0044cbbd:
        call dword ptr [data_004660cc]
    L_0044cbc3:
        mov dword ptr [esi+8Ch],0FFFFFFFFh
    L_0044cbcd:
        test byte ptr [esp+4],1
    L_0044cbd2:
        je short L_0044cbdd
    L_0044cbd4:
        push esi
    L_0044cbd5:
        call asm_free_004524a1
    L_0044cbda:
        add esp,4
    L_0044cbdd:
        mov eax,esi
    L_0044cbdf:
        ret 4
    }
}
