#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042EC36..0x0042EC3F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042ec36() {
    __asm {
    L_0042ec36:
        lea esp,[esp+force_disp32_zero]
    L_0042ec3d:
        TH10_NOP_LEA_ECX_DISP8()
    }
}
