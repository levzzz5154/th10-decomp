#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044C5F0..0x0044C5F8: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044c5f0() {
    __asm {
    L_0044c5f0:
        fld dword ptr [esp+4]
    L_0044c5f4:
        fmul dword ptr [eax]
    L_0044c5f6:
        ret 4
    }
}
