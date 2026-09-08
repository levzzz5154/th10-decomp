#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041C2F0..0x0041C30A: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0041c2f0() {
    __asm {
    L_0041c2f0:
        push esi
    L_0041c2f1:
        call asm_ScoreExtendedObject_DestroyRetail_0041c1c0
    L_0041c2f6:
        test byte ptr [esp+4],1
    L_0041c2fb:
        je short L_0041c306
    L_0041c2fd:
        push esi
    L_0041c2fe:
        call asm_free_004524a1
    L_0041c303:
        add esp,4
    L_0041c306:
        mov eax,esi
    L_0041c308:
        ret 4
    }
}
