#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421BF0..0x00421BFA: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00421bf0() {
    __asm {
    L_00421bf0:
        fld dword ptr [esp+4]
    L_00421bf4:
        fptan
    L_00421bf6:
        fstp st(0)
    L_00421bf8:
        ret 4
    }
}
