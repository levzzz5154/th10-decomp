#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042C590..0x0042C599: FUN_0042c590
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042c590_0042c590() {
    __asm {
    L_0042c590:
        push edi
    L_0042c591:
        mov edi,ecx
    L_0042c593:
        call asm_FUN_0042c360_0042c360
    L_0042c598:
        pop edi
    L_0042c599:
        ret
    }
}
