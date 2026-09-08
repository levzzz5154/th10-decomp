#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00457A7C..0x00458219: FUN_00457a7c
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00457a7c_00457a7c() {
    __asm {
    L_00457a7c:
        push 1D8h
    L_00457a81:
        push 46AB48h
    L_00457a86:
        call asm_SEH_prolog_00454bbc
    L_00457a8b:
        mov eax,dword ptr [data_00473660]
    L_00457a90:
        xor eax,ebp
    L_00457a92:
        mov dword ptr [ebp-1Ch],eax
    L_00457a95:
        mov eax,dword ptr [ebp+8]
    L_00457a98:
        mov dword ptr [ebp-194h],eax
    L_00457a9e:
        mov edi,dword ptr [ebp+0Ch]
    L_00457aa1:
        mov dword ptr [ebp-19Ch],edi
    L_00457aa7:
        mov eax,dword ptr [ebp+10h]
    L_00457aaa:
        mov dword ptr [ebp-1D4h],eax
    L_00457ab0:
        xor eax,eax
    L_00457ab2:
        mov dword ptr [ebp-1C8h],eax
    L_00457ab8:
        mov dword ptr [ebp-1E4h],eax
    L_00457abe:
        mov dword ptr [ebp-1B8h],eax
    L_00457ac4:
        mov dword ptr [ebp-190h],eax
    L_00457aca:
        mov byte ptr [ebp-195h],al
    L_00457ad0:
        mov dword ptr [ebp-184h],eax
    L_00457ad6:
        mov dword ptr [ebp-1C0h],eax
    L_00457adc:
        jmp short L_00457ae4
    L_00457ade:
        mov edi,dword ptr [ebp-19Ch]
    L_00457ae4:
        mov al,byte ptr [edi]
    L_00457ae6:
        test al,al
    L_00457ae8:
        je asm_target_0045885e
    L_00457aee:
        movzx eax,al
    L_00457af1:
        push eax
    L_00457af2:
        call asm_isspace_004568d7
    L_00457af7:
        pop ecx
    L_00457af8:
        test eax,eax
    L_00457afa:
        je short L_00457b50
    L_00457afc:
        dec dword ptr [ebp-184h]
    L_00457b02:
        inc dword ptr [ebp-184h]
    L_00457b08:
        mov edx,dword ptr [ebp-194h]
    L_00457b0e:
        call asm_inc_00457a3c
    L_00457b13:
        mov esi,eax
    L_00457b15:
        push esi
    L_00457b16:
        call asm_isspace_004568d7
    L_00457b1b:
        pop ecx
    L_00457b1c:
        test eax,eax
    L_00457b1e:
        jne short L_00457b02
    L_00457b20:
        cmp esi,0FFFFFFFFh
    L_00457b23:
        je short L_00457b33
    L_00457b25:
        push dword ptr [ebp-194h]
    L_00457b2b:
        push esi
    L_00457b2c:
        call asm_FID_conflict__ungetc_0045e204
    L_00457b31:
        pop ecx
    L_00457b32:
        pop ecx
    L_00457b33:
        mov edi,dword ptr [ebp-19Ch]
    L_00457b39:
        inc edi
    L_00457b3a:
        movzx eax,byte ptr [edi]
    L_00457b3d:
        push eax
    L_00457b3e:
        call asm_isspace_004568d7
    L_00457b43:
        pop ecx
    L_00457b44:
        test eax,eax
    L_00457b46:
        jne short L_00457b39
    L_00457b48:
        mov dword ptr [ebp-19Ch],edi
    L_00457b4e:
        jmp short L_00457ae4
    L_00457b50:
        mov edi,dword ptr [ebp-19Ch]
    L_00457b56:
        cmp byte ptr [edi],25h
    L_00457b59:
        jne asm_target_004587b3
    L_00457b5f:
        xor esi,esi
    L_00457b61:
        mov dword ptr [ebp-1A8h],esi
    L_00457b67:
        mov byte ptr [ebp-1A1h],0
    L_00457b6e:
        mov dword ptr [ebp-1A0h],esi
    L_00457b74:
        mov dword ptr [ebp-1BCh],esi
    L_00457b7a:
        mov dword ptr [ebp-188h],esi
    L_00457b80:
        mov byte ptr [ebp-1B1h],0
    L_00457b87:
        mov byte ptr [ebp-197h],0
    L_00457b8e:
        mov byte ptr [ebp-18Ah],0
    L_00457b95:
        mov byte ptr [ebp-17Dh],0
    L_00457b9c:
        mov byte ptr [ebp-196h],0
    L_00457ba3:
        mov byte ptr [ebp-189h],0
    L_00457baa:
        mov byte ptr [ebp-18Bh],1
    L_00457bb1:
        mov dword ptr [ebp-1D0h],esi
    L_00457bb7:
        inc edi
    L_00457bb8:
        movzx ebx,byte ptr [edi]
    L_00457bbb:
        movzx eax,bl
    L_00457bbe:
        push eax
    L_00457bbf:
        call asm_isdigit_0045685e
    L_00457bc4:
        pop ecx
    L_00457bc5:
        test eax,eax
    L_00457bc7:
        je short L_00457bdb
    L_00457bc9:
        inc dword ptr [ebp-1BCh]
    L_00457bcf:
        lea eax,[esi+esi*4]
    L_00457bd2:
        lea esi,[ebx+eax*2-30h]
    L_00457bd6:
        jmp asm_target_00457c9a
    L_00457bdb:
        cmp ebx,4Eh
    L_00457bde:
        jg asm_target_00457c69
    L_00457be4:
        je asm_target_00457c9a
    L_00457bea:
        cmp ebx,2Ah
    L_00457bed:
        je short L_00457c61
    L_00457bef:
        cmp ebx,46h
    L_00457bf2:
        je asm_target_00457c9a
    L_00457bf8:
        cmp ebx,49h
    L_00457bfb:
        je short L_00457c0d
    L_00457bfd:
        cmp ebx,4Ch
    L_00457c00:
        jne short L_00457c78
    L_00457c02:
        inc byte ptr [ebp-18Bh]
    L_00457c08:
        jmp asm_target_00457c9a
    L_00457c0d:
        mov cl,byte ptr [edi+1]
    L_00457c10:
        cmp cl,36h
    L_00457c13:
        jne short L_00457c35
    L_00457c15:
        lea eax,[edi+2]
    L_00457c18:
        cmp byte ptr [eax],34h
    L_00457c1b:
        jne short L_00457c35
    L_00457c1d:
        mov edi,eax
    L_00457c1f:
        inc dword ptr [ebp-1D0h]
    L_00457c25:
        and dword ptr [ebp-1B0h],0
    L_00457c2c:
        and dword ptr [ebp-1ACh],0
    L_00457c33:
        jmp short L_00457c9a
    L_00457c35:
        cmp cl,33h
    L_00457c38:
        jne short L_00457c46
    L_00457c3a:
        lea eax,[edi+2]
    L_00457c3d:
        cmp byte ptr [eax],32h
    L_00457c40:
        jne short L_00457c46
    L_00457c42:
        mov edi,eax
    L_00457c44:
        jmp short L_00457c9a
    L_00457c46:
        cmp cl,64h
    L_00457c49:
        je short L_00457c9a
    L_00457c4b:
        cmp cl,69h
    L_00457c4e:
        je short L_00457c9a
    L_00457c50:
        cmp cl,6Fh
    L_00457c53:
        je short L_00457c9a
    L_00457c55:
        cmp cl,78h
    L_00457c58:
        je short L_00457c9a
    L_00457c5a:
        cmp cl,58h
    L_00457c5d:
        jne short L_00457c78
    L_00457c5f:
        jmp short L_00457c9a
    L_00457c61:
        inc byte ptr [ebp-18Ah]
    L_00457c67:
        jmp short L_00457c9a
    L_00457c69:
        cmp ebx,68h
    L_00457c6c:
        je short L_00457c8e
    L_00457c6e:
        cmp ebx,6Ch
    L_00457c71:
        je short L_00457c80
    L_00457c73:
        cmp ebx,77h
    L_00457c76:
        je short L_00457c86
    L_00457c78:
        inc byte ptr [ebp-17Dh]
    L_00457c7e:
        jmp short L_00457c9a
    L_00457c80:
        inc byte ptr [ebp-18Bh]
    L_00457c86:
        inc byte ptr [ebp-189h]
    L_00457c8c:
        jmp short L_00457c9a
    L_00457c8e:
        dec byte ptr [ebp-18Bh]
    L_00457c94:
        dec byte ptr [ebp-189h]
    L_00457c9a:
        cmp byte ptr [ebp-17Dh],0
    L_00457ca1:
        je asm_target_00457bb7
    L_00457ca7:
        mov dword ptr [ebp-188h],esi
    L_00457cad:
        mov dword ptr [ebp-19Ch],edi
    L_00457cb3:
        cmp byte ptr [ebp-18Ah],0
    L_00457cba:
        jne short L_00457cdc
    L_00457cbc:
        mov eax,dword ptr [ebp-1D4h]
    L_00457cc2:
        mov dword ptr [ebp-1E8h],eax
    L_00457cc8:
        add eax,4
    L_00457ccb:
        mov dword ptr [ebp-1D4h],eax
    L_00457cd1:
        mov ebx,dword ptr [eax-4]
    L_00457cd4:
        mov dword ptr [ebp-1B8h],ebx
    L_00457cda:
        jmp short L_00457ce2
    L_00457cdc:
        mov ebx,dword ptr [ebp-1B8h]
    L_00457ce2:
        mov byte ptr [ebp-17Dh],0
    L_00457ce9:
        cmp byte ptr [ebp-189h],0
    L_00457cf0:
        jne short L_00457d0a
    L_00457cf2:
        mov al,byte ptr [edi]
    L_00457cf4:
        cmp al,53h
    L_00457cf6:
        je short L_00457d03
    L_00457cf8:
        cmp al,43h
    L_00457cfa:
        mov byte ptr [ebp-189h],0FFh
    L_00457d01:
        jne short L_00457d0a
    L_00457d03:
        mov byte ptr [ebp-189h],1
    L_00457d0a:
        movzx esi,byte ptr [edi]
    L_00457d0d:
        or esi,20h
    L_00457d10:
        mov dword ptr [ebp-1C4h],esi
    L_00457d16:
        cmp esi,6Eh
    L_00457d19:
        je short L_00457d68
    L_00457d1b:
        cmp esi,63h
    L_00457d1e:
        je short L_00457d51
    L_00457d20:
        cmp esi,7Bh
    L_00457d23:
        je short L_00457d51
    L_00457d25:
        inc dword ptr [ebp-184h]
    L_00457d2b:
        mov edx,dword ptr [ebp-194h]
    L_00457d31:
        call asm_inc_00457a3c
    L_00457d36:
        mov esi,eax
    L_00457d38:
        push esi
    L_00457d39:
        call asm_isspace_004568d7
    L_00457d3e:
        pop ecx
    L_00457d3f:
        test eax,eax
    L_00457d41:
        jne short L_00457d25
    L_00457d43:
        mov dword ptr [ebp-190h],esi
    L_00457d49:
        mov esi,dword ptr [ebp-1C4h]
    L_00457d4f:
        jmp short L_00457d68
    L_00457d51:
        inc dword ptr [ebp-184h]
    L_00457d57:
        mov edx,dword ptr [ebp-194h]
    L_00457d5d:
        call asm_inc_00457a3c
    L_00457d62:
        mov dword ptr [ebp-190h],eax
    L_00457d68:
        mov ecx,dword ptr [ebp-1BCh]
    L_00457d6e:
        test ecx,ecx
    L_00457d70:
        je short L_00457d7f
    L_00457d72:
        cmp dword ptr [ebp-188h],0
    L_00457d79:
        je asm_target_0045818e
    L_00457d7f:
        cmp esi,6Fh
    L_00457d82:
        jg asm_target_00458159
    L_00457d88:
        je asm_target_00458488
    L_00457d8e:
        cmp esi,63h
    L_00457d91:
        je asm_target_0045800e
    L_00457d97:
        cmp esi,64h
    L_00457d9a:
        je asm_target_00458488
    L_00457da0:
        jle asm_target_00458183
    L_00457da6:
        cmp esi,67h
    L_00457da9:
        jle short L_00457def
    L_00457dab:
        cmp esi,69h
    L_00457dae:
        je short L_00457dd1
    L_00457db0:
        cmp esi,6Eh
    L_00457db3:
        jne asm_target_00458183
    L_00457db9:
        mov eax,dword ptr [ebp-184h]
    L_00457dbf:
        cmp byte ptr [ebp-18Ah],0
    L_00457dc6:
        je asm_target_0045877c
    L_00457dcc:
        jmp asm_target_00457ffc
    L_00457dd1:
        push 64h
    L_00457dd3:
        pop esi
    L_00457dd4:
        mov ebx,dword ptr [ebp-190h]
    L_00457dda:
        cmp ebx,2Dh
    L_00457ddd:
        jne asm_target_0045831c
    L_00457de3:
        mov byte ptr [ebp-197h],1
    L_00457dea:
        jmp asm_target_00458321
    L_00457def:
        lea esi,[ebp-17Ch]
    L_00457df5:
        mov ebx,dword ptr [ebp-190h]
    L_00457dfb:
        cmp ebx,2Dh
    L_00457dfe:
        jne short L_00457e0e
    L_00457e00:
        mov byte ptr [ebp-17Ch],bl
    L_00457e06:
        lea esi,[ebp-17Bh]
    L_00457e0c:
        jmp short L_00457e13
    L_00457e0e:
        cmp ebx,2Bh
    L_00457e11:
        jne short L_00457e36
    L_00457e13:
        dec dword ptr [ebp-188h]
    L_00457e19:
        inc dword ptr [ebp-184h]
    L_00457e1f:
        mov edi,dword ptr [ebp-194h]
    L_00457e25:
        mov edx,edi
    L_00457e27:
        call asm_inc_00457a3c
    L_00457e2c:
        mov ebx,eax
    L_00457e2e:
        mov dword ptr [ebp-190h],ebx
    L_00457e34:
        jmp short L_00457e3c
    L_00457e36:
        mov edi,dword ptr [ebp-194h]
    L_00457e3c:
        cmp dword ptr [ebp-1BCh],0
    L_00457e43:
        je short L_00457e51
    L_00457e45:
        cmp dword ptr [ebp-188h],15Dh
    L_00457e4f:
        jle short L_00457e8b
    L_00457e51:
        mov dword ptr [ebp-188h],15Dh
    L_00457e5b:
        jmp short L_00457e8b
    L_00457e5d:
        mov eax,dword ptr [ebp-188h]
    L_00457e63:
        dec dword ptr [ebp-188h]
    L_00457e69:
        test eax,eax
    L_00457e6b:
        je short L_00457e96
    L_00457e6d:
        inc dword ptr [ebp-1A0h]
    L_00457e73:
        mov byte ptr [esi],bl
    L_00457e75:
        inc esi
    L_00457e76:
        inc dword ptr [ebp-184h]
    L_00457e7c:
        mov edx,edi
    L_00457e7e:
        call asm_inc_00457a3c
    L_00457e83:
        mov ebx,eax
    L_00457e85:
        mov dword ptr [ebp-190h],ebx
    L_00457e8b:
        push ebx
    L_00457e8c:
        call asm_isdigit_0045685e
    L_00457e91:
        pop ecx
    L_00457e92:
        test eax,eax
    L_00457e94:
        jne short L_00457e5d
    L_00457e96:
        cmp byte ptr [data_00473af4],bl
    L_00457e9c:
        jne short L_00457f00
    L_00457e9e:
        mov eax,dword ptr [ebp-188h]
    L_00457ea4:
        dec dword ptr [ebp-188h]
    L_00457eaa:
        test eax,eax
    L_00457eac:
        je short L_00457f00
    L_00457eae:
        inc dword ptr [ebp-184h]
    L_00457eb4:
        mov edx,edi
    L_00457eb6:
        call asm_inc_00457a3c
    L_00457ebb:
        mov ebx,eax
    L_00457ebd:
        mov al,byte ptr [data_00473af4]
    L_00457ec2:
        mov byte ptr [esi],al
    L_00457ec4:
        inc esi
    L_00457ec5:
        jmp short L_00457eef
    L_00457ec7:
        mov eax,dword ptr [ebp-188h]
    L_00457ecd:
        dec dword ptr [ebp-188h]
    L_00457ed3:
        test eax,eax
    L_00457ed5:
        je short L_00457f00
    L_00457ed7:
        inc dword ptr [ebp-1A0h]
    L_00457edd:
        mov byte ptr [esi],bl
    L_00457edf:
        inc esi
    L_00457ee0:
        inc dword ptr [ebp-184h]
    L_00457ee6:
        mov edx,edi
    L_00457ee8:
        call asm_inc_00457a3c
    L_00457eed:
        mov ebx,eax
    L_00457eef:
        push ebx
    L_00457ef0:
        mov dword ptr [ebp-190h],ebx
    L_00457ef6:
        call asm_isdigit_0045685e
    L_00457efb:
        pop ecx
    L_00457efc:
        test eax,eax
    L_00457efe:
        jne short L_00457ec7
    L_00457f00:
        cmp dword ptr [ebp-1A0h],0
    L_00457f07:
        je asm_target_00457fa4
    L_00457f0d:
        cmp ebx,65h
    L_00457f10:
        je short L_00457f1b
    L_00457f12:
        cmp ebx,45h
    L_00457f15:
        jne asm_target_00457fa4
    L_00457f1b:
        mov eax,dword ptr [ebp-188h]
    L_00457f21:
        dec dword ptr [ebp-188h]
    L_00457f27:
        test eax,eax
    L_00457f29:
        je short L_00457fa4
    L_00457f2b:
        mov byte ptr [esi],65h
    L_00457f2e:
        inc esi
    L_00457f2f:
        inc dword ptr [ebp-184h]
    L_00457f35:
        mov edx,edi
    L_00457f37:
        call asm_inc_00457a3c
    L_00457f3c:
        mov ebx,eax
    L_00457f3e:
        mov dword ptr [ebp-190h],ebx
    L_00457f44:
        cmp ebx,2Dh
    L_00457f47:
        jne short L_00457f4e
    L_00457f49:
        mov byte ptr [esi],al
    L_00457f4b:
        inc esi
    L_00457f4c:
        jmp short L_00457f53
    L_00457f4e:
        cmp ebx,2Bh
    L_00457f51:
        jne short L_00457f99
    L_00457f53:
        mov eax,dword ptr [ebp-188h]
    L_00457f59:
        dec dword ptr [ebp-188h]
    L_00457f5f:
        test eax,eax
    L_00457f61:
        jne short L_00457f84
    L_00457f63:
        and dword ptr [ebp-188h],eax
    L_00457f69:
        jmp short L_00457f99
    L_00457f6b:
        mov eax,dword ptr [ebp-188h]
    L_00457f71:
        dec dword ptr [ebp-188h]
    L_00457f77:
        test eax,eax
    L_00457f79:
        je short L_00457fa4
    L_00457f7b:
        inc dword ptr [ebp-1A0h]
    L_00457f81:
        mov byte ptr [esi],bl
    L_00457f83:
        inc esi
    L_00457f84:
        mov edx,edi
    L_00457f86:
        inc dword ptr [ebp-184h]
    L_00457f8c:
        call asm_inc_00457a3c
    L_00457f91:
        mov ebx,eax
    L_00457f93:
        mov dword ptr [ebp-190h],ebx
    L_00457f99:
        push ebx
    L_00457f9a:
        call asm_isdigit_0045685e
    L_00457f9f:
        pop ecx
    L_00457fa0:
        test eax,eax
    L_00457fa2:
        jne short L_00457f6b
    L_00457fa4:
        dec dword ptr [ebp-184h]
    L_00457faa:
        cmp ebx,0FFFFFFFFh
    L_00457fad:
        je short L_00457fb8
    L_00457faf:
        push edi
    L_00457fb0:
        push ebx
    L_00457fb1:
        call asm_FID_conflict__ungetc_0045e204
    L_00457fb6:
        pop ecx
    L_00457fb7:
        pop ecx
    L_00457fb8:
        cmp dword ptr [ebp-1A0h],0
    L_00457fbf:
        je asm_target_0045885e
    L_00457fc5:
        cmp byte ptr [ebp-18Ah],0
    L_00457fcc:
        jne short L_00457ff6
    L_00457fce:
        inc dword ptr [ebp-1C0h]
    L_00457fd4:
        mov byte ptr [esi],0
    L_00457fd7:
        lea eax,[ebp-17Ch]
    L_00457fdd:
        push eax
    L_00457fde:
        push dword ptr [ebp-1B8h]
    L_00457fe4:
        movsx eax,byte ptr [ebp-18Bh]
    L_00457feb:
        dec eax
    L_00457fec:
        push eax
    L_00457fed:
        call dword ptr [data_004739c8]
    L_00457ff3:
        add esp,0Ch
    L_00457ff6:
        mov edi,dword ptr [ebp-19Ch]
    L_00457ffc:
        inc byte ptr [ebp-195h]
    L_00458002:
        inc edi
    L_00458003:
        mov dword ptr [ebp-19Ch],edi
    L_00458009:
        jmp asm_target_0045883c
    L_0045800e:
        test ecx,ecx
    L_00458010:
        jne short L_00458022
    L_00458012:
        mov dword ptr [ebp-1BCh],1
    L_0045801c:
        inc dword ptr [ebp-188h]
    L_00458022:
        cmp byte ptr [ebp-189h],0
    L_00458029:
        jle short L_00458032
    L_0045802b:
        mov byte ptr [ebp-196h],1
    L_00458032:
        mov edi,ebx
    L_00458034:
        dec dword ptr [ebp-184h]
    L_0045803a:
        cmp dword ptr [ebp-190h],0FFFFFFFFh
    L_00458041:
        je short L_00458056
    L_00458043:
        push dword ptr [ebp-194h]
    L_00458049:
        push dword ptr [ebp-190h]
    L_0045804f:
        call asm_FID_conflict__ungetc_0045e204
    L_00458054:
        pop ecx
    L_00458055:
        pop ecx
    L_00458056:
        cmp dword ptr [ebp-1BCh],0
    L_0045805d:
        je short L_00458073
    L_0045805f:
        mov eax,dword ptr [ebp-188h]
    L_00458065:
        dec dword ptr [ebp-188h]
    L_0045806b:
        test eax,eax
    L_0045806d:
        je asm_target_00458433
    L_00458073:
        inc dword ptr [ebp-184h]
    L_00458079:
        mov edx,dword ptr [ebp-194h]
    L_0045807f:
        call asm_inc_00457a3c
    L_00458084:
        mov dword ptr [ebp-190h],eax
    L_0045808a:
        cmp eax,0FFFFFFFFh
    L_0045808d:
        je asm_target_0045841a
    L_00458093:
        cmp esi,63h
    L_00458096:
        je short L_004580e5
    L_00458098:
        cmp esi,73h
    L_0045809b:
        jne short L_004580ac
    L_0045809d:
        cmp eax,9
    L_004580a0:
        jl short L_004580a7
    L_004580a2:
        cmp eax,0Dh
    L_004580a5:
        jle short L_004580ac
    L_004580a7:
        cmp eax,20h
    L_004580aa:
        jne short L_004580e5
    L_004580ac:
        cmp esi,7Bh
    L_004580af:
        jne asm_target_0045841a
    L_004580b5:
        mov ecx,eax
    L_004580b7:
        and ecx,7
    L_004580ba:
        xor edx,edx
    L_004580bc:
        inc edx
    L_004580bd:
        shl edx,cl
    L_004580bf:
        mov ecx,eax
    L_004580c1:
        sar ecx,3
    L_004580c4:
        mov esi,dword ptr [ebp-1C8h]
    L_004580ca:
        movsx ecx,byte ptr [ecx+esi]
    L_004580ce:
        movsx esi,byte ptr [ebp-1B1h]
    L_004580d5:
        xor ecx,esi
    L_004580d7:
        test edx,ecx
    L_004580d9:
        je asm_target_0045841a
    L_004580df:
        mov esi,dword ptr [ebp-1C4h]
    L_004580e5:
        cmp byte ptr [ebp-18Ah],0
    L_004580ec:
        jne asm_target_00458414
    L_004580f2:
        cmp byte ptr [ebp-196h],0
    L_004580f9:
        je asm_target_00458406
    L_004580ff:
        mov byte ptr [ebp-1CCh],al
    L_00458105:
        movzx eax,al
    L_00458108:
        mov ecx,dword ptr [data_004739d8]
    L_0045810e:
        test byte ptr [ecx+eax*2+1],80h
    L_00458113:
        je short L_0045812c
    L_00458115:
        inc dword ptr [ebp-184h]
    L_0045811b:
        mov edx,dword ptr [ebp-194h]
    L_00458121:
        call asm_inc_00457a3c
    L_00458126:
        mov byte ptr [ebp-1CBh],al
    L_0045812c:
        push dword ptr [data_00473af0]
    L_00458132:
        lea eax,[ebp-1CCh]
    L_00458138:
        push eax
    L_00458139:
        lea eax,[ebp-1D8h]
    L_0045813f:
        push eax
    L_00458140:
        call asm_mbtowc_0045e375
    L_00458145:
        add esp,0Ch
    L_00458148:
        mov ax,word ptr [ebp-1D8h]
    L_0045814f:
        mov word ptr [ebx],ax
    L_00458152:
        inc ebx
    L_00458153:
        inc ebx
    L_00458154:
        jmp asm_target_00458409
    L_00458159:
        mov eax,esi
    L_0045815b:
        sub eax,70h
    L_0045815e:
        je asm_target_00458481
    L_00458164:
        sub eax,3
    L_00458167:
        je asm_target_00458022
    L_0045816d:
        dec eax
    L_0045816e:
        dec eax
    L_0045816f:
        je asm_target_00458488
    L_00458175:
        sub eax,3
    L_00458178:
        je asm_target_00457dd4
    L_0045817e:
        sub eax,3
    L_00458181:
        je short L_004581be
    L_00458183:
        movzx eax,byte ptr [edi]
    L_00458186:
        cmp eax,dword ptr [ebp-190h]
    L_0045818c:
        je short L_0045819a
    L_0045818e:
        cmp dword ptr [ebp-190h],0FFFFFFFFh
    L_00458195:
        jmp asm_target_0045881f
    L_0045819a:
        dec byte ptr [ebp-195h]
    L_004581a0:
        cmp byte ptr [ebp-18Ah],0
    L_004581a7:
        jne asm_target_00457ffc
    L_004581ad:
        mov eax,dword ptr [ebp-1E8h]
    L_004581b3:
        mov dword ptr [ebp-1D4h],eax
    L_004581b9:
        jmp asm_target_00457ffc
    L_004581be:
        cmp byte ptr [ebp-189h],0
    L_004581c5:
        jle short L_004581ce
    L_004581c7:
        mov byte ptr [ebp-196h],1
    L_004581ce:
        mov edi,dword ptr [ebp-19Ch]
    L_004581d4:
        inc edi
    L_004581d5:
        mov dword ptr [ebp-19Ch],edi
    L_004581db:
        mov dword ptr [ebp-1E0h],edi
    L_004581e1:
        cmp byte ptr [edi],5Eh
    L_004581e4:
        jne short L_004581f4
    L_004581e6:
        inc edi
    L_004581e7:
        mov dword ptr [ebp-1E0h],edi
    L_004581ed:
        mov byte ptr [ebp-1B1h],0FFh
    L_004581f4:
        mov ebx,dword ptr [ebp-1C8h]
    L_004581fa:
        test ebx,ebx
    L_004581fc:
        TH10_REL8(0x75, 0x004581fc, VA_asm_FUN_00457a7c_part_0045825b)
    L_004581fe:
        and dword ptr [ebp-4],ebx
    L_00458201:
        push 20h
    L_00458203:
        pop eax
    L_00458204:
        call asm_chkstk_00458ec0
    L_00458209:
        mov dword ptr [ebp-18h],esp
    L_0045820c:
        mov ebx,esp
    L_0045820e:
        mov dword ptr [ebp-1C8h],ebx
    L_00458214:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_00458218:
        TH10_REL8(0xeb, 0x00458218, VA_asm_FUN_00457a7c_part_0045825b)
    }
}

// 0x0045825B..0x004588A6: FUN_00457a7c
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00457a7c_part_0045825b() {
    __asm {
    L_0045825b:
        push 20h
    L_0045825d:
        push 0
    L_0045825f:
        push ebx
    L_00458260:
        call asm_memset_0045bed0
    L_00458265:
        add esp,0Ch
    L_00458268:
        cmp dword ptr [ebp-1C4h],7Bh
    L_0045826f:
        jne short L_004582e8
    L_00458271:
        cmp byte ptr [edi],5Dh
    L_00458274:
        jne short L_004582e8
    L_00458276:
        mov dl,5Dh
    L_00458278:
        inc edi
    L_00458279:
        mov byte ptr [ebx+0Bh],20h
    L_0045827d:
        jmp short L_004582ee
    L_0045827f:
        inc edi
    L_00458280:
        cmp al,2Dh
    L_00458282:
        jne short L_004582cf
    L_00458284:
        test dl,dl
    L_00458286:
        je short L_004582cf
    L_00458288:
        mov cl,byte ptr [edi]
    L_0045828a:
        cmp cl,5Dh
    L_0045828d:
        je short L_004582cf
    L_0045828f:
        inc edi
    L_00458290:
        cmp dl,cl
    L_00458292:
        jae short L_00458298
    L_00458294:
        mov al,cl
    L_00458296:
        jmp short L_0045829c
    L_00458298:
        mov al,dl
    L_0045829a:
        mov dl,cl
    L_0045829c:
        cmp dl,al
    L_0045829e:
        ja short L_004582cb
    L_004582a0:
        movzx esi,dl
    L_004582a3:
        sub al,dl
    L_004582a5:
        inc al
    L_004582a7:
        movzx eax,al
    L_004582aa:
        mov dword ptr [ebp-1DCh],eax
    L_004582b0:
        mov eax,esi
    L_004582b2:
        shr eax,3
    L_004582b5:
        add eax,ebx
    L_004582b7:
        mov ecx,esi
    L_004582b9:
        and ecx,7
    L_004582bc:
        mov dl,1
    L_004582be:
        shl dl,cl
    L_004582c0:
        or byte ptr [eax],dl
    L_004582c2:
        inc esi
    L_004582c3:
        dec dword ptr [ebp-1DCh]
    L_004582c9:
        jne short L_004582b0
    L_004582cb:
        xor dl,dl
    L_004582cd:
        jmp short L_004582ee
    L_004582cf:
        mov byte ptr [ebp-1A1h],al
    L_004582d5:
        movzx ecx,al
    L_004582d8:
        mov eax,ecx
    L_004582da:
        shr eax,3
    L_004582dd:
        add eax,ebx
    L_004582df:
        and ecx,7
    L_004582e2:
        mov dl,1
    L_004582e4:
        shl dl,cl
    L_004582e6:
        or byte ptr [eax],dl
    L_004582e8:
        mov dl,byte ptr [ebp-1A1h]
    L_004582ee:
        mov al,byte ptr [edi]
    L_004582f0:
        cmp al,5Dh
    L_004582f2:
        jne short L_0045827f
    L_004582f4:
        test al,al
    L_004582f6:
        je asm_target_0045885e
    L_004582fc:
        mov esi,dword ptr [ebp-1C4h]
    L_00458302:
        mov ebx,dword ptr [ebp-1B8h]
    L_00458308:
        cmp esi,7Bh
    L_0045830b:
        jne asm_target_00458032
    L_00458311:
        mov dword ptr [ebp-19Ch],edi
    L_00458317:
        jmp asm_target_00458032
    L_0045831c:
        cmp ebx,2Bh
    L_0045831f:
        jne short L_0045834f
    L_00458321:
        dec dword ptr [ebp-188h]
    L_00458327:
        jne short L_00458336
    L_00458329:
        test ecx,ecx
    L_0045832b:
        je short L_00458336
    L_0045832d:
        mov byte ptr [ebp-17Dh],1
    L_00458334:
        jmp short L_0045834f
    L_00458336:
        inc dword ptr [ebp-184h]
    L_0045833c:
        mov edx,dword ptr [ebp-194h]
    L_00458342:
        call asm_inc_00457a3c
    L_00458347:
        mov ebx,eax
    L_00458349:
        mov dword ptr [ebp-190h],ebx
    L_0045834f:
        cmp ebx,30h
    L_00458352:
        jne asm_target_004584cf
    L_00458358:
        inc dword ptr [ebp-184h]
    L_0045835e:
        mov edx,dword ptr [ebp-194h]
    L_00458364:
        call asm_inc_00457a3c
    L_00458369:
        mov ebx,eax
    L_0045836b:
        mov dword ptr [ebp-190h],ebx
    L_00458371:
        cmp bl,78h
    L_00458374:
        je short L_004583ca
    L_00458376:
        cmp bl,58h
    L_00458379:
        je short L_004583ca
    L_0045837b:
        mov dword ptr [ebp-1A0h],1
    L_00458385:
        cmp esi,78h
    L_00458388:
        je short L_004583a9
    L_0045838a:
        cmp dword ptr [ebp-1BCh],0
    L_00458391:
        je short L_004583a1
    L_00458393:
        dec dword ptr [ebp-188h]
    L_00458399:
        jne short L_004583a1
    L_0045839b:
        inc byte ptr [ebp-17Dh]
    L_004583a1:
        push 6Fh
    L_004583a3:
        pop esi
    L_004583a4:
        jmp asm_target_004584cf
    L_004583a9:
        dec dword ptr [ebp-184h]
    L_004583af:
        cmp ebx,0FFFFFFFFh
    L_004583b2:
        je short L_004583c2
    L_004583b4:
        push dword ptr [ebp-194h]
    L_004583ba:
        push ebx
    L_004583bb:
        call asm_FID_conflict__ungetc_0045e204
    L_004583c0:
        pop ecx
    L_004583c1:
        pop ecx
    L_004583c2:
        push 30h
    L_004583c4:
        pop ebx
    L_004583c5:
        jmp asm_target_004584c9
    L_004583ca:
        inc dword ptr [ebp-184h]
    L_004583d0:
        mov edx,dword ptr [ebp-194h]
    L_004583d6:
        call asm_inc_00457a3c
    L_004583db:
        mov ebx,eax
    L_004583dd:
        mov dword ptr [ebp-190h],ebx
    L_004583e3:
        cmp dword ptr [ebp-1BCh],0
    L_004583ea:
        je short L_00458402
    L_004583ec:
        sub dword ptr [ebp-188h],2
    L_004583f3:
        cmp dword ptr [ebp-188h],1
    L_004583fa:
        jge short L_00458402
    L_004583fc:
        inc byte ptr [ebp-17Dh]
    L_00458402:
        push 78h
    L_00458404:
        jmp short L_004583a3
    L_00458406:
        mov byte ptr [ebx],al
    L_00458408:
        inc ebx
    L_00458409:
        mov dword ptr [ebp-1B8h],ebx
    L_0045840f:
        jmp asm_target_00458056
    L_00458414:
        inc edi
    L_00458415:
        jmp asm_target_00458056
    L_0045841a:
        dec dword ptr [ebp-184h]
    L_00458420:
        cmp eax,0FFFFFFFFh
    L_00458423:
        je short L_00458433
    L_00458425:
        push dword ptr [ebp-194h]
    L_0045842b:
        push eax
    L_0045842c:
        call asm_FID_conflict__ungetc_0045e204
    L_00458431:
        pop ecx
    L_00458432:
        pop ecx
    L_00458433:
        cmp edi,ebx
    L_00458435:
        je asm_target_0045885e
    L_0045843b:
        cmp byte ptr [ebp-18Ah],0
    L_00458442:
        jne asm_target_00457ff6
    L_00458448:
        inc dword ptr [ebp-1C0h]
    L_0045844e:
        cmp dword ptr [ebp-1C4h],63h
    L_00458455:
        je asm_target_00457ff6
    L_0045845b:
        mov edi,dword ptr [ebp-19Ch]
    L_00458461:
        mov eax,dword ptr [ebp-1B8h]
    L_00458467:
        cmp byte ptr [ebp-196h],0
    L_0045846e:
        je short L_00458479
    L_00458470:
        and word ptr [eax],0
    L_00458474:
        jmp asm_target_00457ffc
    L_00458479:
        mov byte ptr [eax],0
    L_0045847c:
        jmp asm_target_00457ffc
    L_00458481:
        mov byte ptr [ebp-18Bh],1
    L_00458488:
        mov ebx,dword ptr [ebp-190h]
    L_0045848e:
        cmp ebx,2Dh
    L_00458491:
        jne short L_0045849c
    L_00458493:
        mov byte ptr [ebp-197h],1
    L_0045849a:
        jmp short L_004584a1
    L_0045849c:
        cmp ebx,2Bh
    L_0045849f:
        jne short L_004584cf
    L_004584a1:
        dec dword ptr [ebp-188h]
    L_004584a7:
        jne short L_004584b6
    L_004584a9:
        test ecx,ecx
    L_004584ab:
        je short L_004584b6
    L_004584ad:
        mov byte ptr [ebp-17Dh],1
    L_004584b4:
        jmp short L_004584cf
    L_004584b6:
        inc dword ptr [ebp-184h]
    L_004584bc:
        mov edx,dword ptr [ebp-194h]
    L_004584c2:
        call asm_inc_00457a3c
    L_004584c7:
        mov ebx,eax
    L_004584c9:
        mov dword ptr [ebp-190h],ebx
    L_004584cf:
        cmp dword ptr [ebp-1D0h],0
    L_004584d6:
        je asm_target_00458642
    L_004584dc:
        cmp byte ptr [ebp-17Dh],0
    L_004584e3:
        jne asm_target_00458611
    L_004584e9:
        cmp esi,78h
    L_004584ec:
        je short L_00458554
    L_004584ee:
        cmp esi,70h
    L_004584f1:
        je short L_00458554
    L_004584f3:
        push ebx
    L_004584f4:
        call asm_isdigit_0045685e
    L_004584f9:
        pop ecx
    L_004584fa:
        test eax,eax
    L_004584fc:
        je asm_target_00458591
    L_00458502:
        cmp esi,6Fh
    L_00458505:
        jne short L_00458531
    L_00458507:
        cmp ebx,38h
    L_0045850a:
        jge asm_target_00458591
    L_00458510:
        mov eax,dword ptr [ebp-1B0h]
    L_00458516:
        mov ecx,dword ptr [ebp-1ACh]
    L_0045851c:
        shld ecx,eax,3
    L_00458520:
        shl eax,3
    L_00458523:
        mov dword ptr [ebp-1B0h],eax
    L_00458529:
        mov dword ptr [ebp-1ACh],ecx
    L_0045852f:
        jmp short L_00458597
    L_00458531:
        push 0
    L_00458533:
        push 0Ah
    L_00458535:
        push dword ptr [ebp-1ACh]
    L_0045853b:
        push dword ptr [ebp-1B0h]
    L_00458541:
        call asm_allmul_00456640
    L_00458546:
        mov dword ptr [ebp-1B0h],eax
    L_0045854c:
        mov dword ptr [ebp-1ACh],edx
    L_00458552:
        jmp short L_00458597
    L_00458554:
        push ebx
    L_00458555:
        call asm_isxdigit_00456898
    L_0045855a:
        pop ecx
    L_0045855b:
        test eax,eax
    L_0045855d:
        je short L_00458591
    L_0045855f:
        mov eax,dword ptr [ebp-1B0h]
    L_00458565:
        mov ecx,dword ptr [ebp-1ACh]
    L_0045856b:
        shld ecx,eax,4
    L_0045856f:
        shl eax,4
    L_00458572:
        mov dword ptr [ebp-1B0h],eax
    L_00458578:
        mov dword ptr [ebp-1ACh],ecx
    L_0045857e:
        push ebx
    L_0045857f:
        call asm_isdigit_0045685e
    L_00458584:
        pop ecx
    L_00458585:
        test eax,eax
    L_00458587:
        jne short L_00458597
    L_00458589:
        and ebx,0FFFFFFDFh
    L_0045858c:
        sub ebx,7
    L_0045858f:
        jmp short L_00458597
    L_00458591:
        inc byte ptr [ebp-17Dh]
    L_00458597:
        cmp byte ptr [ebp-17Dh],0
    L_0045859e:
        jne short L_004585e5
    L_004585a0:
        inc dword ptr [ebp-1A0h]
    L_004585a6:
        lea eax,[ebx-30h]
    L_004585a9:
        cdq
    L_004585aa:
        add dword ptr [ebp-1B0h],eax
    L_004585b0:
        adc dword ptr [ebp-1ACh],edx
    L_004585b6:
        cmp dword ptr [ebp-1BCh],0
    L_004585bd:
        je short L_004585d0
    L_004585bf:
        dec dword ptr [ebp-188h]
    L_004585c5:
        jne short L_004585d0
    L_004585c7:
        mov byte ptr [ebp-17Dh],1
    L_004585ce:
        jmp short L_004585fe
    L_004585d0:
        inc dword ptr [ebp-184h]
    L_004585d6:
        mov edx,dword ptr [ebp-194h]
    L_004585dc:
        call asm_inc_00457a3c
    L_004585e1:
        mov ebx,eax
    L_004585e3:
        jmp short L_004585fe
    L_004585e5:
        dec dword ptr [ebp-184h]
    L_004585eb:
        cmp ebx,0FFFFFFFFh
    L_004585ee:
        je short L_004585fe
    L_004585f0:
        push dword ptr [ebp-194h]
    L_004585f6:
        push ebx
    L_004585f7:
        call asm_FID_conflict__ungetc_0045e204
    L_004585fc:
        pop ecx
    L_004585fd:
        pop ecx
    L_004585fe:
        cmp byte ptr [ebp-17Dh],0
    L_00458605:
        je asm_target_004584e9
    L_0045860b:
        mov dword ptr [ebp-190h],ebx
    L_00458611:
        cmp byte ptr [ebp-197h],0
    L_00458618:
        je asm_target_0045873e
    L_0045861e:
        mov eax,dword ptr [ebp-1B0h]
    L_00458624:
        neg eax
    L_00458626:
        mov ecx,dword ptr [ebp-1ACh]
    L_0045862c:
        adc ecx,0
    L_0045862f:
        neg ecx
    L_00458631:
        mov dword ptr [ebp-1B0h],eax
    L_00458637:
        mov dword ptr [ebp-1ACh],ecx
    L_0045863d:
        jmp asm_target_0045873e
    L_00458642:
        cmp byte ptr [ebp-17Dh],0
    L_00458649:
        jne asm_target_0045872f
    L_0045864f:
        cmp esi,78h
    L_00458652:
        je short L_0045868a
    L_00458654:
        cmp esi,70h
    L_00458657:
        je short L_0045868a
    L_00458659:
        push ebx
    L_0045865a:
        call asm_isdigit_0045685e
    L_0045865f:
        pop ecx
    L_00458660:
        test eax,eax
    L_00458662:
        je short L_004586af
    L_00458664:
        cmp esi,6Fh
    L_00458667:
        jne short L_00458677
    L_00458669:
        cmp ebx,38h
    L_0045866c:
        jge short L_004586af
    L_0045866e:
        shl dword ptr [ebp-1A8h],3
    L_00458675:
        jmp short L_004586b5
    L_00458677:
        mov eax,dword ptr [ebp-1A8h]
    L_0045867d:
        lea eax,[eax+eax*4]
    L_00458680:
        shl eax,1
    L_00458682:
        mov dword ptr [ebp-1A8h],eax
    L_00458688:
        jmp short L_004586b5
    L_0045868a:
        push ebx
    L_0045868b:
        call asm_isxdigit_00456898
    L_00458690:
        pop ecx
    L_00458691:
        test eax,eax
    L_00458693:
        je short L_004586af
    L_00458695:
        shl dword ptr [ebp-1A8h],4
    L_0045869c:
        push ebx
    L_0045869d:
        call asm_isdigit_0045685e
    L_004586a2:
        pop ecx
    L_004586a3:
        test eax,eax
    L_004586a5:
        jne short L_004586b5
    L_004586a7:
        and ebx,0FFFFFFDFh
    L_004586aa:
        sub ebx,7
    L_004586ad:
        jmp short L_004586b5
    L_004586af:
        inc byte ptr [ebp-17Dh]
    L_004586b5:
        cmp byte ptr [ebp-17Dh],0
    L_004586bc:
        jne short L_00458703
    L_004586be:
        inc dword ptr [ebp-1A0h]
    L_004586c4:
        mov eax,dword ptr [ebp-1A8h]
    L_004586ca:
        lea eax,[eax+ebx-30h]
    L_004586ce:
        mov dword ptr [ebp-1A8h],eax
    L_004586d4:
        cmp dword ptr [ebp-1BCh],0
    L_004586db:
        je short L_004586ee
    L_004586dd:
        dec dword ptr [ebp-188h]
    L_004586e3:
        jne short L_004586ee
    L_004586e5:
        mov byte ptr [ebp-17Dh],1
    L_004586ec:
        jmp short L_0045871c
    L_004586ee:
        inc dword ptr [ebp-184h]
    L_004586f4:
        mov edx,dword ptr [ebp-194h]
    L_004586fa:
        call asm_inc_00457a3c
    L_004586ff:
        mov ebx,eax
    L_00458701:
        jmp short L_0045871c
    L_00458703:
        dec dword ptr [ebp-184h]
    L_00458709:
        cmp ebx,0FFFFFFFFh
    L_0045870c:
        je short L_0045871c
    L_0045870e:
        push dword ptr [ebp-194h]
    L_00458714:
        push ebx
    L_00458715:
        call asm_FID_conflict__ungetc_0045e204
    L_0045871a:
        pop ecx
    L_0045871b:
        pop ecx
    L_0045871c:
        cmp byte ptr [ebp-17Dh],0
    L_00458723:
        je asm_target_0045864f
    L_00458729:
        mov dword ptr [ebp-190h],ebx
    L_0045872f:
        cmp byte ptr [ebp-197h],0
    L_00458736:
        je short L_0045873e
    L_00458738:
        neg dword ptr [ebp-1A8h]
    L_0045873e:
        cmp esi,46h
    L_00458741:
        jne short L_0045874a
    L_00458743:
        and dword ptr [ebp-1A0h],0
    L_0045874a:
        cmp dword ptr [ebp-1A0h],0
    L_00458751:
        je asm_target_0045885e
    L_00458757:
        cmp byte ptr [ebp-18Ah],0
    L_0045875e:
        jne asm_target_00457ff6
    L_00458764:
        inc dword ptr [ebp-1C0h]
    L_0045876a:
        mov ebx,dword ptr [ebp-1B8h]
    L_00458770:
        mov edi,dword ptr [ebp-19Ch]
    L_00458776:
        mov eax,dword ptr [ebp-1A8h]
    L_0045877c:
        cmp dword ptr [ebp-1D0h],0
    L_00458783:
        je short L_0045879b
    L_00458785:
        mov eax,dword ptr [ebp-1B0h]
    L_0045878b:
        mov dword ptr [ebx],eax
    L_0045878d:
        mov eax,dword ptr [ebp-1ACh]
    L_00458793:
        mov dword ptr [ebx+4],eax
    L_00458796:
        jmp asm_target_00457ffc
    L_0045879b:
        cmp byte ptr [ebp-18Bh],0
    L_004587a2:
        je short L_004587ab
    L_004587a4:
        mov dword ptr [ebx],eax
    L_004587a6:
        jmp asm_target_00457ffc
    L_004587ab:
        mov word ptr [ebx],ax
    L_004587ae:
        jmp asm_target_00457ffc
    L_004587b3:
        inc dword ptr [ebp-184h]
    L_004587b9:
        mov edx,dword ptr [ebp-194h]
    L_004587bf:
        call asm_inc_00457a3c
    L_004587c4:
        mov ebx,eax
    L_004587c6:
        mov dword ptr [ebp-190h],ebx
    L_004587cc:
        movzx eax,byte ptr [edi]
    L_004587cf:
        inc edi
    L_004587d0:
        mov dword ptr [ebp-19Ch],edi
    L_004587d6:
        cmp eax,ebx
    L_004587d8:
        jne short L_0045881c
    L_004587da:
        movzx eax,bl
    L_004587dd:
        mov ecx,dword ptr [data_004739d8]
    L_004587e3:
        test byte ptr [ecx+eax*2+1],80h
    L_004587e8:
        je short L_0045883c
    L_004587ea:
        inc dword ptr [ebp-184h]
    L_004587f0:
        mov edx,dword ptr [ebp-194h]
    L_004587f6:
        call asm_inc_00457a3c
    L_004587fb:
        movzx ecx,byte ptr [edi]
    L_004587fe:
        inc edi
    L_004587ff:
        mov dword ptr [ebp-19Ch],edi
    L_00458805:
        cmp ecx,eax
    L_00458807:
        je short L_00458836
    L_00458809:
        cmp eax,0FFFFFFFFh
    L_0045880c:
        je short L_0045881c
    L_0045880e:
        push dword ptr [ebp-194h]
    L_00458814:
        push eax
    L_00458815:
        call asm_FID_conflict__ungetc_0045e204
    L_0045881a:
        pop ecx
    L_0045881b:
        pop ecx
    L_0045881c:
        cmp ebx,0FFFFFFFFh
    L_0045881f:
        je short L_0045885e
    L_00458821:
        push dword ptr [ebp-194h]
    L_00458827:
        push dword ptr [ebp-190h]
    L_0045882d:
        call asm_FID_conflict__ungetc_0045e204
    L_00458832:
        pop ecx
    L_00458833:
        pop ecx
    L_00458834:
        jmp short L_0045885e
    L_00458836:
        dec dword ptr [ebp-184h]
    L_0045883c:
        cmp dword ptr [ebp-190h],0FFFFFFFFh
    L_00458843:
        jne asm_target_00457ae4
    L_00458849:
        cmp byte ptr [edi],25h
    L_0045884c:
        jne short L_0045885e
    L_0045884e:
        mov eax,dword ptr [ebp-19Ch]
    L_00458854:
        cmp byte ptr [eax+1],6Eh
    L_00458858:
        je asm_target_00457ade
    L_0045885e:
        cmp dword ptr [ebp-1E4h],1
    L_00458865:
        jne short L_00458873
    L_00458867:
        push dword ptr [ebp-1C8h]
    L_0045886d:
        call asm_free_00452422
    L_00458872:
        pop ecx
    L_00458873:
        mov eax,dword ptr [ebp-1C0h]
    L_00458879:
        cmp dword ptr [ebp-190h],0FFFFFFFFh
    L_00458880:
        jne short L_00458891
    L_00458882:
        test eax,eax
    L_00458884:
        jne short L_00458891
    L_00458886:
        cmp byte ptr [ebp-195h],al
    L_0045888c:
        jne short L_00458891
    L_0045888e:
        or eax,0FFFFFFFFh
    L_00458891:
        lea esp,[ebp-1F4h]
    L_00458897:
        mov ecx,dword ptr [ebp-1Ch]
    L_0045889a:
        xor ecx,ebp
    L_0045889c:
        call asm_security_check_cookie_00458ea5
    L_004588a1:
        call asm_SEH_epilog_00454bf7
    L_004588a6:
        ret
    }
}
