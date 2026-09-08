#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00428CA0..0x00428CD3: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00428ca0() {
    __asm {
    L_00428ca0:
        cmp dword ptr [eax+3504h],edx
    L_00428ca6:
        jne short L_00428cb9
    L_00428ca8:
        mov dword ptr [eax+3504h],0
    L_00428cb2:
        mov byte ptr [eax+3508h],0
    L_00428cb9:
        add eax,4E8h
    L_00428cbe:
        mov ecx,80h
    L_00428cc3:
        cmp dword ptr [eax],edx
    L_00428cc5:
        jne short L_00428ccd
    L_00428cc7:
        mov dword ptr [eax],0
    L_00428ccd:
        add eax,5Ch
    L_00428cd0:
        dec ecx
    L_00428cd1:
        jne short L_00428cc3
    L_00428cd3:
        ret
    }
}
