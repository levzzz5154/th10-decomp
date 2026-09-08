#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00433D09..0x00433D0F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00433d09() {
    __asm {
    L_00433d09:
        lea esp,[esp+force_disp32_zero]
    }
}
