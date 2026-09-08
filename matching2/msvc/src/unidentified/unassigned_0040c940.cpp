#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C940..0x0040C94A: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040c940() {
    __asm {
    L_0040c940:
        xor ecx,ecx
    L_0040c942:
        mov dword ptr [eax],ecx
    L_0040c944:
        mov dword ptr [eax+4],ecx
    L_0040c947:
        mov dword ptr [eax+8],ecx
    L_0040c94a:
        ret
    }
}
