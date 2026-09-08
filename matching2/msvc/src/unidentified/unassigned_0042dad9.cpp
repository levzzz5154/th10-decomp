#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042DAD9..0x0042DADF: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042dad9() {
    __asm {
    L_0042dad9:
        lea esp,[esp+force_disp32_zero]
    }
}
