#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004093C8..0x004093CE: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004093c8() {
    __asm {
    L_004093c8:
        lea esp,[esp+force_disp32_zero]
    }
}
