#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004577A2..0x004577CD: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004577a2() {
    __asm {
    L_004577a2:
        mov ecx,dword ptr [data_00473654]
    L_004577a8:
        mov eax,edx
    L_004577aa:
        push edi
    L_004577ab:
        cmp dword ptr [eax],esi
    L_004577ad:
        je short L_004577bc
    L_004577af:
        lea edi,[ecx+ecx*2]
    L_004577b2:
        add eax,0Ch
    L_004577b5:
        lea edi,[edx+edi*4]
    L_004577b8:
        cmp eax,edi
    L_004577ba:
        jb short L_004577ab
    L_004577bc:
        lea ecx,[ecx+ecx*2]
    L_004577bf:
        lea ecx,[edx+ecx*4]
    L_004577c2:
        cmp eax,ecx
    L_004577c4:
        pop edi
    L_004577c5:
        jae short L_004577cb
    L_004577c7:
        cmp dword ptr [eax],esi
    L_004577c9:
        je short L_004577cd
    L_004577cb:
        xor eax,eax
    L_004577cd:
        ret
    }
}
