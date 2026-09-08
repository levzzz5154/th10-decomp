#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041C85A..0x0041C85F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0041c85a() {
    __asm {
    L_0041c85a:
        lea ebx,[ebx+force_disp32_zero]
    }
}
