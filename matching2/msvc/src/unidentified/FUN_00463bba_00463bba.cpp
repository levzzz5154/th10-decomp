#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00463BBA..0x00463BC3: FUN_00463bba
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00463bba_00463bba() {
    __asm {
    L_00463bba:
        mov edx,477010h
    L_00463bbf:
        jmp asm_cintrindisp2_00463cc0
    }
}
