#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00412F80..0x00412F83: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00412f80() {
    __asm {
    L_00412f80:
        fld dword ptr [eax+18h]
    L_00412f83:
        ret
    }
}
