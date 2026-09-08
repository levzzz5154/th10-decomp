#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00441F40..0x00441F4F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00441f40() {
    __asm {
    L_00441f40:
        fld dword ptr [esp+4]
    L_00441f44:
        fld dword ptr [esp+8]
    L_00441f48:
        call asm_FUN_00463bba_00463bba
    L_00441f4d:
        ret 8
    }
}
