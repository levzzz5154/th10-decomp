#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421387..0x0042138F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00421387() {
    __asm {
    L_00421387:
        lea esp,[esp+force_disp32_zero]
    L_0042138e:
        mov edi,edi
    }
}
