#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042F107..0x0042F10F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042f107() {
    __asm {
    L_0042f107:
        lea esp,[esp+force_disp32_zero]
    L_0042f10e:
        mov edi,edi
    }
}
