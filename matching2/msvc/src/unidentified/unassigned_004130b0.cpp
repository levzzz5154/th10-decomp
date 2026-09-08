#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004130B0..0x004130B6: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004130b0() {
    __asm {
    L_004130b0:
        fld dword ptr [esp+4]
    L_004130b4:
        fabs
    L_004130b6:
        ret
    }
}
