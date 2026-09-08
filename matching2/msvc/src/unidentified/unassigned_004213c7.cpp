#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004213C7..0x004213CF: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004213c7() {
    __asm {
    L_004213c7:
        lea esp,[esp+force_disp32_zero]
    L_004213ce:
        mov edi,edi
    }
}
