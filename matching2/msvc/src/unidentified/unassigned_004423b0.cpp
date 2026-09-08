#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004423B0..0x004423BB: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004423b0() {
    __asm {
    L_004423b0:
        call asm_Rng_NextFloatSigned_0044bb90
    L_004423b5:
        fmul dword ptr [esp+4]
    L_004423b9:
        ret 4
    }
}
