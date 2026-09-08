#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004411C3..0x004411CF: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004411c3() {
    __asm {
    L_004411c3:
        lea esp,[esp+force_disp32_zero]
    L_004411ca:
        lea ebx,[ebx+force_disp32_zero]
    }
}
