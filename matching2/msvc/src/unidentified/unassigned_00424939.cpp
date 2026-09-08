#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00424939..0x0042493F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00424939() {
    __asm {
    L_00424939:
        lea esp,[esp+force_disp32_zero]
    }
}
