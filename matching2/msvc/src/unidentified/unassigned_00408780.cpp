#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00408780..0x00408789: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00408780() {
    __asm {
    L_00408780:
        mov eax,dword ptr [eax+58h]
    L_00408783:
        shr eax,2
    L_00408786:
        and eax,1
    L_00408789:
        ret
    }
}
