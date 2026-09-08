#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00403A30..0x00403A8C: FUN_00403a30
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00403a30_00403a30() {
    __asm {
    L_00403a30:
        sub esp,0Ch
    L_00403a33:
        push ebx
    L_00403a34:
        push ebp
    L_00403a35:
        mov ebp,dword ptr [esp+18h]
    L_00403a39:
        mov ebx,dword ptr [ebp+18h]
    L_00403a3c:
        push edi
    L_00403a3d:
        mov edi,491D7Ch
    L_00403a42:
        mov dword ptr [data_00491fac],edi
    L_00403a48:
        call asm_FUN_004215a0_004215a0
    L_00403a4d:
        mov edx,dword ptr [data_00491fac]
    L_00403a53:
        mov eax,dword ptr [data_00491c30]
    L_00403a58:
        mov ecx,dword ptr [eax]
    L_00403a5a:
        add edx,0CCh
    L_00403a60:
        push edx
    L_00403a61:
        push eax
    L_00403a62:
        call dword ptr [ecx+0BCh]
    L_00403a68:
        mov eax,dword ptr [data_00491c10]
    L_00403a6d:
        mov dword ptr [data_00491fb0],0
    L_00403a77:
        mov byte ptr [eax+3ADA6Ch],1
    L_00403a7e:
        mov ax,word ptr [ebx]
    L_00403a81:
        test ax,ax
    L_00403a84:
        jl asm_target_00403c75
    L_00403a8a:
        push esi
    L_00403a8b:
        TH10_REL8(0xeb, 0x00403a8b, VA_asm_FUN_00403a30_part_00403a90)
    }
}

// 0x00403A90..0x00403AFC: FUN_00403a30
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00403a30_part_00403a90() {
    __asm {
    L_00403a90:
        mov edx,dword ptr [ebp+14h]
    L_00403a93:
        movsx ecx,ax
    L_00403a96:
        mov esi,dword ptr [edx+ecx*4]
    L_00403a99:
        movsx eax,byte ptr [esi+2]
    L_00403a9d:
        cmp eax,dword ptr [esp+24h]
    L_00403aa1:
        jne asm_target_00403c64
    L_00403aa7:
        mov ecx,dword ptr [ebx+4]
    L_00403aaa:
        mov edx,dword ptr [ebx+8]
    L_00403aad:
        mov eax,dword ptr [ebx+0Ch]
    L_00403ab0:
        mov dword ptr [esp+10h],ecx
    L_00403ab4:
        mov ecx,dword ptr [ebp+1EE0h]
    L_00403aba:
        mov dword ptr [esp+14h],edx
    L_00403abe:
        mov dword ptr [esp+18h],eax
    L_00403ac2:
        push ecx
    L_00403ac3:
        mov eax,491D7Ch
    L_00403ac8:
        lea edx,[esp+14h]
    L_00403acc:
        mov ecx,esi
    L_00403ace:
        call asm_FUN_00403090_00403090
    L_00403ad3:
        test eax,eax
    L_00403ad5:
        je short L_00403ae2
    L_00403ad7:
        inc dword ptr [ebp+2A10h]
    L_00403add:
        jmp asm_target_00403c64
    L_00403ae2:
        mov dl,byte ptr [esi+3]
    L_00403ae5:
        or dl,2
    L_00403ae8:
        lea ebp,[esi+1Ch]
    L_00403aeb:
        mov byte ptr [esi+3],dl
    L_00403aee:
        mov ax,word ptr [ebp]
    L_00403af2:
        test ax,ax
    L_00403af5:
        jl asm_target_00403c4f
    L_00403afb:
        TH10_REL8(0xeb, 0x00403afb, VA_asm_FUN_00403a30_part_00403b00)
    }
}

// 0x00403B00..0x00403C7F: FUN_00403a30
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00403a30_part_00403b00() {
    __asm {
    L_00403b00:
        movsx edi,word ptr [ebp+6]
    L_00403b04:
        mov esi,dword ptr [esp+20h]
    L_00403b08:
        imul edi,3ACh
    L_00403b0e:
        add edi,dword ptr [esi+17Ch]
    L_00403b14:
        test ax,ax
    L_00403b17:
        jne asm_target_00403c3a
    L_00403b1d:
        mov ecx,dword ptr [edi+35Ch]
    L_00403b23:
        mov edx,ecx
    L_00403b25:
        and edx,3C00000h
    L_00403b2b:
        cmp edx,1000000h
    L_00403b31:
        jb short L_00403bb1
    L_00403b33:
        fld dword ptr [ebp+8]
    L_00403b36:
        fadd dword ptr [ebx+4]
    L_00403b39:
        fstp dword ptr [edi+340h]
    L_00403b3f:
        fld dword ptr [ebp+0Ch]
    L_00403b42:
        fadd dword ptr [ebx+8]
    L_00403b45:
        fstp dword ptr [edi+344h]
    L_00403b4b:
        fld dword ptr [ebp+10h]
    L_00403b4e:
        fadd dword ptr [ebx+0Ch]
    L_00403b51:
        fstp dword ptr [edi+348h]
    L_00403b57:
        fld dword ptr [data_00470b04]
    L_00403b5d:
        fld dword ptr [ebp+14h]
    L_00403b60:
        fucompp
    L_00403b62:
        fnstsw ax
    L_00403b64:
        test ah,44h
    L_00403b67:
        jnp short L_00403b81
    L_00403b69:
        fld dword ptr [ebp+14h]
    L_00403b6c:
        mov eax,dword ptr [edi+394h]
    L_00403b72:
        fdiv dword ptr [eax+34h]
    L_00403b75:
        or ecx,8
    L_00403b78:
        mov dword ptr [edi+35Ch],ecx
    L_00403b7e:
        fstp dword ptr [edi+3Ch]
    L_00403b81:
        fld dword ptr [data_00470b04]
    L_00403b87:
        fld dword ptr [ebp+18h]
    L_00403b8a:
        fucompp
    L_00403b8c:
        fnstsw ax
    L_00403b8e:
        test ah,44h
    L_00403b91:
        jnp short L_00403bb1
    L_00403b93:
        fld dword ptr [ebp+18h]
    L_00403b96:
        mov ecx,dword ptr [edi+394h]
    L_00403b9c:
        fdiv dword ptr [ecx+30h]
    L_00403b9f:
        mov eax,dword ptr [edi+35Ch]
    L_00403ba5:
        or eax,8
    L_00403ba8:
        mov dword ptr [edi+35Ch],eax
    L_00403bae:
        fstp dword ptr [edi+40h]
    L_00403bb1:
        mov edx,dword ptr [edi+35Ch]
    L_00403bb7:
        mov eax,dword ptr [data_00492378]
    L_00403bbc:
        and edx,3C00000h
    L_00403bc2:
        cmp edx,2000000h
    L_00403bc8:
        jne short L_00403bf8
    L_00403bca:
        cmp eax,1
    L_00403bcd:
        je short L_00403c27
    L_00403bcf:
        mov esi,dword ptr [data_00491c10]
    L_00403bd5:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00403bda:
        mov eax,dword ptr [data_00491c30]
    L_00403bdf:
        push 1
    L_00403be1:
        push 1Ch
    L_00403be3:
        mov dword ptr [data_00492378],1
    L_00403bed:
        mov ecx,dword ptr [eax]
    L_00403bef:
        push eax
    L_00403bf0:
        call dword ptr [ecx+0E4h]
    L_00403bf6:
        jmp short L_00403c23
    L_00403bf8:
        test eax,eax
    L_00403bfa:
        je short L_00403c27
    L_00403bfc:
        mov esi,dword ptr [data_00491c10]
    L_00403c02:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00403c07:
        mov eax,dword ptr [data_00491c30]
    L_00403c0c:
        push 0
    L_00403c0e:
        push 1Ch
    L_00403c10:
        mov dword ptr [data_00492378],0
    L_00403c1a:
        mov edx,dword ptr [eax]
    L_00403c1c:
        push eax
    L_00403c1d:
        call dword ptr [edx+0E4h]
    L_00403c23:
        mov esi,dword ptr [esp+20h]
    L_00403c27:
        mov ecx,dword ptr [data_00491c10]
    L_00403c2d:
        mov eax,edi
    L_00403c2f:
        call asm_FUN_004451c0_004451c0
    L_00403c34:
        inc dword ptr [esi+2A14h]
    L_00403c3a:
        movsx eax,word ptr [ebp+2]
    L_00403c3e:
        add ebp,eax
    L_00403c40:
        mov ax,word ptr [ebp]
    L_00403c44:
        test ax,ax
    L_00403c47:
        jge asm_FUN_00403a30_part_00403b00
    L_00403c4d:
        jmp short L_00403c53
    L_00403c4f:
        mov esi,dword ptr [esp+20h]
    L_00403c53:
        mov eax,dword ptr [esi+2A0Ch]
    L_00403c59:
        mov ebp,dword ptr [esp+20h]
    L_00403c5d:
        inc eax
    L_00403c5e:
        mov dword ptr [esi+2A0Ch],eax
    L_00403c64:
        mov ax,word ptr [ebx+10h]
    L_00403c68:
        add ebx,10h
    L_00403c6b:
        test ax,ax
    L_00403c6e:
        jge asm_FUN_00403a30_part_00403a90
    L_00403c74:
        pop esi
    L_00403c75:
        pop edi
    L_00403c76:
        pop ebp
    L_00403c77:
        xor eax,eax
    L_00403c79:
        pop ebx
    L_00403c7a:
        add esp,0Ch
    L_00403c7d:
        ret 8
    }
}
