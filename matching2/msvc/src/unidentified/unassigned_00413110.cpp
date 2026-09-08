#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00413110..0x00413112: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00413110() {
    __asm {
    L_00413110:
        fld dword ptr [eax]
    L_00413112:
        ret
    }
}
