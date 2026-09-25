#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00465A60..0x00465A6C: FUN_00465a60
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00465a60_00465a60() {
    __asm {
    L_00465a60:
        push esi
    L_00465a61:
        mov esi,497990h
    L_00465a66:
        call asm_DatArchive_Close_00434d10
    L_00465a6b:
        pop esi
    L_00465a6c:
        ret
    }
}
