#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042ACE7..0x0042ACEF: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042ace7() {
    __asm {
    L_0042ace7:
        lea esp,[esp+force_disp32_zero]
    L_0042acee:
        mov edi,edi
    }
}
