#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00419BC7..0x00419BCF: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00419bc7() {
    __asm {
    L_00419bc7:
        lea esp,[esp+force_disp32_zero]
    L_00419bce:
        mov edi,edi
    }
}
