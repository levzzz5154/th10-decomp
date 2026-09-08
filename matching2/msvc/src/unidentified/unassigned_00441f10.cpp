#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00441F10..0x00441F1A: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00441f10() {
    __asm {
    L_00441f10:
        fld dword ptr [esp+4]
    L_00441f14:
        fld1
    L_00441f16:
        fpatan
    L_00441f18:
        ret 4
    }
}
