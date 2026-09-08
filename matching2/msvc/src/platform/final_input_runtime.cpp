#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044A5F0..0x0044A941: FUN_0044a5f0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0044a5f0_0044a5f0() {
    __asm {
    L_0044a5f0:
        sub esp,108h
    L_0044a5f6:
        mov eax,dword ptr [data_00473660]
    L_0044a5fb:
        xor eax,esp
    L_0044a5fd:
        push ebx
    L_0044a5fe:
        push esi
    L_0044a5ff:
        mov ebx,ecx
    L_0044a601:
        mov esi,ebx
    L_0044a603:
        imul esi,6Ah
    L_0044a606:
        mov dword ptr [esp+10Ch],eax
    L_0044a60d:
        mov eax,dword ptr [data_004924fc]
    L_0044a612:
        push edi
    L_0044a613:
        xor edi,edi
    L_0044a615:
        add esi,474E30h
    L_0044a61b:
        test eax,eax
    L_0044a61d:
        je asm_target_0044a8b3
    L_0044a623:
        mov eax,dword ptr [data_00491ff4]
    L_0044a628:
        test ah,2
    L_0044a62b:
        jne asm_target_0044a754
    L_0044a631:
        lea eax,[esp+10h]
    L_0044a635:
        push eax
    L_0044a636:
        call dword ptr [data_00466208]
    L_0044a63c:
        mov al,byte ptr [esp+20h]
    L_0044a640:
        mov cl,byte ptr [esp+68h]
    L_0044a644:
        mov dl,byte ptr [esp+6Ah]
    L_0044a648:
        and cl,0BFh
    L_0044a64b:
        shr dl,1
    L_0044a64d:
        or cl,dl
    L_0044a64f:
        mov dl,byte ptr [esp+2Bh]
    L_0044a653:
        shr cl,1
    L_0044a655:
        and al,9Fh
    L_0044a657:
        or cl,al
    L_0044a659:
        mov al,byte ptr [esp+78h]
    L_0044a65d:
        shr cl,1
    L_0044a65f:
        and dl,8Fh
    L_0044a662:
        or cl,dl
    L_0044a664:
        or al,byte ptr [esp+36h]
    L_0044a668:
        mov dl,byte ptr [esp+72h]
    L_0044a66c:
        shr cl,1
    L_0044a66e:
        and al,87h
    L_0044a670:
        or cl,al
    L_0044a672:
        or dl,byte ptr [esp+38h]
    L_0044a676:
        mov al,byte ptr [esp+74h]
    L_0044a67a:
        shr cl,1
    L_0044a67c:
        and dl,83h
    L_0044a67f:
        or cl,dl
    L_0044a681:
        or al,byte ptr [esp+35h]
    L_0044a685:
        mov dl,byte ptr [esp+76h]
    L_0044a689:
        shr cl,1
    L_0044a68b:
        and al,81h
    L_0044a68d:
        or cl,al
    L_0044a68f:
        or dl,byte ptr [esp+37h]
    L_0044a693:
        mov al,byte ptr [esp+62h]
    L_0044a697:
        shr cl,1
    L_0044a699:
        and dl,80h
    L_0044a69c:
        or cl,dl
    L_0044a69e:
        mov dl,byte ptr [esp+54h]
    L_0044a6a2:
        movzx di,cl
    L_0044a6a6:
        and al,80h
    L_0044a6a8:
        and dl,80h
    L_0044a6ab:
        movzx cx,al
    L_0044a6af:
        movzx ax,dl
    L_0044a6b3:
        mov dl,byte ptr [esp+1Dh]
    L_0044a6b7:
        and dl,80h
    L_0044a6ba:
        shl ecx,1
    L_0044a6bc:
        or ecx,eax
    L_0044a6be:
        movzx ax,dl
    L_0044a6c2:
        mov dl,byte ptr [esp+60h]
    L_0044a6c6:
        shl ecx,1
    L_0044a6c8:
        or ecx,eax
    L_0044a6ca:
        or dl,byte ptr [esp+34h]
    L_0044a6ce:
        and dl,80h
    L_0044a6d1:
        movzx ax,dl
    L_0044a6d5:
        mov dl,byte ptr [esp+63h]
    L_0044a6d9:
        shl ecx,1
    L_0044a6db:
        and dl,80h
    L_0044a6de:
        or ecx,eax
    L_0044a6e0:
        movzx ax,dl
    L_0044a6e4:
        mov dl,byte ptr [esp+61h]
    L_0044a6e8:
        shl ecx,1
    L_0044a6ea:
        and dl,80h
    L_0044a6ed:
        or ecx,eax
    L_0044a6ef:
        movzx ax,dl
    L_0044a6f3:
        mov dl,byte ptr [esp+21h]
    L_0044a6f7:
        shl ecx,1
    L_0044a6f9:
        and dl,80h
    L_0044a6fc:
        or ecx,eax
    L_0044a6fe:
        movzx ax,dl
    L_0044a702:
        shl ecx,1
    L_0044a704:
        or ecx,eax
    L_0044a706:
        shl ecx,1
    L_0044a708:
        or edi,ecx
    L_0044a70a:
        mov cl,byte ptr [esp+73h]
    L_0044a70e:
        and cl,80h
    L_0044a711:
        neg cl
    L_0044a713:
        mov dl,byte ptr [esp+79h]
    L_0044a717:
        mov al,byte ptr [esp+71h]
    L_0044a71b:
        sbb ecx,ecx
    L_0044a71d:
        and ecx,0A0h
    L_0044a723:
        or edi,ecx
    L_0044a725:
        mov cl,byte ptr [esp+77h]
    L_0044a729:
        and dl,80h
    L_0044a72c:
        neg dl
    L_0044a72e:
        sbb edx,edx
    L_0044a730:
        and edx,90h
    L_0044a736:
        and al,80h
    L_0044a738:
        or edi,edx
    L_0044a73a:
        neg al
    L_0044a73c:
        sbb eax,eax
    L_0044a73e:
        and eax,60h
    L_0044a741:
        and cl,80h
    L_0044a744:
        or edi,eax
    L_0044a746:
        neg cl
    L_0044a748:
        sbb ecx,ecx
    L_0044a74a:
        and ecx,50h
    L_0044a74d:
        or edi,ecx
    L_0044a74f:
        jmp asm_target_0044a8b3
    L_0044a754:
        mov eax,dword ptr [data_00491c38]
    L_0044a759:
        mov edx,dword ptr [eax]
    L_0044a75b:
        lea ecx,[esp+10h]
    L_0044a75f:
        push ecx
    L_0044a760:
        push 100h
    L_0044a765:
        push eax
    L_0044a766:
        call dword ptr [edx+24h]
    L_0044a769:
        xor edi,edi
    L_0044a76b:
        cmp eax,8007001Eh
    L_0044a770:
        jne short L_0044a782
    L_0044a772:
        mov eax,dword ptr [data_00491c38]
    L_0044a777:
        mov edx,dword ptr [eax]
    L_0044a779:
        push eax
    L_0044a77a:
        call dword ptr [edx+1Ch]
    L_0044a77d:
        jmp asm_target_0044a8b3
    L_0044a782:
        test eax,eax
    L_0044a784:
        je short L_0044a796
    L_0044a786:
        mov eax,dword ptr [data_00491c38]
    L_0044a78b:
        mov ecx,dword ptr [eax]
    L_0044a78d:
        push eax
    L_0044a78e:
        call dword ptr [ecx+1Ch]
    L_0044a791:
        jmp asm_target_0044a8b3
    L_0044a796:
        mov cl,byte ptr [esp+3Ah]
    L_0044a79a:
        mov dl,byte ptr [esp+3Dh]
    L_0044a79e:
        mov al,byte ptr [esp+3Ch]
    L_0044a7a2:
        and dl,0BFh
    L_0044a7a5:
        shr al,1
    L_0044a7a7:
        or dl,al
    L_0044a7a9:
        shr dl,1
    L_0044a7ab:
        mov al,byte ptr [esp+11h]
    L_0044a7af:
        and cl,9Fh
    L_0044a7b2:
        or dl,cl
    L_0044a7b4:
        mov cl,byte ptr [esp+58h]
    L_0044a7b8:
        shr dl,1
    L_0044a7ba:
        and al,8Fh
    L_0044a7bc:
        or dl,al
    L_0044a7be:
        or cl,byte ptr [esp+0D8h]
    L_0044a7c5:
        mov al,byte ptr [esp+0E0h]
    L_0044a7cc:
        shr dl,1
    L_0044a7ce:
        and cl,87h
    L_0044a7d1:
        or dl,cl
    L_0044a7d3:
        or al,byte ptr [esp+60h]
    L_0044a7d7:
        mov cl,byte ptr [esp+5Bh]
    L_0044a7db:
        shr dl,1
    L_0044a7dd:
        and al,83h
    L_0044a7df:
        or dl,al
    L_0044a7e1:
        or cl,byte ptr [esp+0DBh]
    L_0044a7e8:
        mov al,byte ptr [esp+5Dh]
    L_0044a7ec:
        shr dl,1
    L_0044a7ee:
        and cl,81h
    L_0044a7f1:
        or dl,cl
    L_0044a7f3:
        or al,byte ptr [esp+0DDh]
    L_0044a7fa:
        mov cl,byte ptr [esp+23h]
    L_0044a7fe:
        shr dl,1
    L_0044a800:
        and al,80h
    L_0044a802:
        or dl,al
    L_0044a804:
        mov al,byte ptr [esp+30h]
    L_0044a808:
        movzx di,dl
    L_0044a80c:
        and cl,80h
    L_0044a80f:
        and al,80h
    L_0044a811:
        movzx dx,cl
    L_0044a815:
        movzx cx,al
    L_0044a819:
        mov al,byte ptr [esp+2Ch]
    L_0044a81d:
        and al,80h
    L_0044a81f:
        shl edx,1
    L_0044a821:
        or edx,ecx
    L_0044a823:
        movzx cx,al
    L_0044a827:
        mov al,byte ptr [esp+29h]
    L_0044a82b:
        shl edx,1
    L_0044a82d:
        or edx,ecx
    L_0044a82f:
        or al,byte ptr [esp+0D7h]
    L_0044a836:
        and al,80h
    L_0044a838:
        movzx cx,al
    L_0044a83c:
        mov al,byte ptr [esp+2Fh]
    L_0044a840:
        shl edx,1
    L_0044a842:
        and al,80h
    L_0044a844:
        or edx,ecx
    L_0044a846:
        movzx cx,al
    L_0044a84a:
        mov al,byte ptr [esp+20h]
    L_0044a84e:
        shl edx,1
    L_0044a850:
        and al,80h
    L_0044a852:
        or edx,ecx
    L_0044a854:
        movzx cx,al
    L_0044a858:
        mov al,byte ptr [esp+2Dh]
    L_0044a85c:
        shl edx,1
    L_0044a85e:
        and al,80h
    L_0044a860:
        or edx,ecx
    L_0044a862:
        movzx cx,al
    L_0044a866:
        shl edx,1
    L_0044a868:
        or edx,ecx
    L_0044a86a:
        shl edx,1
    L_0044a86c:
        or edi,edx
    L_0044a86e:
        mov dl,byte ptr [esp+59h]
    L_0044a872:
        and dl,80h
    L_0044a875:
        neg dl
    L_0044a877:
        sbb edx,edx
    L_0044a879:
        and edx,90h
    L_0044a87f:
        or edi,edx
    L_0044a881:
        mov al,byte ptr [esp+5Fh]
    L_0044a885:
        mov cl,byte ptr [esp+57h]
    L_0044a889:
        mov dl,byte ptr [esp+61h]
    L_0044a88d:
        and al,80h
    L_0044a88f:
        neg al
    L_0044a891:
        sbb eax,eax
    L_0044a893:
        and eax,60h
    L_0044a896:
        and cl,80h
    L_0044a899:
        or edi,eax
    L_0044a89b:
        neg cl
    L_0044a89d:
        sbb ecx,ecx
    L_0044a89f:
        and ecx,50h
    L_0044a8a2:
        and dl,80h
    L_0044a8a5:
        or edi,ecx
    L_0044a8a7:
        neg dl
    L_0044a8a9:
        sbb edx,edx
    L_0044a8ab:
        and edx,0A0h
    L_0044a8b1:
        or edi,edx
    L_0044a8b3:
        push 0
    L_0044a8b5:
        push ebx
    L_0044a8b6:
        mov ecx,edi
    L_0044a8b8:
        call asm_FUN_0044a190_0044a190
    L_0044a8bd:
        mov cx,word ptr [esi]
    L_0044a8c0:
        mov ebx,1
    L_0044a8c5:
        mov word ptr [esi+2],cx
    L_0044a8c9:
        mov word ptr [esi],ax
    L_0044a8cc:
        mov edx,ebx
    L_0044a8ce:
        mov dword ptr [esp+0Ch],eax
    L_0044a8d2:
        mov word ptr [esi+4],0
    L_0044a8d8:
        lea ecx,[esi+0Ah]
    L_0044a8db:
        mov edi,10h
    L_0044a8e0:
        test byte ptr [esp+0Ch],bl
    L_0044a8e4:
        je short L_0044a8fa
    L_0044a8e6:
        inc word ptr [ecx]
    L_0044a8e9:
        cmp word ptr [ecx],1Ah
    L_0044a8ed:
        jb short L_0044a8ff
    L_0044a8ef:
        or word ptr [esi+4],dx
    L_0044a8f3:
        TH10_ADD_M16_IMM16(TH10_R32_ECX, 0xfff8)
    L_0044a8f8:
        jmp short L_0044a8ff
    L_0044a8fa:
        mov word ptr [ecx],0
    L_0044a8ff:
        shr word ptr [esp+0Ch],1
    L_0044a904:
        add ecx,2
    L_0044a907:
        shl edx,1
    L_0044a909:
        dec edi
    L_0044a90a:
        jne short L_0044a8e0
    L_0044a90c:
        xor ecx,ecx
    L_0044a90e:
        mov cx,word ptr [esi]
    L_0044a911:
        xor edx,edx
    L_0044a913:
        mov dx,word ptr [esi+2]
    L_0044a917:
        xor dx,cx
    L_0044a91a:
        mov edi,edx
    L_0044a91c:
        and edi,ecx
    L_0044a91e:
        not ecx
    L_0044a920:
        and ecx,edx
    L_0044a922:
        mov word ptr [esi+6],di
    L_0044a926:
        mov word ptr [esi+8],cx
    L_0044a92a:
        mov ecx,dword ptr [esp+110h]
    L_0044a931:
        pop edi
    L_0044a932:
        pop esi
    L_0044a933:
        pop ebx
    L_0044a934:
        xor ecx,esp
    L_0044a936:
        call asm_security_check_cookie_00458ea5
    L_0044a93b:
        add esp,108h
    L_0044a941:
        ret
    }
}
