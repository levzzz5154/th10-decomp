#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00408710..0x0040871C: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00408710() {
    __asm {
    L_00408710:
        fld dword ptr [esp+4]
    L_00408714:
        fld dword ptr [esp+8]
    L_00408718:
        fpatan
    L_0040871a:
        ret 8
    }
}
