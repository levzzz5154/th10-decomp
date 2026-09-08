#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042EDD8..0x0042EDDE: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042edd8() {
    __asm {
    L_0042edd8:
        lea esp,[esp+force_disp32_zero]
    }
}
