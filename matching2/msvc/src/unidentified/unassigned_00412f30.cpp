#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00412F30..0x00412F33: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00412f30() {
    __asm {
    L_00412f30:
        fld dword ptr [eax+20h]
    L_00412f33:
        ret
    }
}
