#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044C6D0..0x0044C6DB: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044c6d0() {
    __asm {
    L_0044c6d0:
        mov dword ptr [eax+8],ecx
    L_0044c6d3:
        xor ecx,ecx
    L_0044c6d5:
        mov dword ptr [eax+0Ch],ecx
    L_0044c6d8:
        mov dword ptr [eax+10h],ecx
    L_0044c6db:
        ret
    }
}
