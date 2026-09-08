#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044C6B0..0x0044C6C1: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044c6b0() {
    __asm {
    L_0044c6b0:
        test eax,eax
    L_0044c6b2:
        je short L_0044c6bf
    L_0044c6b4:
        cmp dword ptr [eax],ecx
    L_0044c6b6:
        je short L_0044c6c1
    L_0044c6b8:
        mov eax,dword ptr [eax+4]
    L_0044c6bb:
        test eax,eax
    L_0044c6bd:
        jne short L_0044c6b4
    L_0044c6bf:
        xor eax,eax
    L_0044c6c1:
        ret
    }
}
