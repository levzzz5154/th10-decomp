#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043CF57..0x0043CF5F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0043cf57() {
    __asm {
    L_0043cf57:
        lea esp,[esp+force_disp32_zero]
    L_0043cf5e:
        mov edi,edi
    }
}
