#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00449418..0x0044941E: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00449418() {
    __asm {
    L_00449418:
        lea esp,[esp+force_disp32_zero]
    }
}
