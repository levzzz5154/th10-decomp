#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00436FD9..0x00436FDF: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00436fd9() {
    __asm {
    L_00436fd9:
        lea esp,[esp+force_disp32_zero]
    }
}
