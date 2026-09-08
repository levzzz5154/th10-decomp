#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421BE0..0x00421BE8: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00421be0() {
    __asm {
    L_00421be0:
        fld dword ptr [esp+4]
    L_00421be4:
        fptan
    L_00421be6:
        fstp st(0)
    L_00421be8:
        ret
    }
}
