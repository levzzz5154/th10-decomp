#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421138..0x0042113E: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00421138() {
    __asm {
    L_00421138:
        lea esp,[esp+force_disp32_zero]
    }
}
