#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042C8F9..0x0042C8FF: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042c8f9() {
    __asm {
    L_0042c8f9:
        lea esp,[esp+force_disp32_zero]
    }
}
