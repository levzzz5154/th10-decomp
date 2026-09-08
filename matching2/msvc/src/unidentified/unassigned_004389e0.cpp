#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004389E0..0x004389E3: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004389e0() {
    __asm {
    L_004389e0:
        add eax,8
    L_004389e3:
        ret
    }
}
