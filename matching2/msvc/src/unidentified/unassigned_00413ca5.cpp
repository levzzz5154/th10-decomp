#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00413CA5..0x00413CAF: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00413ca5() {
    __asm {
    L_00413ca5:
        lea esp,[esp+force_disp32_zero]
    L_00413cac:
        TH10_NOP_LEA_ESP_DISP8()
    }
}
