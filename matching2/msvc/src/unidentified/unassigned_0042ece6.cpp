#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042ECE6..0x0042ECEF: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042ece6() {
    __asm {
    L_0042ece6:
        lea esp,[esp+force_disp32_zero]
    L_0042eced:
        TH10_NOP_LEA_ECX_DISP8()
    }
}
