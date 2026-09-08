#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00442F30..0x00442F4C: FUN_00442f30
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00442f30_00442f30() {
    __asm {
    L_00442f30:
        lea ecx,[eax+3ADACCh]
    L_00442f36:
        mov dword ptr [eax+3ADAC8h],0
    L_00442f40:
        mov dword ptr [eax+72DACCh],ecx
    L_00442f46:
        mov dword ptr [eax+72DAD0h],ecx
    L_00442f4c:
        ret
    }
}
