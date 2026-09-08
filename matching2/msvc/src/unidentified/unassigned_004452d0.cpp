#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004452D0..0x004452D8: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004452d0() {
    __asm {
    L_004452d0:
        fld dword ptr [esp+4]
    L_004452d4:
        fsqrt
    L_004452d6:
        ret 4
    }
}
