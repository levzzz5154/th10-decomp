#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00442180..0x00442193: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00442180() {
    __asm {
    L_00442180:
        movzx edx,byte ptr [ecx+2]
    L_00442184:
        mov dword ptr [eax+8],edx
    L_00442187:
        movzx edx,byte ptr [ecx+1]
    L_0044218b:
        mov dword ptr [eax+4],edx
    L_0044218e:
        movzx ecx,byte ptr [ecx]
    L_00442191:
        mov dword ptr [eax],ecx
    L_00442193:
        ret
    }
}
