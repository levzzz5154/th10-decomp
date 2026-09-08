#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042EF39..0x0042EF3F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042ef39() {
    __asm {
    L_0042ef39:
        lea esp,[esp+force_disp32_zero]
    }
}
