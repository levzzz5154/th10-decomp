#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004210B9..0x004210BF: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004210b9() {
    __asm {
    L_004210b9:
        lea esp,[esp+force_disp32_zero]
    }
}
