#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00426D99..0x00426D9F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00426d99() {
    __asm {
    L_00426d99:
        lea esp,[esp+force_disp32_zero]
    }
}
