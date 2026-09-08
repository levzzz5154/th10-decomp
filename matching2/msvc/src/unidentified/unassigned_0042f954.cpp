#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042F954..0x0042F95F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042f954() {
    __asm {
    L_0042f954:
        lea esp,[esp+force_disp32_zero]
    L_0042f95b:
        TH10_REL8(0xeb, 0x0042f95b, VA_asm_FUN_0042f8b0_part_0042f960)
    L_0042f95d:
        TH10_NOP_LEA_ECX_DISP8()
    }
}
