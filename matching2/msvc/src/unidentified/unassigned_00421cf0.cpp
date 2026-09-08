#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421CF0..0x00421CFC: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00421cf0() {
    __asm {
    L_00421cf0:
        mov eax,dword ptr [eax+150h]
    L_00421cf6:
        shr eax,2
    L_00421cf9:
        and eax,1
    L_00421cfc:
        ret
    }
}
