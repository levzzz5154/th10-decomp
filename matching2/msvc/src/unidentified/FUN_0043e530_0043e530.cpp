#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043E530..0x0043E533: FUN_0043e530
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043e530_0043e530() {
    __asm {
    L_0043e530:
        mov eax,dword ptr [eax+0Ch]
    L_0043e533:
        ret
    }
}
