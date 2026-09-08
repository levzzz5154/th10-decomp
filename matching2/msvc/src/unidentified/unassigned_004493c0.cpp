#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004493C0..0x004493DA: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004493c0() {
    __asm {
    L_004493c0:
        mov eax,dword ptr [esp+4]
    L_004493c4:
        push eax
    L_004493c5:
        call asm_AnimationManager_Find_004491c0
    L_004493ca:
        test eax,eax
    L_004493cc:
        je short L_004493d6
    L_004493ce:
        add eax,340h
    L_004493d3:
        ret 4
    L_004493d6:
        xor eax,eax
    L_004493d8:
        ret 4
    }
}
