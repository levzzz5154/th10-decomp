#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00449499..0x0044949F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00449499() {
    __asm {
    L_00449499:
        lea esp,[esp+force_disp32_zero]
    }
}
