#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042F255..0x0042F25F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042f255() {
    __asm {
    L_0042f255:
        lea esp,[esp+force_disp32_zero]
    L_0042f25c:
        TH10_NOP_LEA_ESP_DISP8()
    }
}
