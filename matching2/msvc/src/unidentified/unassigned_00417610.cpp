#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00417610..0x00417616: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00417610() {
    __asm {
    L_00417610:
        movzx eax,word ptr [eax+32h]
    L_00417614:
        and eax,ecx
    L_00417616:
        ret
    }
}
