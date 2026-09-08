#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044D3E0..0x0044D3F2: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044d3e0() {
    __asm {
    L_0044d3e0:
        mov eax,dword ptr [ecx+4]
    L_0044d3e3:
        test eax,eax
    L_0044d3e5:
        je short L_0044d3ec
    L_0044d3e7:
        cmp edx,dword ptr [ecx+10h]
    L_0044d3ea:
        jb short L_0044d3ef
    L_0044d3ec:
        xor eax,eax
    L_0044d3ee:
        ret
    L_0044d3ef:
        mov eax,dword ptr [eax+edx*4]
    L_0044d3f2:
        ret
    }
}
