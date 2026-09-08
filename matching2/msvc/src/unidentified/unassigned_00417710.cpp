#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00417710..0x0041771C: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00417710() {
    __asm {
    L_00417710:
        mov eax,dword ptr [eax+2A18h]
    L_00417716:
        shr eax,3
    L_00417719:
        and eax,1
    L_0041771c:
        ret
    }
}
