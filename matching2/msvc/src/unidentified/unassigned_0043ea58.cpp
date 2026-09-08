#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043EA58..0x0043EA5E: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0043ea58() {
    __asm {
    L_0043ea58:
        lea esp,[esp+force_disp32_zero]
    }
}
