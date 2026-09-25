#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00452730..0x004527ED: FUN_00452730
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00452730_00452730() {
    __asm {
    L_00452730:
        xor eax,eax
    L_00452732:
        mov al,byte ptr [esp+8]
    L_00452736:
        push ebx
    L_00452737:
        mov ebx,eax
    L_00452739:
        shl eax,8
    L_0045273c:
        mov edx,dword ptr [esp+8]
    L_00452740:
        test edx,3
    L_00452746:
        je short L_0045275d
    L_00452748:
        mov cl,byte ptr [edx]
    L_0045274a:
        add edx,1
    L_0045274d:
        TH10_CMP_R8_STORE(TH10_R8_CL, TH10_R8_BL)
    L_0045274f:
        TH10_REL8(0x74, 0x0045274f, VA_asm_FUN_0046227b_part_00452720)
    L_00452751:
        test cl,cl
    L_00452753:
        je short L_004527a6
    L_00452755:
        test edx,3
    L_0045275b:
        jne short L_00452748
    L_0045275d:
        or ebx,eax
    L_0045275f:
        push edi
    L_00452760:
        mov eax,ebx
    L_00452762:
        shl ebx,10h
    L_00452765:
        push esi
    L_00452766:
        or ebx,eax
    L_00452768:
        mov ecx,dword ptr [edx]
    L_0045276a:
        mov edi,7EFEFEFFh
    L_0045276f:
        mov eax,ecx
    L_00452771:
        mov esi,edi
    L_00452773:
        xor ecx,ebx
    L_00452775:
        add esi,eax
    L_00452777:
        add edi,ecx
    L_00452779:
        xor ecx,0FFFFFFFFh
    L_0045277c:
        xor eax,0FFFFFFFFh
    L_0045277f:
        xor ecx,edi
    L_00452781:
        xor eax,esi
    L_00452783:
        add edx,4
    L_00452786:
        and ecx,81010100h
    L_0045278c:
        jne short L_004527aa
    L_0045278e:
        and eax,81010100h
    L_00452793:
        je short L_00452768
    L_00452795:
        and eax,1010100h
    L_0045279a:
        jne short L_004527a4
    L_0045279c:
        and esi,80000000h
    L_004527a2:
        jne short L_00452768
    L_004527a4:
        pop esi
    L_004527a5:
        pop edi
    L_004527a6:
        pop ebx
    L_004527a7:
        xor eax,eax
    L_004527a9:
        ret
    L_004527aa:
        mov eax,dword ptr [edx-4]
    L_004527ad:
        TH10_CMP_R8_STORE(TH10_R8_AL, TH10_R8_BL)
    L_004527af:
        je short L_004527e7
    L_004527b1:
        test al,al
    L_004527b3:
        je short L_004527a4
    L_004527b5:
        TH10_CMP_R8_STORE(TH10_R8_AH, TH10_R8_BL)
    L_004527b7:
        je short L_004527e0
    L_004527b9:
        test ah,ah
    L_004527bb:
        je short L_004527a4
    L_004527bd:
        shr eax,10h
    L_004527c0:
        TH10_CMP_R8_STORE(TH10_R8_AL, TH10_R8_BL)
    L_004527c2:
        je short L_004527d9
    L_004527c4:
        test al,al
    L_004527c6:
        je short L_004527a4
    L_004527c8:
        TH10_CMP_R8_STORE(TH10_R8_AH, TH10_R8_BL)
    L_004527ca:
        je short L_004527d2
    L_004527cc:
        test ah,ah
    L_004527ce:
        je short L_004527a4
    L_004527d0:
        jmp short L_00452768
    L_004527d2:
        pop esi
    L_004527d3:
        pop edi
    L_004527d4:
        lea eax,[edx-1]
    L_004527d7:
        pop ebx
    L_004527d8:
        ret
    L_004527d9:
        lea eax,[edx-2]
    L_004527dc:
        pop esi
    L_004527dd:
        pop edi
    L_004527de:
        pop ebx
    L_004527df:
        ret
    L_004527e0:
        lea eax,[edx-3]
    L_004527e3:
        pop esi
    L_004527e4:
        pop edi
    L_004527e5:
        pop ebx
    L_004527e6:
        ret
    L_004527e7:
        lea eax,[edx-4]
    L_004527ea:
        pop esi
    L_004527eb:
        pop edi
    L_004527ec:
        pop ebx
    L_004527ed:
        ret
    }
}
