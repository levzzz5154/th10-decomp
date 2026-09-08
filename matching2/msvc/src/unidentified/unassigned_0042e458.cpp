#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042E458..0x0042E45E: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042e458() {
    __asm {
    L_0042e458:
        lea esp,[esp+force_disp32_zero]
    }
}
