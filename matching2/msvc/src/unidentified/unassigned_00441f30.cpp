#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00441F30..0x00441F38: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00441f30() {
    __asm {
    L_00441f30:
        fld dword ptr [esp+4]
    L_00441f34:
        fcos
    L_00441f36:
        ret 4
    }
}
