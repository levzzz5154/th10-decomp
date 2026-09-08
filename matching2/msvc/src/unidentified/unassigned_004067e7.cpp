#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004067E7..0x004067EF: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004067e7() {
    __asm {
    L_004067e7:
        lea esp,[esp+force_disp32_zero]
    L_004067ee:
        mov edi,edi
    }
}
