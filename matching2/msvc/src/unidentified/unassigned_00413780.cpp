#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00413780..0x0041378C: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00413780() {
    __asm {
    L_00413780:
        mov eax,dword ptr [eax+9EB4h]
    L_00413786:
        shr eax,5
    L_00413789:
        and eax,1
    L_0041378c:
        ret
    }
}
