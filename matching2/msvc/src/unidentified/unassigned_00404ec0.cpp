#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00404EC0..0x00404EC3: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00404ec0() {
    __asm {
    L_00404ec0:
        fld dword ptr [eax+8]
    L_00404ec3:
        ret
    }
}
