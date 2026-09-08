#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00452725..0x0045272F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00452725() {
    __asm {
    L_00452725:
        lea esp,[esp+force_disp32_zero]
    L_0045272c:
        TH10_NOP_LEA_ESP_DISP8()
    }
}
