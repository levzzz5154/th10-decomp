#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00434C20..0x00434C29: ?DatArchive_Reset@@
// Naked body preserves the retail register/stack ABI.

// 0x00434C20..0x00434C29: ?DatArchive_Reset@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_DatArchive_Reset_00434c20() {
    __asm {
    L_00434c20:
        push esi
    L_00434c21:
        mov esi,ecx
    L_00434c23:
        call asm_DatArchive_Close_00434d10
    L_00434c28:
        pop esi
    L_00434c29:
        ret
    }
}
