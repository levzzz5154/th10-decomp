#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004318A6..0x004318AF: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004318a6() {
    __asm {
    L_004318a6:
        lea esp,[esp+force_disp32_zero]
    L_004318ad:
        TH10_NOP_LEA_ECX_DISP8()
    }
}
