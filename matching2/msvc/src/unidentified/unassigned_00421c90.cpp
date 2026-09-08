#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421C90..0x00421C9C: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00421c90() {
    __asm {
    L_00421c90:
        mov eax,dword ptr [eax+150h]
    L_00421c96:
        shr eax,6
    L_00421c99:
        and eax,1
    L_00421c9c:
        ret
    }
}
