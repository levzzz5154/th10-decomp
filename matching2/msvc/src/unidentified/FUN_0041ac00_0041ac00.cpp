#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041AC00..0x0041AC03: FUN_0041ac00
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041ac00_0041ac00() {
    __asm {
    L_0041ac00:
        mov dword ptr [eax+34h],ecx
    L_0041ac03:
        ret
    }
}
