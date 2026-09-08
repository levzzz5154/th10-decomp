#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00417690..0x00417699: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00417690() {
    __asm {
    L_00417690:
        mov eax,dword ptr [eax+60h]
    L_00417693:
        shr eax,5
    L_00417696:
        and eax,1
    L_00417699:
        ret
    }
}
