#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045D746..0x0045DB54: FUN_0045d746
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045d746_0045d746() {
    __asm {
    L_0045d746:
        push ebp
    L_0045d747:
        mov ebp,esp
    L_0045d749:
        sub esp,64h
    L_0045d74c:
        mov eax,dword ptr [data_00473660]
    L_0045d751:
        xor eax,ebp
    L_0045d753:
        mov dword ptr [ebp-4],eax
    L_0045d756:
        mov eax,dword ptr [ebp+8]
    L_0045d759:
        xor ecx,ecx
    L_0045d75b:
        mov dword ptr [ebp-64h],eax
    L_0045d75e:
        mov eax,dword ptr [ebp+0Ch]
    L_0045d761:
        push esi
    L_0045d762:
        mov dword ptr [ebp-60h],eax
    L_0045d765:
        mov eax,dword ptr [ebp+10h]
    L_0045d768:
        lea esi,[ebp-20h]
    L_0045d76b:
        push edi
    L_0045d76c:
        mov dword ptr [ebp-34h],esi
    L_0045d76f:
        mov dword ptr [ebp-50h],ecx
    L_0045d772:
        mov dword ptr [ebp-5Ch],1
    L_0045d779:
        mov dword ptr [ebp-38h],ecx
    L_0045d77c:
        mov dword ptr [ebp-44h],ecx
    L_0045d77f:
        mov dword ptr [ebp-54h],ecx
    L_0045d782:
        mov dword ptr [ebp-58h],ecx
    L_0045d785:
        mov dword ptr [ebp-4Ch],ecx
    L_0045d788:
        mov dword ptr [ebp-3Ch],ecx
    L_0045d78b:
        mov dword ptr [ebp-48h],ecx
    L_0045d78e:
        mov edi,eax
    L_0045d790:
        mov dword ptr [ebp-40h],eax
    L_0045d793:
        mov al,byte ptr [edi]
    L_0045d795:
        cmp al,20h
    L_0045d797:
        je short L_0045d7a5
    L_0045d799:
        cmp al,9
    L_0045d79b:
        je short L_0045d7a5
    L_0045d79d:
        cmp al,0Ah
    L_0045d79f:
        je short L_0045d7a5
    L_0045d7a1:
        cmp al,0Dh
    L_0045d7a3:
        jne short L_0045d7a8
    L_0045d7a5:
        inc edi
    L_0045d7a6:
        jmp short L_0045d793
    L_0045d7a8:
        push ebx
    L_0045d7a9:
        mov bl,byte ptr [edi]
    L_0045d7ab:
        inc edi
    L_0045d7ac:
        cmp ecx,0Bh
    L_0045d7af:
        ja asm_target_0045da26
    L_0045d7b5:
        jmp dword ptr [ecx*4+45DB56h]
    L_0045d7bc:
        cmp bl,31h
    L_0045d7bf:
        jl short L_0045d7cd
    L_0045d7c1:
        cmp bl,39h
    L_0045d7c4:
        jg short L_0045d7cd
    L_0045d7c6:
        push 3
    L_0045d7c8:
        jmp asm_target_0045d9e5
    L_0045d7cd:
        cmp bl,byte ptr [data_00473af4]
    L_0045d7d3:
        jne short L_0045d7dc
    L_0045d7d5:
        push 5
    L_0045d7d7:
        jmp asm_target_0045da1c
    L_0045d7dc:
        movsx eax,bl
    L_0045d7df:
        sub eax,2Bh
    L_0045d7e2:
        push 2
    L_0045d7e4:
        pop ecx
    L_0045d7e5:
        je short L_0045d806
    L_0045d7e7:
        sub eax,ecx
    L_0045d7e9:
        je short L_0045d7fd
    L_0045d7eb:
        sub eax,3
    L_0045d7ee:
        je asm_target_0045d890
    L_0045d7f4:
        mov dword ptr [ebp-34h],esi
    L_0045d7f7:
        dec edi
    L_0045d7f8:
        jmp asm_target_0045d9a2
    L_0045d7fd:
        mov dword ptr [ebp-50h],8000h
    L_0045d804:
        jmp short L_0045d7a9
    L_0045d806:
        and dword ptr [ebp-50h],0
    L_0045d80a:
        jmp short L_0045d7a9
    L_0045d80c:
        xor ecx,ecx
    L_0045d80e:
        inc ecx
    L_0045d80f:
        cmp bl,31h
    L_0045d812:
        mov dword ptr [ebp-44h],ecx
    L_0045d815:
        jl short L_0045d81c
    L_0045d817:
        cmp bl,39h
    L_0045d81a:
        jle short L_0045d7c6
    L_0045d81c:
        cmp bl,byte ptr [data_00473af4]
    L_0045d822:
        jne short L_0045d82b
    L_0045d824:
        push 4
    L_0045d826:
        jmp asm_target_0045da1c
    L_0045d82b:
        cmp bl,2Bh
    L_0045d82e:
        je short L_0045d865
    L_0045d830:
        cmp bl,2Dh
    L_0045d833:
        je short L_0045d865
    L_0045d835:
        cmp bl,30h
    L_0045d838:
        je asm_target_0045d7a9
    L_0045d83e:
        cmp bl,43h
    L_0045d841:
        jle asm_target_0045d99e
    L_0045d847:
        cmp bl,45h
    L_0045d84a:
        jle short L_0045d85e
    L_0045d84c:
        cmp bl,63h
    L_0045d84f:
        jle asm_target_0045d99e
    L_0045d855:
        cmp bl,65h
    L_0045d858:
        jg asm_target_0045d99e
    L_0045d85e:
        push 6
    L_0045d860:
        jmp asm_target_0045da1c
    L_0045d865:
        dec edi
    L_0045d866:
        push 0Bh
    L_0045d868:
        jmp asm_target_0045da1c
    L_0045d86d:
        cmp bl,31h
    L_0045d870:
        jl short L_0045d87b
    L_0045d872:
        cmp bl,39h
    L_0045d875:
        jle asm_target_0045d7c6
    L_0045d87b:
        cmp bl,byte ptr [data_00473af4]
    L_0045d881:
        je asm_target_0045d7d5
    L_0045d887:
        cmp bl,30h
    L_0045d88a:
        jne asm_target_0045d9f1
    L_0045d890:
        xor ecx,ecx
    L_0045d892:
        inc ecx
    L_0045d893:
        jmp asm_target_0045d7a9
    L_0045d898:
        mov dword ptr [ebp-44h],1
    L_0045d89f:
        jmp short L_0045d8b8
    L_0045d8a1:
        cmp dword ptr [ebp-38h],19h
    L_0045d8a5:
        jae short L_0045d8b2
    L_0045d8a7:
        inc dword ptr [ebp-38h]
    L_0045d8aa:
        sub bl,30h
    L_0045d8ad:
        mov byte ptr [esi],bl
    L_0045d8af:
        inc esi
    L_0045d8b0:
        jmp short L_0045d8b5
    L_0045d8b2:
        inc dword ptr [ebp-3Ch]
    L_0045d8b5:
        mov bl,byte ptr [edi]
    L_0045d8b7:
        inc edi
    L_0045d8b8:
        movzx eax,bl
    L_0045d8bb:
        push eax
    L_0045d8bc:
        call asm_isdigit_0045685e
    L_0045d8c1:
        test eax,eax
    L_0045d8c3:
        pop ecx
    L_0045d8c4:
        jne short L_0045d8a1
    L_0045d8c6:
        cmp bl,byte ptr [data_00473af4]
    L_0045d8cc:
        jne short L_0045d914
    L_0045d8ce:
        jmp asm_target_0045d824
    L_0045d8d3:
        xor eax,eax
    L_0045d8d5:
        inc eax
    L_0045d8d6:
        cmp dword ptr [ebp-38h],0
    L_0045d8da:
        mov dword ptr [ebp-44h],eax
    L_0045d8dd:
        mov dword ptr [ebp-54h],eax
    L_0045d8e0:
        jne short L_0045d906
    L_0045d8e2:
        jmp short L_0045d8ea
    L_0045d8e4:
        dec dword ptr [ebp-3Ch]
    L_0045d8e7:
        mov bl,byte ptr [edi]
    L_0045d8e9:
        inc edi
    L_0045d8ea:
        cmp bl,30h
    L_0045d8ed:
        je short L_0045d8e4
    L_0045d8ef:
        jmp short L_0045d906
    L_0045d8f1:
        cmp dword ptr [ebp-38h],19h
    L_0045d8f5:
        jae short L_0045d903
    L_0045d8f7:
        inc dword ptr [ebp-38h]
    L_0045d8fa:
        sub bl,30h
    L_0045d8fd:
        mov byte ptr [esi],bl
    L_0045d8ff:
        inc esi
    L_0045d900:
        dec dword ptr [ebp-3Ch]
    L_0045d903:
        mov bl,byte ptr [edi]
    L_0045d905:
        inc edi
    L_0045d906:
        movzx eax,bl
    L_0045d909:
        push eax
    L_0045d90a:
        call asm_isdigit_0045685e
    L_0045d90f:
        test eax,eax
    L_0045d911:
        pop ecx
    L_0045d912:
        jne short L_0045d8f1
    L_0045d914:
        cmp bl,2Bh
    L_0045d917:
        je asm_target_0045d865
    L_0045d91d:
        cmp bl,2Dh
    L_0045d920:
        je asm_target_0045d865
    L_0045d926:
        jmp asm_target_0045d83e
    L_0045d92b:
        movzx eax,bl
    L_0045d92e:
        push eax
    L_0045d92f:
        mov dword ptr [ebp-54h],1
    L_0045d936:
        call asm_isdigit_0045685e
    L_0045d93b:
        test eax,eax
    L_0045d93d:
        pop ecx
    L_0045d93e:
        je asm_target_0045d9f1
    L_0045d944:
        push 4
    L_0045d946:
        jmp asm_target_0045d9e5
    L_0045d94b:
        cmp bl,31h
    L_0045d94e:
        lea ecx,[edi-2]
    L_0045d951:
        mov dword ptr [ebp-40h],ecx
    L_0045d954:
        jl short L_0045d95f
    L_0045d956:
        cmp bl,39h
    L_0045d959:
        jle asm_target_0045d9e3
    L_0045d95f:
        movsx eax,bl
    L_0045d962:
        sub eax,2Bh
    L_0045d965:
        je asm_target_0045da1a
    L_0045d96b:
        dec eax
    L_0045d96c:
        dec eax
    L_0045d96d:
        je asm_target_0045da0e
    L_0045d973:
        sub eax,3
    L_0045d976:
        jne asm_target_0045da34
    L_0045d97c:
        push 8
    L_0045d97e:
        jmp asm_target_0045da1c
    L_0045d983:
        mov dword ptr [ebp-58h],1
    L_0045d98a:
        jmp short L_0045d98f
    L_0045d98c:
        mov bl,byte ptr [edi]
    L_0045d98e:
        inc edi
    L_0045d98f:
        cmp bl,30h
    L_0045d992:
        je short L_0045d98c
    L_0045d994:
        cmp bl,31h
    L_0045d997:
        jl short L_0045d99e
    L_0045d999:
        cmp bl,39h
    L_0045d99c:
        jle short L_0045d9e3
    L_0045d99e:
        dec edi
    L_0045d99f:
        mov dword ptr [ebp-34h],esi
    L_0045d9a2:
        cmp dword ptr [ebp-44h],0
    L_0045d9a6:
        mov eax,dword ptr [ebp-60h]
    L_0045d9a9:
        mov dword ptr [eax],edi
    L_0045d9ab:
        pop ebx
    L_0045d9ac:
        je asm_target_0045db02
    L_0045d9b2:
        push 18h
    L_0045d9b4:
        pop eax
    L_0045d9b5:
        cmp dword ptr [ebp-38h],eax
    L_0045d9b8:
        jbe short L_0045d9ca
    L_0045d9ba:
        cmp byte ptr [ebp-9],5
    L_0045d9be:
        jl short L_0045d9c3
    L_0045d9c0:
        inc byte ptr [ebp-9]
    L_0045d9c3:
        dec esi
    L_0045d9c4:
        inc dword ptr [ebp-3Ch]
    L_0045d9c7:
        mov dword ptr [ebp-38h],eax
    L_0045d9ca:
        cmp dword ptr [ebp-38h],0
    L_0045d9ce:
        jbe asm_target_0045db29
    L_0045d9d4:
        jmp asm_target_0045da9e
    L_0045d9d9:
        cmp bl,31h
    L_0045d9dc:
        jl short L_0045d9ec
    L_0045d9de:
        cmp bl,39h
    L_0045d9e1:
        jg short L_0045d9ec
    L_0045d9e3:
        push 9
    L_0045d9e5:
        pop ecx
    L_0045d9e6:
        dec edi
    L_0045d9e7:
        jmp asm_target_0045d7a9
    L_0045d9ec:
        cmp bl,30h
    L_0045d9ef:
        je short L_0045d97c
    L_0045d9f1:
        mov edi,dword ptr [ebp-40h]
    L_0045d9f4:
        jmp short L_0045d99f
    L_0045d9f6:
        cmp dword ptr [ebp+20h],0
    L_0045d9fa:
        je short L_0045da22
    L_0045d9fc:
        movsx eax,bl
    L_0045d9ff:
        sub eax,2Bh
    L_0045da02:
        lea ecx,[edi-1]
    L_0045da05:
        mov dword ptr [ebp-40h],ecx
    L_0045da08:
        je short L_0045da1a
    L_0045da0a:
        dec eax
    L_0045da0b:
        dec eax
    L_0045da0c:
        jne short L_0045da34
    L_0045da0e:
        or dword ptr [ebp-5Ch],0FFFFFFFFh
    L_0045da12:
        push 7
    L_0045da14:
        pop ecx
    L_0045da15:
        jmp asm_target_0045d7a9
    L_0045da1a:
        push 7
    L_0045da1c:
        pop ecx
    L_0045da1d:
        jmp asm_target_0045d7a9
    L_0045da22:
        push 0Ah
    L_0045da24:
        pop ecx
    L_0045da25:
        dec edi
    L_0045da26:
        cmp ecx,0Ah
    L_0045da29:
        jne asm_target_0045d7a9
    L_0045da2f:
        jmp asm_target_0045d99f
    L_0045da34:
        mov dword ptr [ebp-34h],esi
    L_0045da37:
        mov edi,ecx
    L_0045da39:
        jmp asm_target_0045d9a2
    L_0045da3e:
        mov dword ptr [ebp-34h],esi
    L_0045da41:
        mov dword ptr [ebp-58h],1
    L_0045da48:
        xor esi,esi
    L_0045da4a:
        jmp short L_0045da61
    L_0045da4c:
        movsx ecx,bl
    L_0045da4f:
        lea eax,[esi+esi*4]
    L_0045da52:
        lea esi,[ecx+eax*2-30h]
    L_0045da56:
        cmp esi,1450h
    L_0045da5c:
        jg short L_0045da71
    L_0045da5e:
        mov bl,byte ptr [edi]
    L_0045da60:
        inc edi
    L_0045da61:
        movzx eax,bl
    L_0045da64:
        push eax
    L_0045da65:
        call asm_isdigit_0045685e
    L_0045da6a:
        test eax,eax
    L_0045da6c:
        pop ecx
    L_0045da6d:
        jne short L_0045da4c
    L_0045da6f:
        jmp short L_0045da76
    L_0045da71:
        mov esi,1451h
    L_0045da76:
        mov dword ptr [ebp-4Ch],esi
    L_0045da79:
        movzx eax,bl
    L_0045da7c:
        jmp short L_0045da84
    L_0045da7e:
        mov al,byte ptr [edi]
    L_0045da80:
        inc edi
    L_0045da81:
        movzx eax,al
    L_0045da84:
        push eax
    L_0045da85:
        call asm_isdigit_0045685e
    L_0045da8a:
        test eax,eax
    L_0045da8c:
        pop ecx
    L_0045da8d:
        jne short L_0045da7e
    L_0045da8f:
        mov esi,dword ptr [ebp-34h]
    L_0045da92:
        dec edi
    L_0045da93:
        jmp asm_target_0045d9a2
    L_0045da98:
        dec dword ptr [ebp-38h]
    L_0045da9b:
        inc dword ptr [ebp-3Ch]
    L_0045da9e:
        dec esi
    L_0045da9f:
        cmp byte ptr [esi],0
    L_0045daa2:
        je short L_0045da98
    L_0045daa4:
        lea eax,[ebp-30h]
    L_0045daa7:
        push eax
    L_0045daa8:
        push dword ptr [ebp-38h]
    L_0045daab:
        lea eax,[ebp-20h]
    L_0045daae:
        push eax
    L_0045daaf:
        call asm_FUN_00460872_00460872
    L_0045dab4:
        mov eax,dword ptr [ebp-4Ch]
    L_0045dab7:
        xor ecx,ecx
    L_0045dab9:
        add esp,0Ch
    L_0045dabc:
        cmp dword ptr [ebp-5Ch],ecx
    L_0045dabf:
        jge short L_0045dac3
    L_0045dac1:
        neg eax
    L_0045dac3:
        add eax,dword ptr [ebp-3Ch]
    L_0045dac6:
        cmp dword ptr [ebp-58h],ecx
    L_0045dac9:
        jne short L_0045dace
    L_0045dacb:
        add eax,dword ptr [ebp+18h]
    L_0045dace:
        cmp dword ptr [ebp-54h],ecx
    L_0045dad1:
        jne short L_0045dad6
    L_0045dad3:
        sub eax,dword ptr [ebp+1Ch]
    L_0045dad6:
        cmp eax,1450h
    L_0045dadb:
        jg short L_0045db0b
    L_0045dadd:
        cmp eax,0FFFFEBB0h
    L_0045dae2:
        jl short L_0045db22
    L_0045dae4:
        push dword ptr [ebp+14h]
    L_0045dae7:
        push eax
    L_0045dae8:
        lea eax,[ebp-30h]
    L_0045daeb:
        push eax
    L_0045daec:
        call asm_FUN_00460b90_00460b90
    L_0045daf1:
        mov ecx,dword ptr [ebp-30h]
    L_0045daf4:
        mov esi,dword ptr [ebp-2Eh]
    L_0045daf7:
        mov edx,dword ptr [ebp-2Ah]
    L_0045dafa:
        mov eax,dword ptr [ebp-26h]
    L_0045dafd:
        add esp,0Ch
    L_0045db00:
        jmp short L_0045db31
    L_0045db02:
        mov dword ptr [ebp-48h],4
    L_0045db09:
        jmp short L_0045db29
    L_0045db0b:
        xor esi,esi
    L_0045db0d:
        mov eax,7FFFh
    L_0045db12:
        mov edx,80000000h
    L_0045db17:
        xor ecx,ecx
    L_0045db19:
        mov dword ptr [ebp-48h],2
    L_0045db20:
        jmp short L_0045db31
    L_0045db22:
        mov dword ptr [ebp-48h],1
    L_0045db29:
        xor ecx,ecx
    L_0045db2b:
        xor eax,eax
    L_0045db2d:
        xor edx,edx
    L_0045db2f:
        xor esi,esi
    L_0045db31:
        mov edi,dword ptr [ebp-64h]
    L_0045db34:
        or eax,dword ptr [ebp-50h]
    L_0045db37:
        mov word ptr [edi],cx
    L_0045db3a:
        mov ecx,dword ptr [ebp-4]
    L_0045db3d:
        mov dword ptr [edi+2],esi
    L_0045db40:
        mov word ptr [edi+0Ah],ax
    L_0045db44:
        mov eax,dword ptr [ebp-48h]
    L_0045db47:
        mov dword ptr [edi+6],edx
    L_0045db4a:
        pop edi
    L_0045db4b:
        xor ecx,ebp
    L_0045db4d:
        pop esi
    L_0045db4e:
        call asm_security_check_cookie_00458ea5
    L_0045db53:
        leave
    L_0045db54:
        ret
    }
}
