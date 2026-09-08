#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00417600..0x00417609: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00417600() {
    __asm {
    L_00417600:
        mov eax,dword ptr [eax+60h]
    L_00417603:
        shr eax,4
    L_00417606:
        and eax,1
    L_00417609:
        ret
    }
}
