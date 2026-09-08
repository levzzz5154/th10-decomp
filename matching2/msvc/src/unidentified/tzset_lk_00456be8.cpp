#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00456BE8..0x00456DFD: __tzset_lk
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_tzset_lk_00456be8() {
    __asm {
    L_00456be8:
        push 18h
    L_00456bea:
        push 46AAB0h
    L_00456bef:
        call asm_SEH_prolog_00454bbc
    L_00456bf4:
        xor edi,edi
    L_00456bf6:
        mov dword ptr [ebp-20h],edi
    L_00456bf9:
        push 7
    L_00456bfb:
        call asm_lock_00453c0c
    L_00456c00:
        pop ecx
    L_00456c01:
        mov dword ptr [ebp-4],edi
    L_00456c04:
        mov ebx,dword ptr [data_00477664]
    L_00456c0a:
        mov dword ptr [ebp-28h],ebx
    L_00456c0d:
        mov dword ptr [data_0047743c],edi
    L_00456c13:
        or dword ptr [data_004735c4],0FFFFFFFFh
    L_00456c1a:
        or dword ptr [data_004735b8],0FFFFFFFFh
    L_00456c21:
        push 46AAACh
    L_00456c26:
        call asm_getenv_lk_0045e063
    L_00456c2b:
        pop ecx
    L_00456c2c:
        mov esi,eax
    L_00456c2e:
        mov dword ptr [ebp-24h],esi
    L_00456c31:
        cmp esi,edi
    L_00456c33:
        je asm_target_00456cf1
    L_00456c39:
        cmp byte ptr [esi],0
    L_00456c3c:
        je asm_target_00456cf1
    L_00456c42:
        mov eax,dword ptr [data_00477440]
    L_00456c47:
        cmp eax,edi
    L_00456c49:
        je short L_00456c6c
    L_00456c4b:
        push eax
    L_00456c4c:
        push esi
    L_00456c4d:
        call asm_strcmp_0045bf30
    L_00456c52:
        pop ecx
    L_00456c53:
        pop ecx
    L_00456c54:
        test eax,eax
    L_00456c56:
        je asm_target_00456dec
    L_00456c5c:
        mov eax,dword ptr [data_00477440]
    L_00456c61:
        cmp eax,edi
    L_00456c63:
        je short L_00456c6c
    L_00456c65:
        push eax
    L_00456c66:
        call asm_free_00452422
    L_00456c6b:
        pop ecx
    L_00456c6c:
        push esi
    L_00456c6d:
        call asm_strlen_00456720
    L_00456c72:
        inc eax
    L_00456c73:
        push eax
    L_00456c74:
        call asm_malloc_00452706
    L_00456c79:
        pop ecx
    L_00456c7a:
        pop ecx
    L_00456c7b:
        mov dword ptr [data_00477440],eax
    L_00456c80:
        cmp eax,edi
    L_00456c82:
        je asm_target_00456dec
    L_00456c88:
        push esi
    L_00456c89:
        push eax
    L_00456c8a:
        call asm_FUN_0045bd80_0045bd80
    L_00456c8f:
        pop ecx
    L_00456c90:
        pop ecx
    L_00456c91:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_00456c95:
        call asm_FUN_00456e03_00456e03
    L_00456c9a:
        push 3
    L_00456c9c:
        push esi
    L_00456c9d:
        push dword ptr [data_004735b0]
    L_00456ca3:
        call asm_strncpy_00452960
    L_00456ca8:
        add esp,0Ch
    L_00456cab:
        mov eax,dword ptr [data_004735b0]
    L_00456cb0:
        mov byte ptr [eax+3],0
    L_00456cb4:
        add esi,3
    L_00456cb7:
        cmp byte ptr [esi],2Dh
    L_00456cba:
        jne short L_00456cc4
    L_00456cbc:
        mov dword ptr [ebp-20h],1
    L_00456cc3:
        inc esi
    L_00456cc4:
        push esi
    L_00456cc5:
        call asm_atol_004527ee
    L_00456cca:
        pop ecx
    L_00456ccb:
        imul eax,0E10h
    L_00456cd1:
        mov dword ptr [data_00473520],eax
    L_00456cd6:
        mov bl,30h
    L_00456cd8:
        mov al,byte ptr [esi]
    L_00456cda:
        cmp al,2Bh
    L_00456cdc:
        je short L_00456cee
    L_00456cde:
        cmp al,bl
    L_00456ce0:
        jl asm_tzset_lk_part_00456e0c
    L_00456ce6:
        cmp al,39h
    L_00456ce8:
        jg asm_tzset_lk_part_00456e0c
    L_00456cee:
        inc esi
    L_00456cef:
        jmp short L_00456cd8
    L_00456cf1:
        mov eax,dword ptr [data_00477440]
    L_00456cf6:
        cmp eax,edi
    L_00456cf8:
        je short L_00456d07
    L_00456cfa:
        push eax
    L_00456cfb:
        call asm_free_00452422
    L_00456d00:
        pop ecx
    L_00456d01:
        mov dword ptr [data_00477440],edi
    L_00456d07:
        push 477390h
    L_00456d0c:
        call dword ptr [data_00466150]
    L_00456d12:
        cmp eax,0FFFFFFFFh
    L_00456d15:
        je asm_target_00456dec
    L_00456d1b:
        xor ecx,ecx
    L_00456d1d:
        inc ecx
    L_00456d1e:
        mov dword ptr [data_0047743c],ecx
    L_00456d24:
        mov eax,dword ptr [data_00477390]
    L_00456d29:
        imul eax,3Ch
    L_00456d2c:
        mov dword ptr [data_00473520],eax
    L_00456d31:
        cmp word ptr [data_004773d6],di
    L_00456d38:
        je short L_00456d4a
    L_00456d3a:
        mov edx,dword ptr [data_004773e4]
    L_00456d40:
        imul edx,3Ch
    L_00456d43:
        add eax,edx
    L_00456d45:
        mov dword ptr [data_00473520],eax
    L_00456d4a:
        cmp word ptr [data_0047742a],di
    L_00456d51:
        je short L_00456d72
    L_00456d53:
        mov eax,dword ptr [data_00477438]
    L_00456d58:
        cmp eax,edi
    L_00456d5a:
        je short L_00456d72
    L_00456d5c:
        mov dword ptr [data_00473524],ecx
    L_00456d62:
        sub eax,dword ptr [data_004773e4]
    L_00456d68:
        imul eax,3Ch
    L_00456d6b:
        mov dword ptr [data_00473528],eax
    L_00456d70:
        jmp short L_00456d7e
    L_00456d72:
        mov dword ptr [data_00473524],edi
    L_00456d78:
        mov dword ptr [data_00473528],edi
    L_00456d7e:
        lea eax,[ebp-1Ch]
    L_00456d81:
        push eax
    L_00456d82:
        push edi
    L_00456d83:
        push 3Fh
    L_00456d85:
        push dword ptr [data_004735b0]
    L_00456d8b:
        push 0FFFFFFFFh
    L_00456d8d:
        push 477394h
    L_00456d92:
        push edi
    L_00456d93:
        push ebx
    L_00456d94:
        mov esi,dword ptr [data_00466154]
    L_00456d9a:
        call esi
    L_00456d9c:
        test eax,eax
    L_00456d9e:
        je short L_00456db0
    L_00456da0:
        cmp dword ptr [ebp-1Ch],edi
    L_00456da3:
        jne short L_00456db0
    L_00456da5:
        mov eax,dword ptr [data_004735b0]
    L_00456daa:
        mov byte ptr [eax+3Fh],0
    L_00456dae:
        jmp short L_00456db8
    L_00456db0:
        mov eax,dword ptr [data_004735b0]
    L_00456db5:
        mov byte ptr [eax],0
    L_00456db8:
        lea eax,[ebp-1Ch]
    L_00456dbb:
        push eax
    L_00456dbc:
        push edi
    L_00456dbd:
        push 3Fh
    L_00456dbf:
        push dword ptr [data_004735b4]
    L_00456dc5:
        push 0FFFFFFFFh
    L_00456dc7:
        push 4773E8h
    L_00456dcc:
        push edi
    L_00456dcd:
        push ebx
    L_00456dce:
        call esi
    L_00456dd0:
        test eax,eax
    L_00456dd2:
        je short L_00456de4
    L_00456dd4:
        cmp dword ptr [ebp-1Ch],edi
    L_00456dd7:
        jne short L_00456de4
    L_00456dd9:
        mov eax,dword ptr [data_004735b4]
    L_00456dde:
        mov byte ptr [eax+3Fh],0
    L_00456de2:
        jmp short L_00456dec
    L_00456de4:
        mov eax,dword ptr [data_004735b4]
    L_00456de9:
        mov byte ptr [eax],0
    L_00456dec:
        push 0FFFFFFFFh
    L_00456dee:
        lea eax,[ebp-10h]
    L_00456df1:
        push eax
    L_00456df2:
        call asm_local_unwind2_004598de
    L_00456df7:
        pop ecx
    L_00456df8:
        pop ecx
    L_00456df9:
        jmp asm_target_00456e8a
    }
}

// 0x00456E0C..0x00456E8F: __tzset_lk
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_tzset_lk_part_00456e0c() {
    __asm {
    L_00456e0c:
        cmp byte ptr [esi],3Ah
    L_00456e0f:
        jne short L_00456e4f
    L_00456e11:
        inc esi
    L_00456e12:
        push esi
    L_00456e13:
        call asm_atol_004527ee
    L_00456e18:
        pop ecx
    L_00456e19:
        imul eax,3Ch
    L_00456e1c:
        add dword ptr [data_00473520],eax
    L_00456e22:
        jmp short L_00456e29
    L_00456e24:
        cmp al,39h
    L_00456e26:
        jg short L_00456e2f
    L_00456e28:
        inc esi
    L_00456e29:
        mov al,byte ptr [esi]
    L_00456e2b:
        cmp al,bl
    L_00456e2d:
        jge short L_00456e24
    L_00456e2f:
        cmp byte ptr [esi],3Ah
    L_00456e32:
        jne short L_00456e4f
    L_00456e34:
        inc esi
    L_00456e35:
        push esi
    L_00456e36:
        call asm_atol_004527ee
    L_00456e3b:
        pop ecx
    L_00456e3c:
        add dword ptr [data_00473520],eax
    L_00456e42:
        jmp short L_00456e49
    L_00456e44:
        cmp al,39h
    L_00456e46:
        jg short L_00456e4f
    L_00456e48:
        inc esi
    L_00456e49:
        mov al,byte ptr [esi]
    L_00456e4b:
        cmp al,bl
    L_00456e4d:
        jge short L_00456e44
    L_00456e4f:
        cmp dword ptr [ebp-20h],edi
    L_00456e52:
        je short L_00456e5a
    L_00456e54:
        neg dword ptr [data_00473520]
    L_00456e5a:
        movsx eax,byte ptr [esi]
    L_00456e5d:
        mov dword ptr [data_00473524],eax
    L_00456e62:
        cmp eax,edi
    L_00456e64:
        je short L_00456e82
    L_00456e66:
        push 3
    L_00456e68:
        push esi
    L_00456e69:
        push dword ptr [data_004735b4]
    L_00456e6f:
        call asm_strncpy_00452960
    L_00456e74:
        add esp,0Ch
    L_00456e77:
        mov eax,dword ptr [data_004735b4]
    L_00456e7c:
        mov byte ptr [eax+3],0
    L_00456e80:
        jmp short L_00456e8a
    L_00456e82:
        mov eax,dword ptr [data_004735b4]
    L_00456e87:
        mov byte ptr [eax],0
    L_00456e8a:
        call asm_SEH_epilog_00454bf7
    L_00456e8f:
        ret
    }
}
