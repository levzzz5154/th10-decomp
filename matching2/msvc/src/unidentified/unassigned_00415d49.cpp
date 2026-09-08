#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00415D49..0x00415D4F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00415d49() {
    __asm {
    L_00415d49:
        lea esp,[esp+force_disp32_zero]
    }
}
