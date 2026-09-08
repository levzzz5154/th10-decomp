#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00409220..0x00409229: FUN_00409220
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00409220_00409220() {
    __asm {
    L_00409220:
        push edi
    L_00409221:
        mov edi,ecx
    L_00409223:
        call asm_FUN_00408d60_00408d60
    L_00409228:
        pop edi
    L_00409229:
        ret
    }
}
