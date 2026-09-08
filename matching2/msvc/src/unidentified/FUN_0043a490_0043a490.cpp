#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043A490..0x0043A49D: FUN_0043a490
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043a490_0043a490() {
    __asm {
    L_0043a490:
        mov dword ptr [eax],0
    L_0043a496:
        mov dword ptr [eax+4],0
    L_0043a49d:
        ret
    }
}
