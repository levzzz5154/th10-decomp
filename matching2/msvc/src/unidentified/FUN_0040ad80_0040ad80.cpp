#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040AD80..0x0040AD83: FUN_0040ad80
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040ad80_0040ad80() {
    __asm {
    L_0040ad80:
        mov dword ptr [eax+8],ecx
    L_0040ad83:
        ret
    }
}
