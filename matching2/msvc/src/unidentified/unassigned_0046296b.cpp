#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046296B..0x0046296D: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0046296b() {
    __asm {
    L_0046296b:
        xor eax,eax
    L_0046296d:
        inc eax
    }
}
