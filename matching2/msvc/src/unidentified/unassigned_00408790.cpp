#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00408790..0x0040879D: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00408790() {
    __asm {
    L_00408790:
        mov ecx,dword ptr [eax+58h]
    L_00408793:
        mov eax,ecx
    L_00408795:
        shr eax,2
    L_00408798:
        or eax,ecx
    L_0040879a:
        and eax,1
    L_0040879d:
        ret
    }
}
