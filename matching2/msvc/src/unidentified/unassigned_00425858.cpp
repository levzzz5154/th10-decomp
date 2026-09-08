#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00425858..0x0042585E: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00425858() {
    __asm {
    L_00425858:
        lea esp,[esp+force_disp32_zero]
    }
}
