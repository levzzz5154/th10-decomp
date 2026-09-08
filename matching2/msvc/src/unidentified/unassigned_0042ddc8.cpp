#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042DDC8..0x0042DDCE: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042ddc8() {
    __asm {
    L_0042ddc8:
        lea esp,[esp+force_disp32_zero]
    }
}
