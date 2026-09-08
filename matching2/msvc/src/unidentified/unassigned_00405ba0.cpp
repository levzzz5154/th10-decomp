#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405BA0..0x00405BA3: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00405ba0() {
    __asm {
    L_00405ba0:
        fld dword ptr [eax+40h]
    L_00405ba3:
        ret
    }
}
