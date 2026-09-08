#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042AE14..0x0042AE1F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042ae14() {
    __asm {
    L_0042ae14:
        lea esp,[esp+force_disp32_zero]
    L_0042ae1b:
        TH10_REL8(0xeb, 0x0042ae1b, VA_asm_Recovery_InitializeRandomTable_part_0042ae20)
    L_0042ae1d:
        TH10_NOP_LEA_ECX_DISP8()
    }
}
