#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042E1D8..0x0042E1DE: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042e1d8() {
    __asm {
    L_0042e1d8:
        lea esp,[esp+force_disp32_zero]
    }
}
