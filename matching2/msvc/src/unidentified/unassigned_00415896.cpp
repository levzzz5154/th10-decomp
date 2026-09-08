#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00415896..0x0041589F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00415896() {
    __asm {
    L_00415896:
        lea esp,[esp+force_disp32_zero]
    L_0041589d:
        TH10_NOP_LEA_ECX_DISP8()
    }
}
