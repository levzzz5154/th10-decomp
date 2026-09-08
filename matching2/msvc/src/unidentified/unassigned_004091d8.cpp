#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004091D8..0x004091DE: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004091d8() {
    __asm {
    L_004091d8:
        lea esp,[esp+force_disp32_zero]
    }
}
