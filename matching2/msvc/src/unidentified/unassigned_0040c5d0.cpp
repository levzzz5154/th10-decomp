#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C5D0..0x0040C5DE: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040c5d0() {
    __asm {
    L_0040c5d0:
        xor ecx,ecx
    L_0040c5d2:
        mov dword ptr [eax+1000h],ecx
    L_0040c5d8:
        mov dword ptr [eax+1004h],ecx
    L_0040c5de:
        ret
    }
}
