#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040CDE0..0x0040CDE7: FUN_0040cde0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040cde0_0040cde0() {
    __asm {
    L_0040cde0:
        mov byte ptr [eax+3508h],1
    L_0040cde7:
        ret
    }
}
