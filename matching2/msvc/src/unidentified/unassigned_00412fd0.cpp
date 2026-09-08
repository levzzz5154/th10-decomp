#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00412FD0..0x00412FD3: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00412fd0() {
    __asm {
    L_00412fd0:
        fld dword ptr [eax+8]
    L_00412fd3:
        ret
    }
}
