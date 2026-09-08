#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004014D0..0x004014EF: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004014d0() {
    __asm {
    L_004014d0:
        xor ecx,ecx
    L_004014d2:
        mov dword ptr [eax+896Ch],ecx
    L_004014d8:
        mov dword ptr [eax+8970h],ecx
    L_004014de:
        inc dword ptr [eax+8990h]
    L_004014e4:
        mov eax,1
    L_004014e9:
        ret
    L_004014ea:
        int 3
    L_004014eb:
        int 3
    L_004014ec:
        int 3
    L_004014ed:
        int 3
    L_004014ee:
        int 3
    L_004014ef:
        int 3
    }
}
