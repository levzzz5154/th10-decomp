#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044D640..0x0044D697: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044d640() {
    __asm {
    L_0044d640:
        push ecx
    L_0044d641:
        mov eax,dword ptr [edi+4]
    L_0044d644:
        push ebx
    L_0044d645:
        xor ebx,ebx
    L_0044d647:
        test eax,eax
    L_0044d649:
        jne short L_0044d650
    L_0044d64b:
        xor eax,eax
    L_0044d64d:
        pop ebx
    L_0044d64e:
        pop ecx
    L_0044d64f:
        ret
    L_0044d650:
        mov eax,dword ptr [edi+10h]
    L_0044d653:
        push esi
    L_0044d654:
        xor esi,esi
    L_0044d656:
        test eax,eax
    L_0044d658:
        jbe short L_0044d692
    L_0044d65a:
        lea ebx,[ebx+force_disp32_zero]
    L_0044d660:
        mov eax,dword ptr [edi+4]
    L_0044d663:
        cmp dword ptr [eax+esi*4],0
    L_0044d667:
        je short L_0044d68a
    L_0044d669:
        mov ecx,eax
    L_0044d66b:
        mov dword ptr [esp+8],0
    L_0044d673:
        mov eax,dword ptr [ecx+esi*4]
    L_0044d676:
        mov edx,dword ptr [eax]
    L_0044d678:
        lea ecx,[esp+8]
    L_0044d67c:
        push ecx
    L_0044d67d:
        push eax
    L_0044d67e:
        call dword ptr [edx+24h]
    L_0044d681:
        mov edx,dword ptr [esp+8]
    L_0044d685:
        and edx,1
    L_0044d688:
        or ebx,edx
    L_0044d68a:
        mov eax,dword ptr [edi+10h]
    L_0044d68d:
        inc esi
    L_0044d68e:
        cmp esi,eax
    L_0044d690:
        jb short L_0044d660
    L_0044d692:
        pop esi
    L_0044d693:
        mov eax,ebx
    L_0044d695:
        pop ebx
    L_0044d696:
        pop ecx
    L_0044d697:
        ret
    }
}
