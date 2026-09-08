#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00401CC0..0x00401CC6: FUN_00401cc0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00401cc0_00401cc0() {
    __asm {
    L_00401cc0:
        mov dword ptr [eax+2FCh],ecx
    L_00401cc6:
        ret
    }
}
