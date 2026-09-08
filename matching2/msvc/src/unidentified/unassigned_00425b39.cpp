#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00425B39..0x00425B3F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00425b39() {
    __asm {
    L_00425b39:
        lea esp,[esp+force_disp32_zero]
    }
}
