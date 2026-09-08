#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042B9B0..0x0042B9B9: FUN_0042b9b0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042b9b0_0042b9b0() {
    __asm {
    L_0042b9b0:
        push edi
    L_0042b9b1:
        mov edi,ecx
    L_0042b9b3:
        call asm_FUN_0042b780_0042b780
    L_0042b9b8:
        pop edi
    L_0042b9b9:
        ret
    }
}
