#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00436A20..0x00436A24: thunk_FUN_00436a30
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_thunk_FUN_00436a30_00436a20() {
    __asm {
    L_00436a20:
        jmp asm_FontCache_FlushRetail_00436a30
    }
}
