#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041E179..0x0041E17F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0041e179() {
    __asm {
    L_0041e179:
        lea esp,[esp+force_disp32_zero]
    }
}
