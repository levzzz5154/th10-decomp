#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00422917..0x0042291F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00422917() {
    __asm {
    L_00422917:
        lea esp,[esp+force_disp32_zero]
    L_0042291e:
        mov edi,edi
    }
}
