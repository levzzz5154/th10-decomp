#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042E645..0x0042E64F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042e645() {
    __asm {
    L_0042e645:
        lea esp,[esp+force_disp32_zero]
    L_0042e64c:
        TH10_NOP_LEA_ESP_DISP8()
    }
}
