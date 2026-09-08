#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00428D30..0x00428D3C: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00428d30() {
    __asm {
    L_00428d30:
        fld dword ptr [eax+4]
    L_00428d33:
        fsub dword ptr [ecx+4]
    L_00428d36:
        fld dword ptr [eax]
    L_00428d38:
        fsub dword ptr [ecx]
    L_00428d3a:
        fpatan
    L_00428d3c:
        ret
    }
}
