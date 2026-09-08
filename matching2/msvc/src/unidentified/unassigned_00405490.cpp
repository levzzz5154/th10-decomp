#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405490..0x00405493: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00405490() {
    __asm {
    L_00405490:
        fld dword ptr [eax+8]
    L_00405493:
        ret
    }
}
