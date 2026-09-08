#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042DE16..0x0042DE1F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042de16() {
    __asm {
    L_0042de16:
        lea esp,[esp+force_disp32_zero]
    L_0042de1d:
        TH10_NOP_LEA_ECX_DISP8()
    }
}
