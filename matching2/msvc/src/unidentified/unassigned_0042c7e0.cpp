#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042C7E0..0x0042C7F9: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042c7e0() {
    __asm {
    L_0042c7e0:
        mov edx,dword ptr [eax+ecx*4+2C4h]
    L_0042c7e7:
        push edx
    L_0042c7e8:
        mov edx,dword ptr [data_00491c10]
    L_0042c7ee:
        call asm_AnimationManager_Find_004491c0
    L_0042c7f3:
        neg eax
    L_0042c7f5:
        sbb eax,eax
    L_0042c7f7:
        neg eax
    L_0042c7f9:
        ret
    }
}
