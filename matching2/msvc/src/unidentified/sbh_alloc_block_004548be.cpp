#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004548BE..0x00454BB9: ___sbh_alloc_block
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_sbh_alloc_block_004548be() {
    __asm {
    L_004548be:
        push ebp
    L_004548bf:
        mov ebp,esp
    L_004548c1:
        sub esp,14h
    L_004548c4:
        mov ecx,dword ptr [ebp+8]
    L_004548c7:
        mov eax,dword ptr [data_00499328]
    L_004548cc:
        mov edx,dword ptr [data_0049932c]
    L_004548d2:
        add ecx,17h
    L_004548d5:
        and ecx,0FFFFFFF0h
    L_004548d8:
        push ebx
    L_004548d9:
        mov dword ptr [ebp-10h],ecx
    L_004548dc:
        sar ecx,4
    L_004548df:
        push esi
    L_004548e0:
        lea eax,[eax+eax*4]
    L_004548e3:
        push edi
    L_004548e4:
        dec ecx
    L_004548e5:
        cmp ecx,20h
    L_004548e8:
        lea edi,[edx+eax*4]
    L_004548eb:
        mov dword ptr [ebp-4],edi
    L_004548ee:
        jge short L_004548fb
    L_004548f0:
        or esi,0FFFFFFFFh
    L_004548f3:
        shr esi,cl
    L_004548f5:
        or dword ptr [ebp-8],0FFFFFFFFh
    L_004548f9:
        jmp short L_00454908
    L_004548fb:
        add ecx,0FFFFFFE0h
    L_004548fe:
        or eax,0FFFFFFFFh
    L_00454901:
        xor esi,esi
    L_00454903:
        shr eax,cl
    L_00454905:
        mov dword ptr [ebp-8],eax
    L_00454908:
        mov eax,dword ptr [data_00499334]
    L_0045490d:
        mov ebx,eax
    L_0045490f:
        mov dword ptr [ebp-0Ch],esi
    L_00454912:
        cmp ebx,edi
    L_00454914:
        jmp short L_0045492a
    L_00454916:
        mov ecx,dword ptr [ebx+4]
    L_00454919:
        mov edi,dword ptr [ebx]
    L_0045491b:
        and ecx,dword ptr [ebp-8]
    L_0045491e:
        and edi,esi
    L_00454920:
        or ecx,edi
    L_00454922:
        jne short L_0045492f
    L_00454924:
        add ebx,14h
    L_00454927:
        cmp ebx,dword ptr [ebp-4]
    L_0045492a:
        mov dword ptr [ebp+8],ebx
    L_0045492d:
        jb short L_00454916
    L_0045492f:
        cmp ebx,dword ptr [ebp-4]
    L_00454932:
        jne short L_00454958
    L_00454934:
        mov ebx,edx
    L_00454936:
        jmp short L_00454949
    L_00454938:
        mov ecx,dword ptr [ebx+4]
    L_0045493b:
        mov edi,dword ptr [ebx]
    L_0045493d:
        and ecx,dword ptr [ebp-8]
    L_00454940:
        and edi,esi
    L_00454942:
        or ecx,edi
    L_00454944:
        jne short L_00454950
    L_00454946:
        add ebx,14h
    L_00454949:
        cmp ebx,eax
    L_0045494b:
        mov dword ptr [ebp+8],ebx
    L_0045494e:
        jb short L_00454938
    L_00454950:
        cmp ebx,eax
    L_00454952:
        je asm_target_004549ec
    L_00454958:
        mov dword ptr [data_00499334],ebx
    L_0045495e:
        mov eax,dword ptr [ebx+10h]
    L_00454961:
        mov edx,dword ptr [eax]
    L_00454963:
        cmp edx,0FFFFFFFFh
    L_00454966:
        mov dword ptr [ebp-4],edx
    L_00454969:
        je short L_0045497f
    L_0045496b:
        mov ecx,dword ptr [eax+edx*4+0C4h]
    L_00454972:
        mov edi,dword ptr [eax+edx*4+44h]
    L_00454976:
        and ecx,dword ptr [ebp-8]
    L_00454979:
        and edi,esi
    L_0045497b:
        or ecx,edi
    L_0045497d:
        jne short L_004549b5
    L_0045497f:
        mov edx,dword ptr [eax+0C4h]
    L_00454985:
        and edx,dword ptr [ebp-8]
    L_00454988:
        and dword ptr [ebp-4],0
    L_0045498c:
        lea ecx,[eax+44h]
    L_0045498f:
        mov esi,dword ptr [ecx]
    L_00454991:
        and esi,dword ptr [ebp-0Ch]
    L_00454994:
        or edx,esi
    L_00454996:
        mov esi,dword ptr [ebp-0Ch]
    L_00454999:
        jne short L_004549b2
    L_0045499b:
        mov edx,dword ptr [ecx+84h]
    L_004549a1:
        and edx,dword ptr [ebp-8]
    L_004549a4:
        inc dword ptr [ebp-4]
    L_004549a7:
        add ecx,4
    L_004549aa:
        mov edi,dword ptr [ecx]
    L_004549ac:
        and edi,esi
    L_004549ae:
        or edx,edi
    L_004549b0:
        je short L_0045499b
    L_004549b2:
        mov edx,dword ptr [ebp-4]
    L_004549b5:
        mov ecx,edx
    L_004549b7:
        imul ecx,204h
    L_004549bd:
        lea ecx,[ecx+eax+144h]
    L_004549c4:
        mov dword ptr [ebp-0Ch],ecx
    L_004549c7:
        mov ecx,dword ptr [eax+edx*4+44h]
    L_004549cb:
        xor edi,edi
    L_004549cd:
        and ecx,esi
    L_004549cf:
        jne short L_00454a3e
    L_004549d1:
        mov ecx,dword ptr [eax+edx*4+0C4h]
    L_004549d8:
        and ecx,dword ptr [ebp-8]
    L_004549db:
        push 20h
    L_004549dd:
        pop edi
    L_004549de:
        jmp short L_00454a3e
    L_004549e0:
        cmp dword ptr [ebx+8],0
    L_004549e4:
        jne short L_004549f1
    L_004549e6:
        add ebx,14h
    L_004549e9:
        mov dword ptr [ebp+8],ebx
    L_004549ec:
        cmp ebx,dword ptr [ebp-4]
    L_004549ef:
        jb short L_004549e0
    L_004549f1:
        cmp ebx,dword ptr [ebp-4]
    L_004549f4:
        jne short L_00454a1c
    L_004549f6:
        mov ebx,edx
    L_004549f8:
        jmp short L_00454a03
    L_004549fa:
        cmp dword ptr [ebx+8],0
    L_004549fe:
        jne short L_00454a0a
    L_00454a00:
        add ebx,14h
    L_00454a03:
        cmp ebx,eax
    L_00454a05:
        mov dword ptr [ebp+8],ebx
    L_00454a08:
        jb short L_004549fa
    L_00454a0a:
        cmp ebx,eax
    L_00454a0c:
        jne short L_00454a1c
    L_00454a0e:
        call asm_sbh_alloc_new_region_00453fdd
    L_00454a13:
        mov ebx,eax
    L_00454a15:
        test ebx,ebx
    L_00454a17:
        mov dword ptr [ebp+8],ebx
    L_00454a1a:
        je short L_00454a34
    L_00454a1c:
        push ebx
    L_00454a1d:
        call asm_sbh_alloc_new_group_00454094
    L_00454a22:
        pop ecx
    L_00454a23:
        mov ecx,dword ptr [ebx+10h]
    L_00454a26:
        mov dword ptr [ecx],eax
    L_00454a28:
        mov eax,dword ptr [ebx+10h]
    L_00454a2b:
        cmp dword ptr [eax],0FFFFFFFFh
    L_00454a2e:
        jne asm_target_00454958
    L_00454a34:
        xor eax,eax
    L_00454a36:
        jmp asm_target_00454bb5
    L_00454a3b:
        shl ecx,1
    L_00454a3d:
        inc edi
    L_00454a3e:
        test ecx,ecx
    L_00454a40:
        jge short L_00454a3b
    L_00454a42:
        mov ecx,dword ptr [ebp-0Ch]
    L_00454a45:
        mov edx,dword ptr [ecx+edi*8+4]
    L_00454a49:
        mov ecx,dword ptr [edx]
    L_00454a4b:
        sub ecx,dword ptr [ebp-10h]
    L_00454a4e:
        mov esi,ecx
    L_00454a50:
        sar esi,4
    L_00454a53:
        dec esi
    L_00454a54:
        cmp esi,3Fh
    L_00454a57:
        mov dword ptr [ebp-8],ecx
    L_00454a5a:
        jle short L_00454a5f
    L_00454a5c:
        push 3Fh
    L_00454a5e:
        pop esi
    L_00454a5f:
        cmp esi,edi
    L_00454a61:
        je asm_target_00454b68
    L_00454a67:
        mov ecx,dword ptr [edx+4]
    L_00454a6a:
        cmp ecx,dword ptr [edx+8]
    L_00454a6d:
        jne short L_00454acb
    L_00454a6f:
        cmp edi,20h
    L_00454a72:
        mov ebx,80000000h
    L_00454a77:
        jge short L_00454a9f
    L_00454a79:
        mov ecx,edi
    L_00454a7b:
        shr ebx,cl
    L_00454a7d:
        mov ecx,dword ptr [ebp-4]
    L_00454a80:
        lea edi,[eax+edi+4]
    L_00454a84:
        not ebx
    L_00454a86:
        mov dword ptr [ebp-14h],ebx
    L_00454a89:
        and ebx,dword ptr [eax+ecx*4+44h]
    L_00454a8d:
        mov dword ptr [eax+ecx*4+44h],ebx
    L_00454a91:
        dec byte ptr [edi]
    L_00454a93:
        jne short L_00454ac8
    L_00454a95:
        mov ecx,dword ptr [ebp-14h]
    L_00454a98:
        mov ebx,dword ptr [ebp+8]
    L_00454a9b:
        and dword ptr [ebx],ecx
    L_00454a9d:
        jmp short L_00454acb
    L_00454a9f:
        lea ecx,[edi-20h]
    L_00454aa2:
        shr ebx,cl
    L_00454aa4:
        mov ecx,dword ptr [ebp-4]
    L_00454aa7:
        lea ecx,[eax+ecx*4+0C4h]
    L_00454aae:
        lea edi,[eax+edi+4]
    L_00454ab2:
        not ebx
    L_00454ab4:
        and dword ptr [ecx],ebx
    L_00454ab6:
        dec byte ptr [edi]
    L_00454ab8:
        mov dword ptr [ebp-14h],ebx
    L_00454abb:
        jne short L_00454ac8
    L_00454abd:
        mov ebx,dword ptr [ebp+8]
    L_00454ac0:
        mov ecx,dword ptr [ebp-14h]
    L_00454ac3:
        and dword ptr [ebx+4],ecx
    L_00454ac6:
        jmp short L_00454acb
    L_00454ac8:
        mov ebx,dword ptr [ebp+8]
    L_00454acb:
        cmp dword ptr [ebp-8],0
    L_00454acf:
        mov ecx,dword ptr [edx+8]
    L_00454ad2:
        mov edi,dword ptr [edx+4]
    L_00454ad5:
        mov dword ptr [ecx+4],edi
    L_00454ad8:
        mov ecx,dword ptr [edx+4]
    L_00454adb:
        mov edi,dword ptr [edx+8]
    L_00454ade:
        mov dword ptr [ecx+8],edi
    L_00454ae1:
        je asm_target_00454b74
    L_00454ae7:
        mov ecx,dword ptr [ebp-0Ch]
    L_00454aea:
        lea ecx,[ecx+esi*8]
    L_00454aed:
        mov edi,dword ptr [ecx+4]
    L_00454af0:
        mov dword ptr [edx+8],ecx
    L_00454af3:
        mov dword ptr [edx+4],edi
    L_00454af6:
        mov dword ptr [ecx+4],edx
    L_00454af9:
        mov ecx,dword ptr [edx+4]
    L_00454afc:
        mov dword ptr [ecx+8],edx
    L_00454aff:
        mov ecx,dword ptr [edx+4]
    L_00454b02:
        cmp ecx,dword ptr [edx+8]
    L_00454b05:
        jne short L_00454b65
    L_00454b07:
        mov cl,byte ptr [esi+eax+4]
    L_00454b0b:
        mov byte ptr [ebp+0Bh],cl
    L_00454b0e:
        inc cl
    L_00454b10:
        cmp esi,20h
    L_00454b13:
        mov byte ptr [esi+eax+4],cl
    L_00454b17:
        jge short L_00454b3c
    L_00454b19:
        cmp byte ptr [ebp+0Bh],0
    L_00454b1d:
        jne short L_00454b2a
    L_00454b1f:
        mov edi,80000000h
    L_00454b24:
        mov ecx,esi
    L_00454b26:
        shr edi,cl
    L_00454b28:
        or dword ptr [ebx],edi
    L_00454b2a:
        mov ecx,esi
    L_00454b2c:
        mov edi,80000000h
    L_00454b31:
        shr edi,cl
    L_00454b33:
        mov ecx,dword ptr [ebp-4]
    L_00454b36:
        or dword ptr [eax+ecx*4+44h],edi
    L_00454b3a:
        jmp short L_00454b65
    L_00454b3c:
        cmp byte ptr [ebp+0Bh],0
    L_00454b40:
        jne short L_00454b4f
    L_00454b42:
        lea ecx,[esi-20h]
    L_00454b45:
        mov edi,80000000h
    L_00454b4a:
        shr edi,cl
    L_00454b4c:
        or dword ptr [ebx+4],edi
    L_00454b4f:
        mov ecx,dword ptr [ebp-4]
    L_00454b52:
        lea edi,[eax+ecx*4+0C4h]
    L_00454b59:
        lea ecx,[esi-20h]
    L_00454b5c:
        mov esi,80000000h
    L_00454b61:
        shr esi,cl
    L_00454b63:
        or dword ptr [edi],esi
    L_00454b65:
        mov ecx,dword ptr [ebp-8]
    L_00454b68:
        test ecx,ecx
    L_00454b6a:
        je short L_00454b77
    L_00454b6c:
        mov dword ptr [edx],ecx
    L_00454b6e:
        mov dword ptr [ecx+edx-4],ecx
    L_00454b72:
        jmp short L_00454b77
    L_00454b74:
        mov ecx,dword ptr [ebp-8]
    L_00454b77:
        mov esi,dword ptr [ebp-10h]
    L_00454b7a:
        add edx,ecx
    L_00454b7c:
        lea ecx,[esi+1]
    L_00454b7f:
        mov dword ptr [edx],ecx
    L_00454b81:
        mov dword ptr [edx+esi-4],ecx
    L_00454b85:
        mov esi,dword ptr [ebp-0Ch]
    L_00454b88:
        mov ecx,dword ptr [esi]
    L_00454b8a:
        test ecx,ecx
    L_00454b8c:
        lea edi,[ecx+1]
    L_00454b8f:
        mov dword ptr [esi],edi
    L_00454b91:
        jne short L_00454bad
    L_00454b93:
        cmp ebx,dword ptr [data_00499324]
    L_00454b99:
        jne short L_00454bad
    L_00454b9b:
        mov ecx,dword ptr [ebp-4]
    L_00454b9e:
        cmp ecx,dword ptr [data_0049933c]
    L_00454ba4:
        jne short L_00454bad
    L_00454ba6:
        and dword ptr [data_00499324],0
    L_00454bad:
        mov ecx,dword ptr [ebp-4]
    L_00454bb0:
        mov dword ptr [eax],ecx
    L_00454bb2:
        lea eax,[edx+4]
    L_00454bb5:
        pop edi
    L_00454bb6:
        pop esi
    L_00454bb7:
        pop ebx
    L_00454bb8:
        leave
    L_00454bb9:
        ret
    }
}
