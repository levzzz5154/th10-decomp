#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042A850..0x0042A866: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042a850() {
    __asm {
    L_0042a850:
        mov ecx,dword ptr [eax+5460h]
    L_0042a856:
        sub ecx,eax
    L_0042a858:
        mov eax,2AAAAAABh
    L_0042a85d:
        imul ecx
    L_0042a85f:
        mov eax,edx
    L_0042a861:
        shr eax,1Fh
    L_0042a864:
        add eax,edx
    L_0042a866:
        ret
    }
}
