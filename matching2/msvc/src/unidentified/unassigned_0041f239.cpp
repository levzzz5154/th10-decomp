#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041F239..0x0041F23F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0041f239() {
    __asm {
    L_0041f239:
        lea esp,[esp+force_disp32_zero]
    }
}
