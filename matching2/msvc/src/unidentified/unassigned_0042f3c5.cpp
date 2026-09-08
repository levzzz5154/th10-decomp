#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042F3C5..0x0042F3CF: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042f3c5() {
    __asm {
    L_0042f3c5:
        lea esp,[esp+force_disp32_zero]
    L_0042f3cc:
        TH10_NOP_LEA_ESP_DISP8()
    }
}
