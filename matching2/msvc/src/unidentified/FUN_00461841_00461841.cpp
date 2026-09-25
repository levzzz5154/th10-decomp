#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00461841..0x00461ADC: FUN_00461841
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00461841_00461841() {
    __asm {
    L_00461841:
        push ebp
    L_00461842:
        mov ebp,esp
    L_00461844:
        sub esp,34h
    L_00461847:
        mov eax,dword ptr [data_00473660]
    L_0046184c:
        push ebx
    L_0046184d:
        mov ebx,dword ptr [ebp+1Ch]
    L_00461850:
        push esi
    L_00461851:
        push edi
    L_00461852:
        lea esi,[ebp+8]
    L_00461855:
        lea edi,[ebp-28h]
    L_00461858:
        movsd
    L_00461859:
        movsd
    L_0046185a:
        xor eax,ebp
    L_0046185c:
        mov dword ptr [ebp-4],eax
    L_0046185f:
        movsw
    L_00461861:
        mov eax,dword ptr [ebp-20h]
    L_00461864:
        mov ecx,eax
    L_00461866:
        mov esi,7FFFh
    L_0046186b:
        and ecx,8000h
    L_00461871:
        and eax,esi
    L_00461873:
        test cx,cx
    L_00461876:
        mov byte ptr [ebp-1Ch],0CCh
    L_0046187a:
        mov byte ptr [ebp-1Bh],0CCh
    L_0046187e:
        mov byte ptr [ebp-1Ah],0CCh
    L_00461882:
        mov byte ptr [ebp-19h],0CCh
    L_00461886:
        mov byte ptr [ebp-18h],0CCh
    L_0046188a:
        mov byte ptr [ebp-17h],0CCh
    L_0046188e:
        mov byte ptr [ebp-16h],0CCh
    L_00461892:
        mov byte ptr [ebp-15h],0CCh
    L_00461896:
        mov byte ptr [ebp-14h],0CCh
    L_0046189a:
        mov byte ptr [ebp-13h],0CCh
    L_0046189e:
        mov byte ptr [ebp-12h],0FBh
    L_004618a2:
        mov byte ptr [ebp-11h],3Fh
    L_004618a6:
        mov dword ptr [ebp-30h],1
    L_004618ad:
        mov edx,eax
    L_004618af:
        je short L_004618b7
    L_004618b1:
        mov byte ptr [ebx+2],2Dh
    L_004618b5:
        jmp short L_004618bb
    L_004618b7:
        mov byte ptr [ebx+2],20h
    L_004618bb:
        test dx,dx
    L_004618be:
        mov edi,dword ptr [ebp-24h]
    L_004618c1:
        jne short L_004618d0
    L_004618c3:
        test edi,edi
    L_004618c5:
        jne short L_004618d0
    L_004618c7:
        cmp dword ptr [ebp-28h],edi
    L_004618ca:
        je asm_target_004619c3
    L_004618d0:
        cmp dx,si
    L_004618d3:
        jne short L_0046194d
    L_004618d5:
        mov eax,80000000h
    L_004618da:
        cmp edi,eax
    L_004618dc:
        mov word ptr [ebx],1
    L_004618e1:
        jne short L_004618e9
    L_004618e3:
        cmp dword ptr [ebp-28h],0
    L_004618e7:
        je short L_004618f8
    L_004618e9:
        test edi,40000000h
    L_004618ef:
        jne short L_004618f8
    L_004618f1:
        push 46C9B4h
    L_004618f6:
        jmp short L_0046193e
    L_004618f8:
        test cx,cx
    L_004618fb:
        je short L_00461912
    L_004618fd:
        cmp edi,0C0000000h
    L_00461903:
        jne short L_00461912
    L_00461905:
        cmp dword ptr [ebp-28h],0
    L_00461909:
        jne short L_00461939
    L_0046190b:
        push 46C9ACh
    L_00461910:
        jmp short L_00461921
    L_00461912:
        cmp edi,eax
    L_00461914:
        jne short L_00461939
    L_00461916:
        cmp dword ptr [ebp-28h],0
    L_0046191a:
        jne short L_00461939
    L_0046191c:
        push 46C9A4h
    L_00461921:
        lea eax,[ebx+4]
    L_00461924:
        push eax
    L_00461925:
        call asm_FUN_0045bd80_0045bd80
    L_0046192a:
        mov byte ptr [ebx+3],5
    L_0046192e:
        and dword ptr [ebp-30h],0
    L_00461932:
        pop ecx
    L_00461933:
        pop ecx
    L_00461934:
        jmp asm_target_00461aa5
    L_00461939:
        push 46C99Ch
    L_0046193e:
        lea eax,[ebx+4]
    L_00461941:
        push eax
    L_00461942:
        call asm_FUN_0045bd80_0045bd80
    L_00461947:
        mov byte ptr [ebx+3],6
    L_0046194b:
        jmp short L_0046192e
    L_0046194d:
        movzx eax,dx
    L_00461950:
        mov esi,eax
    L_00461952:
        imul eax,4D10h
    L_00461958:
        and word ptr [ebp-10h],0
    L_0046195d:
        mov ecx,edi
    L_0046195f:
        shr ecx,18h
    L_00461962:
        shr esi,8
    L_00461965:
        lea ecx,[esi+ecx*2]
    L_00461968:
        imul ecx,4Dh
    L_0046196b:
        lea esi,[ecx+eax-134312F4h]
    L_00461972:
        mov eax,dword ptr [ebp-28h]
    L_00461975:
        mov dword ptr [ebp-0Eh],eax
    L_00461978:
        sar esi,10h
    L_0046197b:
        movsx eax,si
    L_0046197e:
        neg eax
    L_00461980:
        push 1
    L_00461982:
        push eax
    L_00461983:
        lea eax,[ebp-10h]
    L_00461986:
        push eax
    L_00461987:
        mov word ptr [ebp-6],dx
    L_0046198b:
        mov dword ptr [ebp-0Ah],edi
    L_0046198e:
        call asm_FUN_00460b90_00460b90
    L_00461993:
        add esp,0Ch
    L_00461996:
        cmp word ptr [ebp-6],3FFFh
    L_0046199c:
        jb short L_004619ae
    L_0046199e:
        lea eax,[ebp-1Ch]
    L_004619a1:
        push eax
    L_004619a2:
        lea eax,[ebp-10h]
    L_004619a5:
        push eax
    L_004619a6:
        inc esi
    L_004619a7:
        call asm_FUN_0046095a_0046095a
    L_004619ac:
        pop ecx
    L_004619ad:
        pop ecx
    L_004619ae:
        test byte ptr [ebp+18h],1
    L_004619b2:
        mov edi,dword ptr [ebp+14h]
    L_004619b5:
        mov word ptr [ebx],si
    L_004619b8:
        je short L_004619cc
    L_004619ba:
        movsx eax,si
    L_004619bd:
        add edi,eax
    L_004619bf:
        test edi,edi
    L_004619c1:
        jg short L_004619cc
    L_004619c3:
        mov byte ptr [ebx+4],30h
    L_004619c7:
        jmp asm_target_00461ac8
    L_004619cc:
        cmp edi,15h
    L_004619cf:
        jle short L_004619d4
    L_004619d1:
        push 15h
    L_004619d3:
        pop edi
    L_004619d4:
        movzx esi,word ptr [ebp-6]
    L_004619d8:
        sub esi,3FFEh
    L_004619de:
        and word ptr [ebp-6],0
    L_004619e3:
        mov dword ptr [ebp-2Ch],8
    L_004619ea:
        lea eax,[ebp-10h]
    L_004619ed:
        push eax
    L_004619ee:
        call asm_shl_12_00460817
    L_004619f3:
        dec dword ptr [ebp-2Ch]
    L_004619f6:
        pop ecx
    L_004619f7:
        jne short L_004619ea
    L_004619f9:
        test esi,esi
    L_004619fb:
        jge short L_00461a14
    L_004619fd:
        neg esi
    L_004619ff:
        and esi,0FFh
    L_00461a05:
        jle short L_00461a14
    L_00461a07:
        lea eax,[ebp-10h]
    L_00461a0a:
        push eax
    L_00461a0b:
        call asm_shr_12_00460845
    L_00461a10:
        dec esi
    L_00461a11:
        pop ecx
    L_00461a12:
        jne short L_00461a07
    L_00461a14:
        lea ecx,[edi+1]
    L_00461a17:
        test ecx,ecx
    L_00461a19:
        lea eax,[ebx+4]
    L_00461a1c:
        mov dword ptr [ebp-2Ch],eax
    L_00461a1f:
        jle short L_00461a71
    L_00461a21:
        mov dword ptr [ebp-34h],ecx
    L_00461a24:
        lea esi,[ebp-10h]
    L_00461a27:
        lea edi,[ebp-28h]
    L_00461a2a:
        movsd
    L_00461a2b:
        movsd
    L_00461a2c:
        lea eax,[ebp-10h]
    L_00461a2f:
        push eax
    L_00461a30:
        movsd
    L_00461a31:
        call asm_shl_12_00460817
    L_00461a36:
        lea eax,[ebp-10h]
    L_00461a39:
        push eax
    L_00461a3a:
        call asm_shl_12_00460817
    L_00461a3f:
        lea eax,[ebp-28h]
    L_00461a42:
        push eax
    L_00461a43:
        lea eax,[ebp-10h]
    L_00461a46:
        push eax
    L_00461a47:
        call asm_add_12_004607b9
    L_00461a4c:
        lea eax,[ebp-10h]
    L_00461a4f:
        push eax
    L_00461a50:
        call asm_shl_12_00460817
    L_00461a55:
        mov al,byte ptr [ebp-5]
    L_00461a58:
        mov ecx,dword ptr [ebp-2Ch]
    L_00461a5b:
        add al,30h
    L_00461a5d:
        add esp,14h
    L_00461a60:
        inc dword ptr [ebp-2Ch]
    L_00461a63:
        dec dword ptr [ebp-34h]
    L_00461a66:
        mov byte ptr [ecx],al
    L_00461a68:
        mov byte ptr [ebp-5],0
    L_00461a6c:
        jne short L_00461a24
    L_00461a6e:
        mov eax,dword ptr [ebp-2Ch]
    L_00461a71:
        dec eax
    L_00461a72:
        mov cl,byte ptr [eax]
    L_00461a74:
        dec eax
    L_00461a75:
        cmp cl,35h
    L_00461a78:
        lea ecx,[ebx+4]
    L_00461a7b:
        jl short L_00461abd
    L_00461a7d:
        jmp short L_00461a88
    L_00461a7f:
        cmp byte ptr [eax],39h
    L_00461a82:
        jne short L_00461a8c
    L_00461a84:
        mov byte ptr [eax],30h
    L_00461a87:
        dec eax
    L_00461a88:
        cmp eax,ecx
    L_00461a8a:
        jae short L_00461a7f
    L_00461a8c:
        cmp eax,ecx
    L_00461a8e:
        jae short L_00461a94
    L_00461a90:
        inc eax
    L_00461a91:
        inc word ptr [ebx]
    L_00461a94:
        inc byte ptr [eax]
    L_00461a96:
        sub al,bl
    L_00461a98:
        sub al,3
    L_00461a9a:
        mov byte ptr [ebx+3],al
    L_00461a9d:
        movsx eax,al
    L_00461aa0:
        mov byte ptr [eax+ebx+4],0
    L_00461aa5:
        mov eax,dword ptr [ebp-30h]
    L_00461aa8:
        mov ecx,dword ptr [ebp-4]
    L_00461aab:
        pop edi
    L_00461aac:
        pop esi
    L_00461aad:
        xor ecx,ebp
    L_00461aaf:
        pop ebx
    L_00461ab0:
        call asm_security_check_cookie_00458ea5
    L_00461ab5:
        leave
    L_00461ab6:
        ret
    L_00461ab7:
        cmp byte ptr [eax],30h
    L_00461aba:
        jne short L_00461ac1
    L_00461abc:
        dec eax
    L_00461abd:
        cmp eax,ecx
    L_00461abf:
        jae short L_00461ab7
    L_00461ac1:
        cmp eax,ecx
    L_00461ac3:
        jae short L_00461a96
    L_00461ac5:
        mov byte ptr [ecx],30h
    L_00461ac8:
        and word ptr [ebx],0
    L_00461acc:
        xor eax,eax
    L_00461ace:
        mov byte ptr [ebx+2],20h
    L_00461ad2:
        mov byte ptr [ebx+3],1
    L_00461ad6:
        mov byte ptr [ebx+5],0
    L_00461ada:
        inc eax
    L_00461adb:
        jmp short L_00461aa8
    }
}
