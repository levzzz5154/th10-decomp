#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004278D8..0x004278DE: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004278d8() {
    __asm {
    L_004278d8:
        lea esp,[esp+force_disp32_zero]
    }
}
