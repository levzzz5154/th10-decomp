#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00461AF9..0x00461CA1: FUN_00461af9
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00461af9_00461af9() {
    __asm {
    L_00461af9:
        push 48h
    L_00461afb:
        push 46C9C0h
    L_00461b00:
        call asm_SEH_prolog_00454bbc
    L_00461b05:
        mov eax,dword ptr [data_00473660]
    L_00461b0a:
        xor eax,ebp
    L_00461b0c:
        mov dword ptr [ebp-1Ch],eax
    L_00461b0f:
        mov esi,dword ptr [ebp+10h]
    L_00461b12:
        mov dword ptr [ebp-3Ch],esi
    L_00461b15:
        mov ebx,dword ptr [ebp+18h]
    L_00461b18:
        mov dword ptr [ebp-34h],ebx
    L_00461b1b:
        xor edi,edi
    L_00461b1d:
        cmp dword ptr [data_004776d4],edi
    L_00461b23:
        jne short L_00461b5d
    L_00461b25:
        push 1
    L_00461b27:
        mov eax,46B5C4h
    L_00461b2c:
        push eax
    L_00461b2d:
        push 1
    L_00461b2f:
        push eax
    L_00461b30:
        push edi
    L_00461b31:
        push edi
    L_00461b32:
        call dword ptr [data_004661d0]
    L_00461b38:
        test eax,eax
    L_00461b3a:
        je short L_00461b48
    L_00461b3c:
        mov dword ptr [data_004776d4],1
    L_00461b46:
        jmp short L_00461b5d
    L_00461b48:
        call dword ptr [data_0046610c]
    L_00461b4e:
        cmp eax,78h
    L_00461b51:
        jne short L_00461b5d
    L_00461b53:
        mov dword ptr [data_004776d4],2
    L_00461b5d:
        cmp dword ptr [ebp+14h],edi
    L_00461b60:
        jle short L_00461b70
    L_00461b62:
        push dword ptr [ebp+14h]
    L_00461b65:
        mov eax,esi
    L_00461b67:
        call asm_strncnt_00461add
    L_00461b6c:
        pop ecx
    L_00461b6d:
        mov dword ptr [ebp+14h],eax
    L_00461b70:
        mov eax,dword ptr [ebp+1Ch]
    L_00461b73:
        cmp eax,edi
    L_00461b75:
        jle short L_00461b83
    L_00461b77:
        push eax
    L_00461b78:
        mov eax,ebx
    L_00461b7a:
        call asm_strncnt_00461add
    L_00461b7f:
        pop ecx
    L_00461b80:
        mov dword ptr [ebp+1Ch],eax
    L_00461b83:
        mov ecx,dword ptr [data_004776d4]
    L_00461b89:
        cmp ecx,2
    L_00461b8c:
        je asm_target_00461dc2
    L_00461b92:
        cmp ecx,edi
    L_00461b94:
        je asm_target_00461dc2
    L_00461b9a:
        xor edx,edx
    L_00461b9c:
        inc edx
    L_00461b9d:
        cmp ecx,edx
    L_00461b9f:
        jne asm_target_00461def
    L_00461ba5:
        mov dword ptr [ebp-50h],edi
    L_00461ba8:
        mov dword ptr [ebp-44h],edi
    L_00461bab:
        mov dword ptr [ebp-48h],edi
    L_00461bae:
        cmp dword ptr [ebp+20h],edi
    L_00461bb1:
        jne short L_00461bbc
    L_00461bb3:
        mov ecx,dword ptr [data_00477664]
    L_00461bb9:
        mov dword ptr [ebp+20h],ecx
    L_00461bbc:
        cmp dword ptr [ebp+14h],edi
    L_00461bbf:
        je short L_00461bc9
    L_00461bc1:
        cmp eax,edi
    L_00461bc3:
        jne asm_target_00461c65
    L_00461bc9:
        cmp dword ptr [ebp+14h],eax
    L_00461bcc:
        jne short L_00461bd6
    L_00461bce:
        push 2
    L_00461bd0:
        pop eax
    L_00461bd1:
        jmp asm_target_00461e70
    L_00461bd6:
        cmp eax,edx
    L_00461bd8:
        jle short L_00461be1
    L_00461bda:
        mov eax,edx
    L_00461bdc:
        jmp asm_target_00461e70
    L_00461be1:
        cmp dword ptr [ebp+14h],edx
    L_00461be4:
        jg short L_00461c27
    L_00461be6:
        lea eax,[ebp-30h]
    L_00461be9:
        push eax
    L_00461bea:
        push dword ptr [ebp+20h]
    L_00461bed:
        call dword ptr [data_00466064]
    L_00461bf3:
        test eax,eax
    L_00461bf5:
        je asm_target_00461def
    L_00461bfb:
        cmp dword ptr [ebp+14h],edi
    L_00461bfe:
        jle short L_00461c2b
    L_00461c00:
        cmp dword ptr [ebp-30h],2
    L_00461c04:
        jb short L_00461c27
    L_00461c06:
        lea eax,[ebp-2Ah]
    L_00461c09:
        cmp byte ptr [ebp-2Ah],0
    L_00461c0d:
        je short L_00461c27
    L_00461c0f:
        mov dl,byte ptr [eax+1]
    L_00461c12:
        test dl,dl
    L_00461c14:
        je short L_00461c27
    L_00461c16:
        mov cl,byte ptr [esi]
    L_00461c18:
        cmp cl,byte ptr [eax]
    L_00461c1a:
        jb short L_00461c20
    L_00461c1c:
        cmp cl,dl
    L_00461c1e:
        jbe short L_00461bce
    L_00461c20:
        inc eax
    L_00461c21:
        inc eax
    L_00461c22:
        cmp byte ptr [eax],0
    L_00461c25:
        jne short L_00461c0f
    L_00461c27:
        push 3
    L_00461c29:
        jmp short L_00461bd0
    L_00461c2b:
        cmp dword ptr [ebp+1Ch],edi
    L_00461c2e:
        jle short L_00461c65
    L_00461c30:
        cmp dword ptr [ebp-30h],2
    L_00461c34:
        jae short L_00461c3e
    L_00461c36:
        xor eax,eax
    L_00461c38:
        inc eax
    L_00461c39:
        jmp asm_target_00461e70
    L_00461c3e:
        lea eax,[ebp-2Ah]
    L_00461c41:
        cmp byte ptr [ebp-2Ah],0
    L_00461c45:
        je short L_00461c36
    L_00461c47:
        mov dl,byte ptr [eax+1]
    L_00461c4a:
        test dl,dl
    L_00461c4c:
        je short L_00461c36
    L_00461c4e:
        mov cl,byte ptr [ebx]
    L_00461c50:
        cmp cl,byte ptr [eax]
    L_00461c52:
        jb short L_00461c5c
    L_00461c54:
        cmp cl,dl
    L_00461c56:
        jbe asm_target_00461bce
    L_00461c5c:
        inc eax
    L_00461c5d:
        inc eax
    L_00461c5e:
        cmp byte ptr [eax],0
    L_00461c61:
        jne short L_00461c47
    L_00461c63:
        jmp short L_00461c36
    L_00461c65:
        push edi
    L_00461c66:
        push edi
    L_00461c67:
        push dword ptr [ebp+14h]
    L_00461c6a:
        push esi
    L_00461c6b:
        push 9
    L_00461c6d:
        push dword ptr [ebp+20h]
    L_00461c70:
        call dword ptr [data_00466104]
    L_00461c76:
        mov ebx,eax
    L_00461c78:
        mov dword ptr [ebp-4Ch],ebx
    L_00461c7b:
        cmp ebx,edi
    L_00461c7d:
        je asm_target_00461def
    L_00461c83:
        mov dword ptr [ebp-4],edi
    L_00461c86:
        lea eax,[ebx+ebx]
    L_00461c89:
        add eax,3
    L_00461c8c:
        and eax,0FFFFFFFCh
    L_00461c8f:
        call asm_chkstk_00458ec0
    L_00461c94:
        mov dword ptr [ebp-18h],esp
    L_00461c97:
        mov eax,esp
    L_00461c99:
        mov dword ptr [ebp-38h],eax
    L_00461c9c:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_00461ca0:
        TH10_REL8(0xeb, 0x00461ca0, VA_asm_FUN_00461af9_part_00461cbe)
    }
}

// 0x00461CBE..0x00461D3E: FUN_00461af9
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00461af9_part_00461cbe() {
    __asm {
    L_00461cbe:
        mov eax,dword ptr [ebp-38h]
    L_00461cc1:
        cmp eax,edi
    L_00461cc3:
        jne short L_00461ce1
    L_00461cc5:
        lea eax,[ebx+ebx]
    L_00461cc8:
        push eax
    L_00461cc9:
        call asm_malloc_00452706
    L_00461cce:
        pop ecx
    L_00461ccf:
        mov dword ptr [ebp-38h],eax
    L_00461cd2:
        cmp eax,edi
    L_00461cd4:
        je asm_target_00461def
    L_00461cda:
        mov dword ptr [ebp-50h],1
    L_00461ce1:
        push ebx
    L_00461ce2:
        push eax
    L_00461ce3:
        push dword ptr [ebp+14h]
    L_00461ce6:
        push esi
    L_00461ce7:
        push 1
    L_00461ce9:
        push dword ptr [ebp+20h]
    L_00461cec:
        call dword ptr [data_00466104]
    L_00461cf2:
        test eax,eax
    L_00461cf4:
        je asm_target_00461dab
    L_00461cfa:
        push 0
    L_00461cfc:
        push 0
    L_00461cfe:
        push dword ptr [ebp+1Ch]
    L_00461d01:
        push dword ptr [ebp-34h]
    L_00461d04:
        push 9
    L_00461d06:
        push dword ptr [ebp+20h]
    L_00461d09:
        call dword ptr [data_00466104]
    L_00461d0f:
        mov esi,eax
    L_00461d11:
        mov dword ptr [ebp-54h],esi
    L_00461d14:
        test esi,esi
    L_00461d16:
        je asm_target_00461dab
    L_00461d1c:
        mov dword ptr [ebp-4],1
    L_00461d23:
        lea eax,[esi+esi]
    L_00461d26:
        add eax,3
    L_00461d29:
        and eax,0FFFFFFFCh
    L_00461d2c:
        call asm_chkstk_00458ec0
    L_00461d31:
        mov dword ptr [ebp-18h],esp
    L_00461d34:
        mov edi,esp
    L_00461d36:
        mov dword ptr [ebp-58h],edi
    L_00461d39:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_00461d3d:
        TH10_REL8(0xeb, 0x00461d3d, VA_asm_FUN_00461af9_part_00461d57)
    }
}

// 0x00461D57..0x00461E82: FUN_00461af9
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00461af9_part_00461d57() {
    __asm {
    L_00461d57:
        test edi,edi
    L_00461d59:
        jne short L_00461d72
    L_00461d5b:
        lea eax,[esi+esi]
    L_00461d5e:
        push eax
    L_00461d5f:
        call asm_malloc_00452706
    L_00461d64:
        pop ecx
    L_00461d65:
        mov edi,eax
    L_00461d67:
        test edi,edi
    L_00461d69:
        je short L_00461dab
    L_00461d6b:
        mov dword ptr [ebp-44h],1
    L_00461d72:
        push esi
    L_00461d73:
        push edi
    L_00461d74:
        push dword ptr [ebp+1Ch]
    L_00461d77:
        push dword ptr [ebp-34h]
    L_00461d7a:
        push 1
    L_00461d7c:
        push dword ptr [ebp+20h]
    L_00461d7f:
        call dword ptr [data_00466104]
    L_00461d85:
        test eax,eax
    L_00461d87:
        je short L_00461d9e
    L_00461d89:
        push esi
    L_00461d8a:
        push edi
    L_00461d8b:
        push ebx
    L_00461d8c:
        push dword ptr [ebp-38h]
    L_00461d8f:
        push dword ptr [ebp+0Ch]
    L_00461d92:
        push dword ptr [ebp+8]
    L_00461d95:
        call dword ptr [data_004661d0]
    L_00461d9b:
        mov dword ptr [ebp-48h],eax
    L_00461d9e:
        cmp dword ptr [ebp-44h],0
    L_00461da2:
        je short L_00461dab
    L_00461da4:
        push edi
    L_00461da5:
        call asm_free_00452422
    L_00461daa:
        pop ecx
    L_00461dab:
        cmp dword ptr [ebp-50h],0
    L_00461daf:
        je short L_00461dba
    L_00461db1:
        push dword ptr [ebp-38h]
    L_00461db4:
        call asm_free_00452422
    L_00461db9:
        pop ecx
    L_00461dba:
        mov eax,dword ptr [ebp-48h]
    L_00461dbd:
        jmp asm_target_00461e70
    L_00461dc2:
        mov dword ptr [ebp-40h],edi
    L_00461dc5:
        cmp dword ptr [ebp+8],edi
    L_00461dc8:
        jne short L_00461dd2
    L_00461dca:
        mov eax,dword ptr [data_00477654]
    L_00461dcf:
        mov dword ptr [ebp+8],eax
    L_00461dd2:
        mov ebx,dword ptr [ebp+20h]
    L_00461dd5:
        cmp ebx,edi
    L_00461dd7:
        jne short L_00461ddf
    L_00461dd9:
        mov ebx,dword ptr [data_00477664]
    L_00461ddf:
        push dword ptr [ebp+8]
    L_00461de2:
        call asm_FUN_004601a1_004601a1
    L_00461de7:
        pop ecx
    L_00461de8:
        mov esi,eax
    L_00461dea:
        cmp esi,0FFFFFFFFh
    L_00461ded:
        jne short L_00461df3
    L_00461def:
        xor eax,eax
    L_00461df1:
        jmp short L_00461e70
    L_00461df3:
        cmp esi,ebx
    L_00461df5:
        je short L_00461e40
    L_00461df7:
        push 0
    L_00461df9:
        push 0
    L_00461dfb:
        lea eax,[ebp+14h]
    L_00461dfe:
        push eax
    L_00461dff:
        push dword ptr [ebp-3Ch]
    L_00461e02:
        push esi
    L_00461e03:
        push ebx
    L_00461e04:
        call asm_FUN_004601e8_004601e8
    L_00461e09:
        add esp,18h
    L_00461e0c:
        mov edi,eax
    L_00461e0e:
        test edi,edi
    L_00461e10:
        je short L_00461def
    L_00461e12:
        push 0
    L_00461e14:
        push 0
    L_00461e16:
        lea eax,[ebp+1Ch]
    L_00461e19:
        push eax
    L_00461e1a:
        push dword ptr [ebp-34h]
    L_00461e1d:
        push esi
    L_00461e1e:
        push ebx
    L_00461e1f:
        call asm_FUN_004601e8_004601e8
    L_00461e24:
        add esp,18h
    L_00461e27:
        mov dword ptr [ebp-40h],eax
    L_00461e2a:
        test eax,eax
    L_00461e2c:
        jne short L_00461e37
    L_00461e2e:
        push edi
    L_00461e2f:
        call asm_free_00452422
    L_00461e34:
        pop ecx
    L_00461e35:
        jmp short L_00461def
    L_00461e37:
        mov dword ptr [ebp-3Ch],edi
    L_00461e3a:
        mov eax,dword ptr [ebp-40h]
    L_00461e3d:
        mov dword ptr [ebp-34h],eax
    L_00461e40:
        push dword ptr [ebp+1Ch]
    L_00461e43:
        push dword ptr [ebp-34h]
    L_00461e46:
        push dword ptr [ebp+14h]
    L_00461e49:
        push dword ptr [ebp-3Ch]
    L_00461e4c:
        push dword ptr [ebp+0Ch]
    L_00461e4f:
        push dword ptr [ebp+8]
    L_00461e52:
        call dword ptr [data_004661cc]
    L_00461e58:
        mov esi,eax
    L_00461e5a:
        test edi,edi
    L_00461e5c:
        je short L_00461e6e
    L_00461e5e:
        push edi
    L_00461e5f:
        call asm_free_00452422
    L_00461e64:
        push dword ptr [ebp-40h]
    L_00461e67:
        call asm_free_00452422
    L_00461e6c:
        pop ecx
    L_00461e6d:
        pop ecx
    L_00461e6e:
        mov eax,esi
    L_00461e70:
        lea esp,[ebp-64h]
    L_00461e73:
        mov ecx,dword ptr [ebp-1Ch]
    L_00461e76:
        xor ecx,ebp
    L_00461e78:
        call asm_security_check_cookie_00458ea5
    L_00461e7d:
        call asm_SEH_epilog_00454bf7
    L_00461e82:
        ret
    }
}
