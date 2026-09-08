#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00428F20..0x00428F23: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00428f20() {
    __asm {
    L_00428f20:
        fld dword ptr [eax+34h]
    L_00428f23:
        ret
    }
}
