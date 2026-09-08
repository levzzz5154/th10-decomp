#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00408720..0x00408728: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00408720() {
    __asm {
    L_00408720:
        fld dword ptr [esp+4]
    L_00408724:
        fabs
    L_00408726:
        ret 4
    }
}
