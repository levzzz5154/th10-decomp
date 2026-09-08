#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00427CC0..0x00427CD5: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00427cc0() {
    __asm {
    L_00427cc0:
        movsx ecx,word ptr [eax+8]
    L_00427cc4:
        mov eax,66666667h
    L_00427cc9:
        imul ecx
    L_00427ccb:
        sar edx,3
    L_00427cce:
        mov eax,edx
    L_00427cd0:
        shr eax,1Fh
    L_00427cd3:
        add eax,edx
    L_00427cd5:
        ret
    }
}
