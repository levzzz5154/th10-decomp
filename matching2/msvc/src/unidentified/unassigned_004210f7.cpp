#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004210F7..0x004210FF: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004210f7() {
    __asm {
    L_004210f7:
        lea esp,[esp+force_disp32_zero]
    L_004210fe:
        mov edi,edi
    }
}
