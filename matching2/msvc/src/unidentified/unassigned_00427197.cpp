#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00427197..0x0042719F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00427197() {
    __asm {
    L_00427197:
        lea esp,[esp+force_disp32_zero]
    L_0042719e:
        mov edi,edi
    }
}
