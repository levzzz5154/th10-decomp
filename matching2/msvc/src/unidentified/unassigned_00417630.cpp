#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00417630..0x00417635: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00417630() {
    __asm {
    L_00417630:
        add eax,2FCh
    L_00417635:
        ret
    }
}
