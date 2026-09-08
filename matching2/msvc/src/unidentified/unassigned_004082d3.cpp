#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004082D3..0x004082DF: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004082d3() {
    __asm {
    L_004082d3:
        lea esp,[esp+force_disp32_zero]
    L_004082da:
        lea ebx,[ebx+force_disp32_zero]
    }
}
