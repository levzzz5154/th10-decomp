#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042F166..0x0042F16F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042f166() {
    __asm {
    L_0042f166:
        lea esp,[esp+force_disp32_zero]
    L_0042f16d:
        TH10_NOP_LEA_ECX_DISP8()
    }
}
