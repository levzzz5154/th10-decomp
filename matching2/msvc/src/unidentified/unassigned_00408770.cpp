#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00408770..0x0040877B: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00408770() {
    __asm {
    L_00408770:
        call asm_Rng_NextFloat_0044bb20
    L_00408775:
        fmul dword ptr [esp+4]
    L_00408779:
        ret 4
    }
}
