#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042DA28..0x0042DA2E: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042da28() {
    __asm {
    L_0042da28:
        lea esp,[esp+force_disp32_zero]
    }
}
