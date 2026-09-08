#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004475E7..0x004475EF: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004475e7() {
    __asm {
    L_004475e7:
        lea esp,[esp+force_disp32_zero]
    L_004475ee:
        mov edi,edi
    }
}
