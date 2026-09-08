#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004257C8..0x004257CE: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004257c8() {
    __asm {
    L_004257c8:
        lea esp,[esp+force_disp32_zero]
    }
}
