#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00441F20..0x00441F2B: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00441f20() {
    __asm {
    L_00441f20:
        fld dword ptr [esp+4]
    L_00441f24:
        call asm_FUN_00463bf0_00463bf0
    L_00441f29:
        ret 4
    }
}
