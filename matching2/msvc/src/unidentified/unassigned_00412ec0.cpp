#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00412EC0..0x00412EC7: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00412ec0() {
    __asm {
    L_00412ec0:
        fld dword ptr [eax+4]
    L_00412ec3:
        fld dword ptr [eax]
    L_00412ec5:
        fpatan
    L_00412ec7:
        ret
    }
}
