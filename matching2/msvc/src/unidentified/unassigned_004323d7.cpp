#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004323D7..0x004323DF: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004323d7() {
    __asm {
    L_004323d7:
        lea esp,[esp+force_disp32_zero]
    L_004323de:
        mov edi,edi
    }
}
