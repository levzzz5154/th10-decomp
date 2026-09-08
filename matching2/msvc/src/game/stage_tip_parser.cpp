#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00419960..0x00419BC6: FUN_00419960
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00419960_00419960() {
    __asm {
    L_00419960:
        sub esp,24h
    L_00419963:
        push esi
    L_00419964:
        push 1
    L_00419966:
        lea eax,[esp+34h]
    L_0041996a:
        push eax
    L_0041996b:
        mov eax,dword ptr [esp+38h]
    L_0041996f:
        mov dword ptr [esp+0Ch],0FFFFFFFFh
    L_00419977:
        mov dword ptr [esp+10h],0
    L_0041997f:
        call asm_FUN_0044b360_0044b360
    L_00419984:
        mov esi,eax
    L_00419986:
        test esi,esi
    L_00419988:
        mov dword ptr [esp+18h],esi
    L_0041998c:
        jne short L_00419998
    L_0041998e:
        or eax,0FFFFFFFFh
    L_00419991:
        pop esi
    L_00419992:
        add esp,24h
    L_00419995:
        ret 0Ch
    L_00419998:
        push ebx
    L_00419999:
        push ebp
    L_0041999a:
        push edi
    L_0041999b:
        push 1000h
    L_004199a0:
        call asm_malloc_00452706
    L_004199a5:
        mov edi,eax
    L_004199a7:
        push 1000h
    L_004199ac:
        mov dword ptr [esp+24h],edi
    L_004199b0:
        call asm_malloc_00452706
    L_004199b5:
        mov ebp,eax
    L_004199b7:
        push 1000h
    L_004199bc:
        mov dword ptr [esp+24h],ebp
    L_004199c0:
        call asm_malloc_00452706
    L_004199c5:
        mov ecx,dword ptr [esp+48h]
    L_004199c9:
        add esp,0Ch
    L_004199cc:
        test ecx,ecx
    L_004199ce:
        mov ebx,eax
    L_004199d0:
        mov eax,esi
    L_004199d2:
        jle asm_target_00419acb
    L_004199d8:
        mov esi,edi
    L_004199da:
        sub esi,ebp
    L_004199dc:
        mov ecx,ebp
    L_004199de:
        sub ecx,edi
    L_004199e0:
        mov dword ptr [esp+28h],esi
    L_004199e4:
        mov dword ptr [esp+2Ch],ecx
    L_004199e8:
        jmp short L_004199f2
    L_004199ea:
        mov eax,dword ptr [esp+20h]
    L_004199ee:
        mov esi,dword ptr [esp+28h]
    L_004199f2:
        push 1000h
    L_004199f7:
        lea ecx,[esp+40h]
    L_004199fb:
        push ecx
    L_004199fc:
        push edi
    L_004199fd:
        call asm_FUN_00419f40_00419f40
    L_00419a02:
        mov dword ptr [esp+20h],eax
    L_00419a06:
        mov eax,ebp
    L_00419a08:
        mov cl,byte ptr [esi+eax]
    L_00419a0b:
        mov byte ptr [eax],cl
    L_00419a0d:
        inc eax
    L_00419a0e:
        test cl,cl
    L_00419a10:
        jne short L_00419a08
    L_00419a12:
        push 3Ah
    L_00419a14:
        push ebp
    L_00419a15:
        call asm_FUN_00452730_00452730
    L_00419a1a:
        add esp,8
    L_00419a1d:
        test eax,eax
    L_00419a1f:
        jne short L_00419a25
    L_00419a21:
        mov eax,ebp
    L_00419a23:
        jmp short L_00419a45
    L_00419a25:
        lea ecx,[eax+1]
    L_00419a28:
        mov esi,ebx
    L_00419a2a:
        sub esi,ecx
    L_00419a2c:
        TH10_NOP_LEA_ESP_DISP8()
    L_00419a30:
        mov dl,byte ptr [ecx]
    L_00419a32:
        mov byte ptr [esi+ecx],dl
    L_00419a35:
        inc ecx
    L_00419a36:
        test dl,dl
    L_00419a38:
        jne short L_00419a30
    L_00419a3a:
        mov byte ptr [eax],dl
    L_00419a3c:
        mov eax,ebp
    L_00419a3e:
        call asm_Recovery_TrimWhitespace_0041a0a0
    L_00419a43:
        mov eax,ebx
    L_00419a45:
        call asm_Recovery_TrimWhitespace_0041a0a0
    L_00419a4a:
        mov eax,edi
    L_00419a4c:
        TH10_NOP_LEA_ESP_DISP8()
    L_00419a50:
        mov cl,byte ptr [eax]
    L_00419a52:
        mov edx,dword ptr [esp+2Ch]
    L_00419a56:
        mov byte ptr [edx+eax],cl
    L_00419a59:
        inc eax
    L_00419a5a:
        test cl,cl
    L_00419a5c:
        jne short L_00419a50
    L_00419a5e:
        push 3Ah
    L_00419a60:
        push ebp
    L_00419a61:
        call asm_FUN_00452730_00452730
    L_00419a66:
        add esp,8
    L_00419a69:
        test eax,eax
    L_00419a6b:
        jne short L_00419a71
    L_00419a6d:
        mov eax,ebp
    L_00419a6f:
        jmp short L_00419a8d
    L_00419a71:
        lea ecx,[eax+1]
    L_00419a74:
        mov esi,ebx
    L_00419a76:
        sub esi,ecx
    L_00419a78:
        mov dl,byte ptr [ecx]
    L_00419a7a:
        mov byte ptr [esi+ecx],dl
    L_00419a7d:
        inc ecx
    L_00419a7e:
        test dl,dl
    L_00419a80:
        jne short L_00419a78
    L_00419a82:
        mov byte ptr [eax],dl
    L_00419a84:
        mov eax,ebp
    L_00419a86:
        call asm_Recovery_TrimWhitespace_0041a0a0
    L_00419a8b:
        mov eax,ebx
    L_00419a8d:
        call asm_Recovery_TrimWhitespace_0041a0a0
    L_00419a92:
        mov edi,46D658h
    L_00419a97:
        mov esi,ebp
    L_00419a99:
        mov ecx,8
    L_00419a9e:
        xor eax,eax
    L_00419aa0:
        repe cmpsb
    L_00419aa2:
        jne short L_00419af2
    L_00419aa4:
        mov edi,46D654h
    L_00419aa9:
        mov esi,ebx
    L_00419aab:
        mov ecx,4
    L_00419ab0:
        xor edx,edx
    L_00419ab2:
        repe cmpsb
    L_00419ab4:
        je asm_target_00419f25
    L_00419aba:
        mov eax,dword ptr [esp+38h]
    L_00419abe:
        call asm_Recovery_ClearEightBuckets_00419040
    L_00419ac3:
        mov edi,dword ptr [esp+1Ch]
    L_00419ac7:
        mov esi,dword ptr [esp+24h]
    L_00419acb:
        push edi
    L_00419acc:
        call asm_free_00452422
    L_00419ad1:
        push ebp
    L_00419ad2:
        call asm_free_00452422
    L_00419ad7:
        push ebx
    L_00419ad8:
        call asm_free_00452422
    L_00419add:
        push esi
    L_00419ade:
        call asm_free_00452422
    L_00419ae3:
        add esp,10h
    L_00419ae6:
        pop edi
    L_00419ae7:
        pop ebp
    L_00419ae8:
        pop ebx
    L_00419ae9:
        xor eax,eax
    L_00419aeb:
        pop esi
    L_00419aec:
        add esp,24h
    L_00419aef:
        ret 0Ch
    L_00419af2:
        mov edi,46D64Ch
    L_00419af7:
        mov esi,ebp
    L_00419af9:
        mov ecx,6
    L_00419afe:
        xor eax,eax
    L_00419b00:
        repe cmpsb
    L_00419b02:
        jne short L_00419b33
    L_00419b04:
        push ebx
    L_00419b05:
        call asm_atol_00452876
    L_00419b0a:
        add esp,4
    L_00419b0d:
        test eax,eax
    L_00419b0f:
        mov dword ptr [esp+10h],eax
    L_00419b13:
        mov dword ptr [esp+14h],0
    L_00419b1b:
        jle short L_00419b26
    L_00419b1d:
        cmp eax,8
    L_00419b20:
        jl asm_target_00419f25
    L_00419b26:
        mov dword ptr [esp+10h],0FFFFFFFFh
    L_00419b2e:
        jmp asm_target_00419f25
    L_00419b33:
        mov edi,46D640h
    L_00419b38:
        mov esi,ebp
    L_00419b3a:
        mov ecx,9
    L_00419b3f:
        xor edx,edx
    L_00419b41:
        repe cmpsb
    L_00419b43:
        jne short L_00419b52
    L_00419b45:
        mov dword ptr [esp+10h],0FFFFFFFFh
    L_00419b4d:
        jmp asm_target_00419f25
    L_00419b52:
        mov edi,46D638h
    L_00419b57:
        mov esi,ebp
    L_00419b59:
        mov ecx,5
    L_00419b5e:
        xor eax,eax
    L_00419b60:
        repe cmpsb
    L_00419b62:
        jne asm_target_00419f25
    L_00419b68:
        mov eax,dword ptr [esp+10h]
    L_00419b6c:
        test eax,eax
    L_00419b6e:
        jle asm_target_00419f25
    L_00419b74:
        cmp dword ptr [esp+14h],0FFh
    L_00419b7c:
        jl short L_00419b8b
    L_00419b7e:
        mov dword ptr [esp+10h],0FFFFFFFFh
    L_00419b86:
        jmp asm_target_00419f25
    L_00419b8b:
        push 88h
    L_00419b90:
        call asm_operator_new_00452493
    L_00419b95:
        add esp,4
    L_00419b98:
        test eax,eax
    L_00419b9a:
        je short L_00419ba7
    L_00419b9c:
        mov edx,eax
    L_00419b9e:
        call asm_StageTip_Initialize_00418d00
    L_00419ba3:
        mov ebp,eax
    L_00419ba5:
        jmp short L_00419ba9
    L_00419ba7:
        xor ebp,ebp
    L_00419ba9:
        mov ecx,dword ptr [esp+14h]
    L_00419bad:
        mov eax,dword ptr [esp+3Ch]
    L_00419bb1:
        inc ecx
    L_00419bb2:
        test eax,eax
    L_00419bb4:
        mov dword ptr [esp+14h],ecx
    L_00419bb8:
        mov dword ptr [ebp+18h],0
    L_00419bbf:
        jle asm_target_00419e83
    L_00419bc5:
        TH10_REL8(0xeb, 0x00419bc5, VA_asm_FUN_00419960_part_00419bd0)
    }
}

// 0x00419BD0..0x00419F39: FUN_00419960
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00419960_part_00419bd0() {
    __asm {
    L_00419bd0:
        mov esi,dword ptr [esp+1Ch]
    L_00419bd4:
        mov eax,dword ptr [esp+20h]
    L_00419bd8:
        push 1000h
    L_00419bdd:
        lea ecx,[esp+40h]
    L_00419be1:
        push ecx
    L_00419be2:
        push esi
    L_00419be3:
        call asm_FUN_00419f40_00419f40
    L_00419be8:
        mov dword ptr [esp+20h],eax
    L_00419bec:
        mov eax,esi
    L_00419bee:
        mov esi,dword ptr [esp+18h]
    L_00419bf2:
        mov edi,esi
    L_00419bf4:
        call asm_Recovery_SplitResourcePath_0041a050
    L_00419bf9:
        mov edi,46D610h
    L_00419bfe:
        mov ecx,4
    L_00419c03:
        xor edx,edx
    L_00419c05:
        repe cmpsb
    L_00419c07:
        jne short L_00419c5a
    L_00419c09:
        push 2Ch
    L_00419c0b:
        push ebx
    L_00419c0c:
        call asm_FUN_00452730_00452730
    L_00419c11:
        mov esi,eax
    L_00419c13:
        add esp,8
    L_00419c16:
        test esi,esi
    L_00419c18:
        je asm_target_00419e77
    L_00419c1e:
        mov byte ptr [esi],0
    L_00419c21:
        mov eax,ebx
    L_00419c23:
        inc esi
    L_00419c24:
        call asm_Recovery_TrimWhitespace_0041a0a0
    L_00419c29:
        mov eax,esi
    L_00419c2b:
        call asm_Recovery_TrimWhitespace_0041a0a0
    L_00419c30:
        push ebx
    L_00419c31:
        call asm_atol_00452876
    L_00419c36:
        mov dword ptr [esp+34h],eax
    L_00419c3a:
        fild dword ptr [esp+34h]
    L_00419c3e:
        push esi
    L_00419c3f:
        fstp dword ptr [ebp]
    L_00419c42:
        call asm_atol_00452876
    L_00419c47:
        mov dword ptr [esp+38h],eax
    L_00419c4b:
        fild dword ptr [esp+38h]
    L_00419c4f:
        add esp,8
    L_00419c52:
        fstp dword ptr [ebp+4]
    L_00419c55:
        jmp asm_target_00419e77
    L_00419c5a:
        mov eax,dword ptr [esp+18h]
    L_00419c5e:
        mov edi,46D608h
    L_00419c63:
        mov esi,eax
    L_00419c65:
        mov ecx,5
    L_00419c6a:
        xor edx,edx
    L_00419c6c:
        repe cmpsb
    L_00419c6e:
        jne short L_00419cb0
    L_00419c70:
        push 22h
    L_00419c72:
        push ebx
    L_00419c73:
        call asm_FUN_00452730_00452730
    L_00419c78:
        mov esi,eax
    L_00419c7a:
        add esp,8
    L_00419c7d:
        test esi,esi
    L_00419c7f:
        je asm_target_00419e77
    L_00419c85:
        inc esi
    L_00419c86:
        push 22h
    L_00419c88:
        push esi
    L_00419c89:
        call asm_strrchr_00452930
    L_00419c8e:
        add esp,8
    L_00419c91:
        test eax,eax
    L_00419c93:
        je asm_target_00419e83
    L_00419c99:
        push 41h
    L_00419c9b:
        mov byte ptr [eax],0
    L_00419c9e:
        lea eax,[ebp+1Ch]
    L_00419ca1:
        push esi
    L_00419ca2:
        push eax
    L_00419ca3:
        call asm_strncpy_00452960
    L_00419ca8:
        add esp,0Ch
    L_00419cab:
        jmp asm_target_00419e77
    L_00419cb0:
        mov edi,46D600h
    L_00419cb5:
        mov esi,eax
    L_00419cb7:
        mov ecx,6
    L_00419cbc:
        xor edx,edx
    L_00419cbe:
        repe cmpsb
    L_00419cc0:
        jne short L_00419cd3
    L_00419cc2:
        push ebx
    L_00419cc3:
        call asm_atol_00452876
    L_00419cc8:
        add esp,4
    L_00419ccb:
        mov dword ptr [ebp+60h],eax
    L_00419cce:
        jmp asm_target_00419e77
    L_00419cd3:
        mov edi,46D5F8h
    L_00419cd8:
        mov esi,eax
    L_00419cda:
        mov ecx,5
    L_00419cdf:
        xor edx,edx
    L_00419ce1:
        repe cmpsb
    L_00419ce3:
        jne short L_00419cf6
    L_00419ce5:
        push ebx
    L_00419ce6:
        call asm_atol_00452876
    L_00419ceb:
        add esp,4
    L_00419cee:
        mov dword ptr [ebp+6Ch],eax
    L_00419cf1:
        jmp asm_target_00419e77
    L_00419cf6:
        mov edi,46D5F0h
    L_00419cfb:
        mov esi,eax
    L_00419cfd:
        mov ecx,5
    L_00419d02:
        xor edx,edx
    L_00419d04:
        repe cmpsb
    L_00419d06:
        jne short L_00419d1e
    L_00419d08:
        push 3Dh
    L_00419d0a:
        push 4744B0h
    L_00419d0f:
        mov edx,ebx
    L_00419d11:
        call asm_Recovery_FindNamedValue_004198c0
    L_00419d16:
        mov dword ptr [ebp+68h],eax
    L_00419d19:
        jmp asm_target_00419e77
    L_00419d1e:
        mov edi,46D5E8h
    L_00419d23:
        mov esi,eax
    L_00419d25:
        mov ecx,6
    L_00419d2a:
        xor edx,edx
    L_00419d2c:
        repe cmpsb
    L_00419d2e:
        jne short L_00419d46
    L_00419d30:
        push 3
    L_00419d32:
        push 474494h
    L_00419d37:
        mov edx,ebx
    L_00419d39:
        call asm_Recovery_FindNamedValue_004198c0
    L_00419d3e:
        mov dword ptr [ebp+64h],eax
    L_00419d41:
        jmp asm_target_00419e77
    L_00419d46:
        mov edi,46D5E0h
    L_00419d4b:
        mov esi,eax
    L_00419d4d:
        mov ecx,7
    L_00419d52:
        xor edx,edx
    L_00419d54:
        repe cmpsb
    L_00419d56:
        jne short L_00419d69
    L_00419d58:
        push ebx
    L_00419d59:
        call asm_atol_00452876
    L_00419d5e:
        add esp,4
    L_00419d61:
        mov dword ptr [ebp+70h],eax
    L_00419d64:
        jmp asm_target_00419e77
    L_00419d69:
        mov edi,46D5D8h
    L_00419d6e:
        mov esi,eax
    L_00419d70:
        mov ecx,6
    L_00419d75:
        xor edx,edx
    L_00419d77:
        repe cmpsb
    L_00419d79:
        jne short L_00419dbf
    L_00419d7b:
        push ebx
    L_00419d7c:
        call asm_atof_00452a84
    L_00419d81:
        fcom dword ptr [data_00470c40]
    L_00419d87:
        add esp,4
    L_00419d8a:
        fst dword ptr [ebp+7Ch]
    L_00419d8d:
        fnstsw ax
    L_00419d8f:
        test ah,41h
    L_00419d92:
        jne short L_00419da2
    L_00419d94:
        fstp st(0)
    L_00419d96:
        mov dword ptr [ebp+7Ch],40800000h
    L_00419d9d:
        jmp asm_target_00419e77
    L_00419da2:
        fcomp dword ptr [data_00470c60]
    L_00419da8:
        fnstsw ax
    L_00419daa:
        test ah,5
    L_00419dad:
        jp asm_target_00419e77
    L_00419db3:
        mov dword ptr [ebp+7Ch],0C0800000h
    L_00419dba:
        jmp asm_target_00419e77
    L_00419dbf:
        mov edi,46D5D0h
    L_00419dc4:
        mov esi,eax
    L_00419dc6:
        mov ecx,6
    L_00419dcb:
        xor edx,edx
    L_00419dcd:
        repe cmpsb
    L_00419dcf:
        jne short L_00419e42
    L_00419dd1:
        push 2Ch
    L_00419dd3:
        push ebx
    L_00419dd4:
        call asm_FUN_00452730_00452730
    L_00419dd9:
        mov esi,eax
    L_00419ddb:
        add esp,8
    L_00419dde:
        test esi,esi
    L_00419de0:
        je asm_target_00419e77
    L_00419de6:
        mov byte ptr [esi],0
    L_00419de9:
        mov eax,ebx
    L_00419deb:
        inc esi
    L_00419dec:
        call asm_Recovery_TrimWhitespace_0041a0a0
    L_00419df1:
        push ebx
    L_00419df2:
        call asm_atol_00452876
    L_00419df7:
        push 2Ch
    L_00419df9:
        push esi
    L_00419dfa:
        mov byte ptr [ebp+86h],al
    L_00419e00:
        mov edi,esi
    L_00419e02:
        call asm_FUN_00452730_00452730
    L_00419e07:
        mov esi,eax
    L_00419e09:
        add esp,0Ch
    L_00419e0c:
        test esi,esi
    L_00419e0e:
        je short L_00419e77
    L_00419e10:
        mov eax,edi
    L_00419e12:
        mov byte ptr [esi],0
    L_00419e15:
        call asm_Recovery_TrimWhitespace_0041a0a0
    L_00419e1a:
        push edi
    L_00419e1b:
        call asm_atol_00452876
    L_00419e20:
        mov byte ptr [ebp+85h],al
    L_00419e26:
        add esp,4
    L_00419e29:
        lea eax,[esi+1]
    L_00419e2c:
        call asm_Recovery_TrimWhitespace_0041a0a0
    L_00419e31:
        push eax
    L_00419e32:
        call asm_atol_00452876
    L_00419e37:
        add esp,4
    L_00419e3a:
        mov byte ptr [ebp+84h],al
    L_00419e40:
        jmp short L_00419e77
    L_00419e42:
        mov edi,46D5C8h
    L_00419e47:
        mov esi,eax
    L_00419e49:
        mov ecx,6
    L_00419e4e:
        xor edx,edx
    L_00419e50:
        repe cmpsb
    L_00419e52:
        jne short L_00419e65
    L_00419e54:
        push ebx
    L_00419e55:
        call asm_atol_00452876
    L_00419e5a:
        add esp,4
    L_00419e5d:
        mov byte ptr [ebp+87h],al
    L_00419e63:
        jmp short L_00419e77
    L_00419e65:
        mov esi,eax
    L_00419e67:
        mov edi,46D5C4h
    L_00419e6c:
        mov ecx,4
    L_00419e71:
        xor eax,eax
    L_00419e73:
        repe cmpsb
    L_00419e75:
        je short L_00419e83
    L_00419e77:
        mov eax,dword ptr [esp+3Ch]
    L_00419e7b:
        test eax,eax
    L_00419e7d:
        jg asm_FUN_00419960_part_00419bd0
    L_00419e83:
        lea eax,[ebp+1Ch]
    L_00419e86:
        lea edx,[eax+1]
    L_00419e89:
        lea esp,[esp+force_disp32_zero]
    L_00419e90:
        mov cl,byte ptr [eax]
    L_00419e92:
        inc eax
    L_00419e93:
        test cl,cl
    L_00419e95:
        jne short L_00419e90
    L_00419e97:
        sub eax,edx
    L_00419e99:
        test eax,eax
    L_00419e9b:
        mov dword ptr [esp+30h],eax
    L_00419e9f:
        fild dword ptr [esp+30h]
    L_00419ea3:
        jge short L_00419eab
    L_00419ea5:
        fadd dword ptr [data_00470b98]
    L_00419eab:
        fmul dword ptr [ebp+7Ch]
    L_00419eae:
        mov eax,dword ptr [esp+10h]
    L_00419eb2:
        lea ecx,[eax+eax*2+6]
    L_00419eb6:
        mov eax,dword ptr [esp+38h]
    L_00419eba:
        fmul dword ptr [data_00470c5c]
    L_00419ec0:
        lea edx,[ebp+0Ch]
    L_00419ec3:
        lea eax,[eax+ecx*4]
    L_00419ec6:
        fstp dword ptr [ebp+80h]
    L_00419ecc:
        call asm_Recovery_AppendNode_0041ab10
    L_00419ed1:
        mov eax,dword ptr [esp+40h]
    L_00419ed5:
        test eax,eax
    L_00419ed7:
        jne short L_00419f21
    L_00419ed9:
        push 88h
    L_00419ede:
        call asm_operator_new_00452493
    L_00419ee3:
        add esp,4
    L_00419ee6:
        test eax,eax
    L_00419ee8:
        je short L_00419ef3
    L_00419eea:
        mov edx,eax
    L_00419eec:
        call asm_StageTip_Initialize_00418d00
    L_00419ef1:
        jmp short L_00419ef5
    L_00419ef3:
        xor eax,eax
    L_00419ef5:
        lea edx,[eax+0Ch]
    L_00419ef8:
        mov edi,eax
    L_00419efa:
        mov ecx,22h
    L_00419eff:
        mov esi,ebp
    L_00419f01:
        rep movsd
    L_00419f03:
        mov dword ptr [edx],eax
    L_00419f05:
        xor eax,eax
    L_00419f07:
        mov dword ptr [edx+4],eax
    L_00419f0a:
        mov dword ptr [edx+8],eax
    L_00419f0d:
        mov eax,dword ptr [esp+10h]
    L_00419f11:
        lea ecx,[eax+eax*2+1Eh]
    L_00419f15:
        mov eax,dword ptr [esp+38h]
    L_00419f19:
        lea eax,[eax+ecx*4]
    L_00419f1c:
        call asm_Recovery_AppendNode_0041ab10
    L_00419f21:
        mov ebp,dword ptr [esp+18h]
    L_00419f25:
        mov eax,dword ptr [esp+3Ch]
    L_00419f29:
        test eax,eax
    L_00419f2b:
        mov edi,dword ptr [esp+1Ch]
    L_00419f2f:
        jg asm_target_004199ea
    L_00419f35:
        jmp asm_target_00419ac7
    }
}
