#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004393C9..0x004393CF: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004393c9() {
    __asm {
    L_004393c9:
        lea esp,[esp+force_disp32_zero]
    }
}
