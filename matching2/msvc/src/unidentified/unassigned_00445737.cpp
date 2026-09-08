#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00445737..0x0044573F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00445737() {
    __asm {
    L_00445737:
        lea esp,[esp+force_disp32_zero]
    L_0044573e:
        mov edi,edi
    }
}
