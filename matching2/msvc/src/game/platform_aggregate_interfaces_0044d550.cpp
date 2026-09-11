#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x0044D550..0x0044D5A1: ?Platform_AggregateInterfaces@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Platform_AggregateInterfaces_0044d550() {
    __asm {
    L_0044d550:
        mov eax,dword ptr [edi+4]
    L_0044d553:
        test eax,eax
    L_0044d555:
        jne short L_0044d55d
    L_0044d557:
        mov eax,800401F0h
    L_0044d55c:
        ret
    L_0044d55d:
        mov eax,dword ptr [edi+10h]
    L_0044d560:
        push ebx
    L_0044d561:
        push esi
    L_0044d562:
        xor ebx,ebx
    L_0044d564:
        xor esi,esi
    L_0044d566:
        test eax,eax
    L_0044d568:
        mov dword ptr [edi+30h],ebx
    L_0044d56b:
        jbe short L_0044d596
    L_0044d56d:
        TH10_NOP_LEA_ECX_DISP8()
    L_0044d570:
        mov eax,dword ptr [edi+4]
    L_0044d573:
        mov eax,dword ptr [eax+esi*4]
    L_0044d576:
        mov ecx,dword ptr [eax]
    L_0044d578:
        push eax
    L_0044d579:
        call dword ptr [ecx+48h]
    L_0044d57c:
        mov edx,dword ptr [edi+4]
    L_0044d57f:
        or ebx,eax
    L_0044d581:
        mov eax,dword ptr [edx+esi*4]
    L_0044d584:
        mov ecx,dword ptr [eax]
    L_0044d586:
        push 0
    L_0044d588:
        push eax
    L_0044d589:
        call dword ptr [ecx+34h]
    L_0044d58c:
        or ebx,eax
    L_0044d58e:
        mov eax,dword ptr [edi+10h]
    L_0044d591:
        inc esi
    L_0044d592:
        cmp esi,eax
    L_0044d594:
        jb short L_0044d570
    L_0044d596:
        pop esi
    L_0044d597:
        mov eax,ebx
    L_0044d599:
        mov dword ptr [edi+1Ch],0
    L_0044d5a0:
        pop ebx
    L_0044d5a1:
        ret
    }
}
