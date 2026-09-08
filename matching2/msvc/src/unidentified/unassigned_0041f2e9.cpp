#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041F2E9..0x0041F2EF: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0041f2e9() {
    __asm {
    L_0041f2e9:
        lea esp,[esp+force_disp32_zero]
    }
}
