#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00415817..0x0041581F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00415817() {
    __asm {
    L_00415817:
        lea esp,[esp+force_disp32_zero]
    L_0041581e:
        mov edi,edi
    }
}
