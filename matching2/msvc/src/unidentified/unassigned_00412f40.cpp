#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00412F40..0x00412F43: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00412f40() {
    __asm {
    L_00412f40:
        fld dword ptr [eax+24h]
    L_00412f43:
        ret
    }
}
