#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044CAC5..0x0044CACF: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044cac5() {
    __asm {
    L_0044cac5:
        lea esp,[esp+force_disp32_zero]
    L_0044cacc:
        TH10_NOP_LEA_ESP_DISP8()
    }
}
