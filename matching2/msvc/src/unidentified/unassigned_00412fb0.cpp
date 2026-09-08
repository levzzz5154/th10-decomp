#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00412FB0..0x00412FB6: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00412fb0() {
    __asm {
    L_00412fb0:
        fld dword ptr [eax+4Ch]
    L_00412fb3:
        fmul dword ptr [eax+3Ch]
    L_00412fb6:
        ret
    }
}
