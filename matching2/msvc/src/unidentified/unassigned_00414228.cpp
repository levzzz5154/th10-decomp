#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00414228..0x0041422E: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00414228() {
    __asm {
    L_00414228:
        lea esp,[esp+force_disp32_zero]
    }
}
