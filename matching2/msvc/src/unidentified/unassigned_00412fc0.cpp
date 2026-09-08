#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00412FC0..0x00412FC6: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00412fc0() {
    __asm {
    L_00412fc0:
        fld dword ptr [eax+50h]
    L_00412fc3:
        fmul dword ptr [eax+40h]
    L_00412fc6:
        ret
    }
}
