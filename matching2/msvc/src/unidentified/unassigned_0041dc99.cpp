#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041DC99..0x0041DC9F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0041dc99() {
    __asm {
    L_0041dc99:
        lea esp,[esp+force_disp32_zero]
    }
}
