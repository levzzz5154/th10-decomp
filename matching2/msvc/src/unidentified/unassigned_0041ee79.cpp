#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041EE79..0x0041EE7F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0041ee79() {
    __asm {
    L_0041ee79:
        lea esp,[esp+force_disp32_zero]
    }
}
