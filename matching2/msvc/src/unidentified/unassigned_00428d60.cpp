#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00428D60..0x00428D63: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00428d60() {
    __asm {
    L_00428d60:
        fld dword ptr [eax+2Ch]
    L_00428d63:
        ret
    }
}
