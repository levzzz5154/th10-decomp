#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041B8F8..0x0041B8FE: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0041b8f8() {
    __asm {
    L_0041b8f8:
        lea esp,[esp+force_disp32_zero]
    }
}
