#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00413290..0x0041329B: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00413290() {
    __asm {
    L_00413290:
        call asm_Rng_NextFloatSigned_0044bb90
    L_00413295:
        fmul dword ptr [data_00470b18]
    L_0041329b:
        ret
    }
}
