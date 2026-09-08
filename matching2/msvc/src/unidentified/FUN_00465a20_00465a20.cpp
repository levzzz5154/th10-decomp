#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00465A20..0x00465A2C: FUN_00465a20
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00465a20_00465a20() {
    __asm {
    L_00465a20:
        push esi
    L_00465a21:
        mov esi,474CB0h
    L_00465a26:
        call asm_FontCache_FlushRetail_00436a30
    L_00465a2b:
        pop esi
    L_00465a2c:
        ret
    }
}
