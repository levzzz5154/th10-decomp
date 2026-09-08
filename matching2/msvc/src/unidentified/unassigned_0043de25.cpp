#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043DE25..0x0043DE2F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0043de25() {
    __asm {
    L_0043de25:
        lea esp,[esp+force_disp32_zero]
    L_0043de2c:
        TH10_NOP_LEA_ESP_DISP8()
    }
}
