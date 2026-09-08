#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405380..0x00405382: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00405380() {
    __asm {
    L_00405380:
        fld dword ptr [eax]
    L_00405382:
        ret
    }
}
