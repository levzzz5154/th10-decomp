#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00413BC0..0x00413CA4: FUN_00413bc0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00413bc0_00413bc0() {
    __asm {
    L_00413bc0:
        push ecx
    L_00413bc1:
        mov eax,dword ptr [edi+8]
    L_00413bc4:
        test eax,eax
    L_00413bc6:
        mov ecx,2
    L_00413bcb:
        je short L_00413bd0
    L_00413bcd:
        or dword ptr [eax+4],ecx
    L_00413bd0:
        mov eax,dword ptr [edi+0Ch]
    L_00413bd3:
        test eax,eax
    L_00413bd5:
        je short L_00413bda
    L_00413bd7:
        or dword ptr [eax+4],ecx
    L_00413bda:
        mov eax,dword ptr [edi+9E58h]
    L_00413be0:
        test eax,eax
    L_00413be2:
        push ebx
    L_00413be3:
        push ebp
    L_00413be4:
        push esi
    L_00413be5:
        mov esi,dword ptr [data_00491c10]
    L_00413beb:
        jne short L_00413c38
    L_00413bed:
        mov ebp,dword ptr [edi+9EC8h]
    L_00413bf3:
        call asm_FUN_00449950_00449950
    L_00413bf8:
        mov ebx,eax
    L_00413bfa:
        mov edx,dword ptr [ebx+35Ch]
    L_00413c00:
        push 0
    L_00413c02:
        or edx,40000000h
    L_00413c08:
        push ebx
    L_00413c09:
        mov ecx,ebp
    L_00413c0b:
        mov dword ptr [ebx+20h],0Fh
    L_00413c12:
        mov dword ptr [ebx+35Ch],edx
    L_00413c18:
        call asm_FUN_00449870_00449870
    L_00413c1d:
        mov esi,dword ptr [data_00491c10]
    L_00413c23:
        lea eax,[esp+0Ch]
    L_00413c27:
        mov edx,esi
    L_00413c29:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_00413c2e:
        mov eax,dword ptr [esp+0Ch]
    L_00413c32:
        mov dword ptr [edi+9E58h],eax
    L_00413c38:
        mov eax,dword ptr [edi+9E5Ch]
    L_00413c3e:
        test eax,eax
    L_00413c40:
        jne short L_00413c83
    L_00413c42:
        mov ebp,dword ptr [edi+9EC8h]
    L_00413c48:
        call asm_FUN_00449950_00449950
    L_00413c4d:
        mov ebx,eax
    L_00413c4f:
        mov edx,dword ptr [ebx+35Ch]
    L_00413c55:
        push 1
    L_00413c57:
        or edx,40000000h
    L_00413c5d:
        push ebx
    L_00413c5e:
        mov ecx,ebp
    L_00413c60:
        mov dword ptr [ebx+20h],0Fh
    L_00413c67:
        mov dword ptr [ebx+35Ch],edx
    L_00413c6d:
        call asm_FUN_00449870_00449870
    L_00413c72:
        mov esi,dword ptr [data_00491c10]
    L_00413c78:
        lea eax,[esp+0Ch]
    L_00413c7c:
        mov edx,esi
    L_00413c7e:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_00413c83:
        test byte ptr [edi+36Ch],1
    L_00413c8a:
        jne asm_target_00413d86
    L_00413c90:
        mov esi,14h
    L_00413c95:
        lea ebp,[edi+24C8h]
    L_00413c9b:
        mov dword ptr [esp+0Ch],0Ah
    L_00413ca3:
        TH10_REL8(0xeb, 0x00413ca3, VA_asm_FUN_00413bc0_part_00413cb0)
    }
}

// 0x00413CB0..0x00413D39: FUN_00413bc0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00413bc0_part_00413cb0() {
    __asm {
    L_00413cb0:
        mov ecx,dword ptr [edi+9EC8h]
    L_00413cb6:
        lea ebx,[esi-0Ah]
    L_00413cb9:
        lea eax,[ebp-24B8h]
    L_00413cbf:
        call asm_AnimationObject_LoadScript_0043e710
    L_00413cc4:
        mov ecx,dword ptr [edi+9EC8h]
    L_00413cca:
        mov ebx,esi
    L_00413ccc:
        mov eax,ebp
    L_00413cce:
        call asm_AnimationObject_LoadScript_0043e710
    L_00413cd3:
        mov eax,dword ptr [esp+0Ch]
    L_00413cd7:
        inc esi
    L_00413cd8:
        add ebp,3ACh
    L_00413cde:
        dec eax
    L_00413cdf:
        mov dword ptr [esp+0Ch],eax
    L_00413ce3:
        jne short L_00413cb0
    L_00413ce5:
        xor esi,esi
    L_00413ce7:
        lea ebp,[edi+4980h]
    L_00413ced:
        TH10_NOP_LEA_ECX_DISP8()
    L_00413cf0:
        mov ecx,dword ptr [edi+9EC8h]
    L_00413cf6:
        lea ebx,[esi+1Eh]
    L_00413cf9:
        mov eax,ebp
    L_00413cfb:
        call asm_AnimationObject_LoadScript_0043e710
    L_00413d00:
        inc esi
    L_00413d01:
        add ebp,3ACh
    L_00413d07:
        cmp esi,9
    L_00413d0a:
        jl short L_00413cf0
    L_00413d0c:
        xor esi,esi
    L_00413d0e:
        lea ebp,[edi+6A8Ch]
    L_00413d14:
        mov ecx,dword ptr [edi+9EC8h]
    L_00413d1a:
        lea ebx,[esi+2Fh]
    L_00413d1d:
        mov eax,ebp
    L_00413d1f:
        call asm_AnimationObject_LoadScript_0043e710
    L_00413d24:
        inc esi
    L_00413d25:
        add ebp,3ACh
    L_00413d2b:
        cmp esi,4
    L_00413d2e:
        jl short L_00413d14
    L_00413d30:
        xor esi,esi
    L_00413d32:
        lea ebp,[edi+793Ch]
    L_00413d38:
        TH10_REL8(0xeb, 0x00413d38, VA_asm_FUN_00413bc0_part_00413d40)
    }
}

// 0x00413D40..0x00414227: FUN_00413bc0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00413bc0_part_00413d40() {
    __asm {
    L_00413d40:
        mov ecx,dword ptr [edi+9EC8h]
    L_00413d46:
        lea ebx,[esi+50h]
    L_00413d49:
        mov eax,ebp
    L_00413d4b:
        call asm_AnimationObject_LoadScript_0043e710
    L_00413d50:
        inc esi
    L_00413d51:
        add ebp,3ACh
    L_00413d57:
        cmp esi,2
    L_00413d5a:
        jl short L_00413d40
    L_00413d5c:
        xor esi,esi
    L_00413d5e:
        lea ebp,[edi+8094h]
    L_00413d64:
        mov ecx,dword ptr [edi+9EC8h]
    L_00413d6a:
        lea ebx,[esi+33h]
    L_00413d6d:
        mov eax,ebp
    L_00413d6f:
        call asm_AnimationObject_LoadScript_0043e710
    L_00413d74:
        inc esi
    L_00413d75:
        add ebp,3ACh
    L_00413d7b:
        cmp esi,7
    L_00413d7e:
        jl short L_00413d64
    L_00413d80:
        mov esi,dword ptr [data_00491c10]
    L_00413d86:
        mov ecx,dword ptr [data_00474c70]
    L_00413d8c:
        xor edx,edx
    L_00413d8e:
        test ecx,ecx
    L_00413d90:
        jle short L_00413db0
    L_00413d92:
        lea eax,[edi+4CDCh]
    L_00413d98:
        mov edx,ecx
    L_00413d9a:
        lea ebx,[ebx+force_disp32_zero]
    L_00413da0:
        or dword ptr [eax],2
    L_00413da3:
        add eax,3ACh
    L_00413da8:
        dec ecx
    L_00413da9:
        jne short L_00413da0
    L_00413dab:
        cmp edx,9
    L_00413dae:
        jge short L_00413dd1
    L_00413db0:
        mov ecx,edx
    L_00413db2:
        imul ecx,3ACh
    L_00413db8:
        lea eax,[ecx+edi+4CDCh]
    L_00413dbf:
        mov ecx,9
    L_00413dc4:
        sub ecx,edx
    L_00413dc6:
        and dword ptr [eax],0FFFFFFFDh
    L_00413dc9:
        add eax,3ACh
    L_00413dce:
        dec ecx
    L_00413dcf:
        jne short L_00413dc6
    L_00413dd1:
        movsx eax,word ptr [data_00474c48]
    L_00413dd8:
        cdq
    L_00413dd9:
        mov ecx,14h
    L_00413dde:
        idiv ecx
    L_00413de0:
        imul edx,64h
    L_00413de3:
        mov ecx,eax
    L_00413de5:
        mov eax,66666667h
    L_00413dea:
        imul edx
    L_00413dec:
        sar edx,3
    L_00413def:
        mov ebx,edx
    L_00413df1:
        shr ebx,1Fh
    L_00413df4:
        add ebx,edx
    L_00413df6:
        lea edx,[ecx+8]
    L_00413df9:
        mov ecx,dword ptr [edi+9EC8h]
    L_00413dff:
        lea eax,[edi+6A8Ch]
    L_00413e05:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_00413e0a:
        mov eax,ebx
    L_00413e0c:
        cdq
    L_00413e0d:
        mov ecx,0Ah
    L_00413e12:
        idiv ecx
    L_00413e14:
        mov ecx,dword ptr [edi+9EC8h]
    L_00413e1a:
        mov ebx,edx
    L_00413e1c:
        lea edx,[eax+8]
    L_00413e1f:
        lea eax,[edi+71E4h]
    L_00413e25:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_00413e2a:
        mov ecx,dword ptr [edi+9EC8h]
    L_00413e30:
        lea edx,[ebx+8]
    L_00413e33:
        lea eax,[edi+7590h]
    L_00413e39:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_00413e3e:
        cmp dword ptr [data_00491fb8],8
    L_00413e45:
        je asm_target_00413f87
    L_00413e4b:
        test byte ptr [data_00474ca0],20h
    L_00413e52:
        jne asm_target_00413f94
    L_00413e58:
        mov ebp,dword ptr [edi+9E80h]
    L_00413e5e:
        call asm_FUN_00449950_00449950
    L_00413e63:
        mov ebx,eax
    L_00413e65:
        mov ecx,dword ptr [ebx+35Ch]
    L_00413e6b:
        or ecx,40000000h
    L_00413e71:
        xor esi,esi
    L_00413e73:
        push esi
    L_00413e74:
        mov dword ptr [ebx+35Ch],ecx
    L_00413e7a:
        push ebx
    L_00413e7b:
        mov ecx,ebp
    L_00413e7d:
        mov dword ptr [ebx+20h],0Fh
    L_00413e84:
        call asm_FUN_00449870_00449870
    L_00413e89:
        lea eax,[ebx+4]
    L_00413e8c:
        mov dword ptr [eax+4],esi
    L_00413e8f:
        mov dword ptr [eax+8],esi
    L_00413e92:
        mov esi,dword ptr [data_00491c10]
    L_00413e98:
        mov dword ptr [eax],ebx
    L_00413e9a:
        mov ecx,dword ptr [esi+72DAD4h]
    L_00413ea0:
        test ecx,ecx
    L_00413ea2:
        jne short L_00413eac
    L_00413ea4:
        mov dword ptr [esi+72DAD4h],eax
    L_00413eaa:
        jmp short L_00413ec8
    L_00413eac:
        mov ecx,dword ptr [esi+72DAD8h]
    L_00413eb2:
        mov edx,dword ptr [ecx+4]
    L_00413eb5:
        test edx,edx
    L_00413eb7:
        je short L_00413ec2
    L_00413eb9:
        mov dword ptr [eax+4],edx
    L_00413ebc:
        mov edx,dword ptr [ecx+4]
    L_00413ebf:
        mov dword ptr [edx+8],eax
    L_00413ec2:
        mov dword ptr [ecx+4],eax
    L_00413ec5:
        mov dword ptr [eax+8],ecx
    L_00413ec8:
        mov dword ptr [esi+72DAD8h],eax
    L_00413ece:
        mov ecx,dword ptr [esi+732454h]
    L_00413ed4:
        inc ecx
    L_00413ed5:
        mov eax,ecx
    L_00413ed7:
        test eax,eax
    L_00413ed9:
        mov dword ptr [esi+732454h],ecx
    L_00413edf:
        jne short L_00413ee8
    L_00413ee1:
        inc eax
    L_00413ee2:
        mov dword ptr [esi+732454h],eax
    L_00413ee8:
        mov eax,dword ptr [esi+732454h]
    L_00413eee:
        mov dword ptr [ebx],eax
    L_00413ef0:
        mov ebp,dword ptr [edi+9E80h]
    L_00413ef6:
        call asm_FUN_00449950_00449950
    L_00413efb:
        mov ebx,eax
    L_00413efd:
        mov ecx,dword ptr [ebx+35Ch]
    L_00413f03:
        or ecx,40000000h
    L_00413f09:
        push 1
    L_00413f0b:
        mov dword ptr [ebx+35Ch],ecx
    L_00413f11:
        push ebx
    L_00413f12:
        mov ecx,ebp
    L_00413f14:
        mov dword ptr [ebx+20h],0Fh
    L_00413f1b:
        call asm_FUN_00449870_00449870
    L_00413f20:
        mov esi,dword ptr [data_00491c10]
    L_00413f26:
        lea eax,[ebx+4]
    L_00413f29:
        xor ecx,ecx
    L_00413f2b:
        mov dword ptr [eax],ebx
    L_00413f2d:
        mov dword ptr [eax+4],ecx
    L_00413f30:
        mov dword ptr [eax+8],ecx
    L_00413f33:
        cmp dword ptr [esi+72DAD4h],ecx
    L_00413f39:
        jne short L_00413f43
    L_00413f3b:
        mov dword ptr [esi+72DAD4h],eax
    L_00413f41:
        jmp short L_00413f5f
    L_00413f43:
        mov ecx,dword ptr [esi+72DAD8h]
    L_00413f49:
        mov edx,dword ptr [ecx+4]
    L_00413f4c:
        test edx,edx
    L_00413f4e:
        je short L_00413f59
    L_00413f50:
        mov dword ptr [eax+4],edx
    L_00413f53:
        mov edx,dword ptr [ecx+4]
    L_00413f56:
        mov dword ptr [edx+8],eax
    L_00413f59:
        mov dword ptr [ecx+4],eax
    L_00413f5c:
        mov dword ptr [eax+8],ecx
    L_00413f5f:
        mov dword ptr [esi+72DAD8h],eax
    L_00413f65:
        mov ecx,dword ptr [esi+732454h]
    L_00413f6b:
        inc ecx
    L_00413f6c:
        mov eax,ecx
    L_00413f6e:
        test eax,eax
    L_00413f70:
        mov dword ptr [esi+732454h],ecx
    L_00413f76:
        jne short L_00413f7f
    L_00413f78:
        inc eax
    L_00413f79:
        mov dword ptr [esi+732454h],eax
    L_00413f7f:
        mov eax,dword ptr [esi+732454h]
    L_00413f85:
        mov dword ptr [ebx],eax
    L_00413f87:
        test byte ptr [data_00474ca0],20h
    L_00413f8e:
        je asm_target_0041402b
    L_00413f94:
        mov ebx,dword ptr [edi+9EC8h]
    L_00413f9a:
        call asm_FUN_00449950_00449950
    L_00413f9f:
        mov esi,eax
    L_00413fa1:
        mov ecx,dword ptr [esi+35Ch]
    L_00413fa7:
        or ecx,40000000h
    L_00413fad:
        push 71h
    L_00413faf:
        mov dword ptr [esi+35Ch],ecx
    L_00413fb5:
        push esi
    L_00413fb6:
        mov ecx,ebx
    L_00413fb8:
        mov dword ptr [esi+20h],0Fh
    L_00413fbf:
        call asm_FUN_00449870_00449870
    L_00413fc4:
        mov ecx,dword ptr [data_00491c10]
    L_00413fca:
        lea eax,[esi+4]
    L_00413fcd:
        xor ebp,ebp
    L_00413fcf:
        mov dword ptr [eax],esi
    L_00413fd1:
        mov dword ptr [eax+4],ebp
    L_00413fd4:
        mov dword ptr [eax+8],ebp
    L_00413fd7:
        cmp dword ptr [ecx+72DAD4h],ebp
    L_00413fdd:
        jne short L_00413fe7
    L_00413fdf:
        mov dword ptr [ecx+72DAD4h],eax
    L_00413fe5:
        jmp short L_00414003
    L_00413fe7:
        mov edx,dword ptr [ecx+72DAD8h]
    L_00413fed:
        mov ebx,dword ptr [edx+4]
    L_00413ff0:
        cmp ebx,ebp
    L_00413ff2:
        je short L_00413ffd
    L_00413ff4:
        mov dword ptr [eax+4],ebx
    L_00413ff7:
        mov ebx,dword ptr [edx+4]
    L_00413ffa:
        mov dword ptr [ebx+8],eax
    L_00413ffd:
        mov dword ptr [edx+4],eax
    L_00414000:
        mov dword ptr [eax+8],edx
    L_00414003:
        mov dword ptr [ecx+72DAD8h],eax
    L_00414009:
        mov edx,dword ptr [ecx+732454h]
    L_0041400f:
        inc edx
    L_00414010:
        mov eax,edx
    L_00414012:
        cmp eax,ebp
    L_00414014:
        mov dword ptr [ecx+732454h],edx
    L_0041401a:
        jne short L_00414023
    L_0041401c:
        inc eax
    L_0041401d:
        mov dword ptr [ecx+732454h],eax
    L_00414023:
        mov ecx,dword ptr [ecx+732454h]
    L_00414029:
        mov dword ptr [esi],ecx
    L_0041402b:
        mov edx,dword ptr [data_004776e0]
    L_00414031:
        mov ecx,dword ptr [edx+8994h]
    L_00414037:
        lea eax,[edi+9A48h]
    L_0041403d:
        xor ebx,ebx
    L_0041403f:
        call asm_AnimationObject_LoadScript_0043e710
    L_00414044:
        cmp dword ptr [data_00474c7c],1
    L_0041404b:
        jne asm_target_0041410d
    L_00414051:
        mov eax,dword ptr [data_00477810]
    L_00414056:
        mov ecx,dword ptr [eax+5Ch]
    L_00414059:
        test ecx,ecx
    L_0041405b:
        jne asm_target_0041410d
    L_00414061:
        mov eax,dword ptr [data_00474c90]
    L_00414066:
        test eax,eax
    L_00414068:
        jne asm_target_0041410d
    L_0041406e:
        mov esi,dword ptr [data_00491c10]
    L_00414074:
        mov ebp,dword ptr [edi+9EC8h]
    L_0041407a:
        call asm_FUN_00449950_00449950
    L_0041407f:
        mov ebx,eax
    L_00414081:
        mov ecx,dword ptr [ebx+35Ch]
    L_00414087:
        or ecx,40000000h
    L_0041408d:
        push 4Fh
    L_0041408f:
        mov dword ptr [ebx+35Ch],ecx
    L_00414095:
        push ebx
    L_00414096:
        mov ecx,ebp
    L_00414098:
        mov dword ptr [ebx+20h],0Fh
    L_0041409f:
        call asm_FUN_00449870_00449870
    L_004140a4:
        mov esi,dword ptr [data_00491c10]
    L_004140aa:
        lea eax,[ebx+4]
    L_004140ad:
        xor ecx,ecx
    L_004140af:
        mov dword ptr [eax],ebx
    L_004140b1:
        mov dword ptr [eax+4],ecx
    L_004140b4:
        mov dword ptr [eax+8],ecx
    L_004140b7:
        cmp dword ptr [esi+72DAD4h],ecx
    L_004140bd:
        jne short L_004140c7
    L_004140bf:
        mov dword ptr [esi+72DAD4h],eax
    L_004140c5:
        jmp short L_004140e3
    L_004140c7:
        mov ecx,dword ptr [esi+72DAD8h]
    L_004140cd:
        mov edx,dword ptr [ecx+4]
    L_004140d0:
        test edx,edx
    L_004140d2:
        je short L_004140dd
    L_004140d4:
        mov dword ptr [eax+4],edx
    L_004140d7:
        mov edx,dword ptr [ecx+4]
    L_004140da:
        mov dword ptr [edx+8],eax
    L_004140dd:
        mov dword ptr [ecx+4],eax
    L_004140e0:
        mov dword ptr [eax+8],ecx
    L_004140e3:
        mov dword ptr [esi+72DAD8h],eax
    L_004140e9:
        mov ecx,dword ptr [esi+732454h]
    L_004140ef:
        inc ecx
    L_004140f0:
        mov eax,ecx
    L_004140f2:
        test eax,eax
    L_004140f4:
        mov dword ptr [esi+732454h],ecx
    L_004140fa:
        jne short L_00414103
    L_004140fc:
        inc eax
    L_004140fd:
        mov dword ptr [esi+732454h],eax
    L_00414103:
        mov eax,dword ptr [esi+732454h]
    L_00414109:
        mov dword ptr [ebx],eax
    L_0041410b:
        jmp short L_00414113
    L_0041410d:
        mov esi,dword ptr [data_00491c10]
    L_00414113:
        mov eax,dword ptr [data_00491fc4]
    L_00414118:
        test eax,eax
    L_0041411a:
        je asm_target_00414240
    L_00414120:
        mov ecx,dword ptr [edi+9EC8h]
    L_00414126:
        mov ebp,dword ptr [data_00474c74]
    L_0041412c:
        mov dword ptr [esp+0Ch],ecx
    L_00414130:
        call asm_FUN_00449950_00449950
    L_00414135:
        mov ebx,eax
    L_00414137:
        mov ecx,dword ptr [ebx+35Ch]
    L_0041413d:
        or ecx,40000000h
    L_00414143:
        add ebp,66h
    L_00414146:
        push ebp
    L_00414147:
        mov dword ptr [ebx+35Ch],ecx
    L_0041414d:
        mov ecx,dword ptr [esp+10h]
    L_00414151:
        push ebx
    L_00414152:
        mov dword ptr [ebx+20h],0Fh
    L_00414159:
        call asm_FUN_00449870_00449870
    L_0041415e:
        mov esi,dword ptr [data_00491c10]
    L_00414164:
        lea eax,[ebx+4]
    L_00414167:
        xor ecx,ecx
    L_00414169:
        mov dword ptr [eax],ebx
    L_0041416b:
        mov dword ptr [eax+4],ecx
    L_0041416e:
        mov dword ptr [eax+8],ecx
    L_00414171:
        cmp dword ptr [esi+72DAD4h],ecx
    L_00414177:
        jne short L_00414181
    L_00414179:
        mov dword ptr [esi+72DAD4h],eax
    L_0041417f:
        jmp short L_0041419d
    L_00414181:
        mov ecx,dword ptr [esi+72DAD8h]
    L_00414187:
        mov edx,dword ptr [ecx+4]
    L_0041418a:
        test edx,edx
    L_0041418c:
        je short L_00414197
    L_0041418e:
        mov dword ptr [eax+4],edx
    L_00414191:
        mov edx,dword ptr [ecx+4]
    L_00414194:
        mov dword ptr [edx+8],eax
    L_00414197:
        mov dword ptr [ecx+4],eax
    L_0041419a:
        mov dword ptr [eax+8],ecx
    L_0041419d:
        mov dword ptr [esi+72DAD8h],eax
    L_004141a3:
        mov ecx,dword ptr [esi+732454h]
    L_004141a9:
        inc ecx
    L_004141aa:
        mov eax,ecx
    L_004141ac:
        test eax,eax
    L_004141ae:
        mov dword ptr [esi+732454h],ecx
    L_004141b4:
        jne short L_004141bd
    L_004141b6:
        inc eax
    L_004141b7:
        mov dword ptr [esi+732454h],eax
    L_004141bd:
        mov eax,dword ptr [esi+732454h]
    L_004141c3:
        mov dword ptr [ebx],eax
    L_004141c5:
        mov ecx,dword ptr [esi+732454h]
    L_004141cb:
        test ecx,ecx
    L_004141cd:
        mov dword ptr [edi+9E50h],ecx
    L_004141d3:
        TH10_REL8(0x74, 0x004141d3, VA_asm_target_00414240)
    L_004141d5:
        mov eax,dword ptr [esi+72DAD4h]
    L_004141db:
        test eax,eax
    L_004141dd:
        je short L_004141ed
    L_004141df:
        nop
    L_004141e0:
        mov edx,dword ptr [eax]
    L_004141e2:
        cmp dword ptr [edx],ecx
    L_004141e4:
        je short L_00414206
    L_004141e6:
        mov eax,dword ptr [eax+4]
    L_004141e9:
        test eax,eax
    L_004141eb:
        jne short L_004141e0
    L_004141ed:
        mov eax,dword ptr [esi+72DADCh]
    L_004141f3:
        test eax,eax
    L_004141f5:
        TH10_REL8(0x74, 0x004141f5, VA_asm_target_00414240)
    L_004141f7:
        mov edx,dword ptr [eax]
    L_004141f9:
        cmp dword ptr [edx],ecx
    L_004141fb:
        je short L_00414206
    L_004141fd:
        mov eax,dword ptr [eax+4]
    L_00414200:
        test eax,eax
    L_00414202:
        jne short L_004141f7
    L_00414204:
        TH10_REL8(0xeb, 0x00414204, VA_asm_target_00414240)
    L_00414206:
        mov eax,dword ptr [eax]
    L_00414208:
        test eax,eax
    L_0041420a:
        TH10_REL8(0x74, 0x0041420a, VA_asm_target_00414240)
    L_0041420c:
        mov edx,dword ptr [eax+18h]
    L_0041420f:
        test edx,edx
    L_00414211:
        mov ecx,3
    L_00414216:
        mov word ptr [eax+304h],cx
    L_0041421d:
        TH10_REL8(0x75, 0x0041421d, VA_asm_target_00414240)
    L_0041421f:
        mov eax,dword ptr [eax+14h]
    L_00414222:
        test eax,eax
    L_00414224:
        TH10_REL8(0x74, 0x00414224, VA_asm_target_00414240)
    L_00414226:
        TH10_REL8(0xeb, 0x00414226, VA_asm_FUN_00413bc0_part_00414230)
    }
}

// 0x00414230..0x0041436C: FUN_00413bc0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00413bc0_part_00414230() {
    __asm {
    L_00414230:
        mov edx,dword ptr [eax]
    L_00414232:
        mov word ptr [edx+304h],cx
    L_00414239:
        mov eax,dword ptr [eax+4]
    L_0041423c:
        test eax,eax
    L_0041423e:
        jne short L_00414230
    L_00414240:
        mov ebx,dword ptr [data_00474c74]
    L_00414246:
        mov ebp,dword ptr [edi+9EC8h]
    L_0041424c:
        call asm_FUN_00449950_00449950
    L_00414251:
        mov esi,eax
    L_00414253:
        mov edx,dword ptr [esi+35Ch]
    L_00414259:
        add ebx,6Bh
    L_0041425c:
        push ebx
    L_0041425d:
        or edx,40000000h
    L_00414263:
        push esi
    L_00414264:
        mov ecx,ebp
    L_00414266:
        mov dword ptr [esi+20h],0Fh
    L_0041426d:
        mov dword ptr [esi+35Ch],edx
    L_00414273:
        call asm_FUN_00449870_00449870
    L_00414278:
        mov ecx,dword ptr [data_00491c10]
    L_0041427e:
        lea eax,[esi+4]
    L_00414281:
        xor edx,edx
    L_00414283:
        mov dword ptr [eax],esi
    L_00414285:
        mov dword ptr [eax+4],edx
    L_00414288:
        mov dword ptr [eax+8],edx
    L_0041428b:
        cmp dword ptr [ecx+72DAD4h],edx
    L_00414291:
        jne short L_0041429b
    L_00414293:
        mov dword ptr [ecx+72DAD4h],eax
    L_00414299:
        jmp short L_004142b7
    L_0041429b:
        mov edx,dword ptr [ecx+72DAD8h]
    L_004142a1:
        mov ebx,dword ptr [edx+4]
    L_004142a4:
        test ebx,ebx
    L_004142a6:
        je short L_004142b1
    L_004142a8:
        mov dword ptr [eax+4],ebx
    L_004142ab:
        mov ebx,dword ptr [edx+4]
    L_004142ae:
        mov dword ptr [ebx+8],eax
    L_004142b1:
        mov dword ptr [edx+4],eax
    L_004142b4:
        mov dword ptr [eax+8],edx
    L_004142b7:
        mov dword ptr [ecx+72DAD8h],eax
    L_004142bd:
        mov edx,dword ptr [ecx+732454h]
    L_004142c3:
        inc edx
    L_004142c4:
        xor ebx,ebx
    L_004142c6:
        mov eax,edx
    L_004142c8:
        cmp eax,ebx
    L_004142ca:
        mov dword ptr [ecx+732454h],edx
    L_004142d0:
        jne short L_004142d9
    L_004142d2:
        inc eax
    L_004142d3:
        mov dword ptr [ecx+732454h],eax
    L_004142d9:
        mov eax,dword ptr [ecx+732454h]
    L_004142df:
        mov dword ptr [esi],eax
    L_004142e1:
        mov edx,dword ptr [edi+9E50h]
    L_004142e7:
        cmp edx,ebx
    L_004142e9:
        mov eax,dword ptr [ecx+732454h]
    L_004142ef:
        mov dword ptr [edi+9E54h],eax
    L_004142f5:
        je short L_00414362
    L_004142f7:
        mov eax,dword ptr [ecx+72DAD4h]
    L_004142fd:
        cmp eax,ebx
    L_004142ff:
        je short L_0041430e
    L_00414301:
        mov esi,dword ptr [eax]
    L_00414303:
        cmp dword ptr [esi],edx
    L_00414305:
        je short L_00414330
    L_00414307:
        mov eax,dword ptr [eax+4]
    L_0041430a:
        cmp eax,ebx
    L_0041430c:
        jne short L_00414301
    L_0041430e:
        mov ecx,dword ptr [ecx+72DADCh]
    L_00414314:
        cmp ecx,ebx
    L_00414316:
        je short L_00414362
    L_00414318:
        mov eax,dword ptr [ecx]
    L_0041431a:
        cmp dword ptr [eax],edx
    L_0041431c:
        je short L_00414334
    L_0041431e:
        mov ecx,dword ptr [ecx+4]
    L_00414321:
        cmp ecx,ebx
    L_00414323:
        jne short L_00414318
    L_00414325:
        pop esi
    L_00414326:
        pop ebp
    L_00414327:
        mov dword ptr [edi+9E90h],ebx
    L_0041432d:
        pop ebx
    L_0041432e:
        pop ecx
    L_0041432f:
        ret
    L_00414330:
        mov eax,dword ptr [eax]
    L_00414332:
        jmp short L_00414336
    L_00414334:
        mov eax,dword ptr [ecx]
    L_00414336:
        cmp eax,ebx
    L_00414338:
        je short L_00414362
    L_0041433a:
        cmp dword ptr [eax+18h],ebx
    L_0041433d:
        mov ecx,3
    L_00414342:
        mov word ptr [eax+304h],cx
    L_00414349:
        jne short L_00414362
    L_0041434b:
        mov eax,dword ptr [eax+14h]
    L_0041434e:
        cmp eax,ebx
    L_00414350:
        je short L_00414362
    L_00414352:
        mov edx,dword ptr [eax]
    L_00414354:
        mov word ptr [edx+304h],cx
    L_0041435b:
        mov eax,dword ptr [eax+4]
    L_0041435e:
        cmp eax,ebx
    L_00414360:
        jne short L_00414352
    L_00414362:
        pop esi
    L_00414363:
        pop ebp
    L_00414364:
        mov dword ptr [edi+9E90h],ebx
    L_0041436a:
        pop ebx
    L_0041436b:
        pop ecx
    L_0041436c:
        ret
    }
}

// 0x004250B0..0x0042558C: FUN_004250b0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004250b0_004250b0() {
    __asm {
    L_004250b0:
        sub esp,18h
    L_004250b3:
        mov al,byte ptr [data_00474e5c]
    L_004250b8:
        push ebx
    L_004250b9:
        mov cl,al
    L_004250bb:
        push ebp
    L_004250bc:
        xor ebp,ebp
    L_004250be:
        xor ebx,ebx
    L_004250c0:
        and cl,50h
    L_004250c3:
        cmp cl,50h
    L_004250c6:
        push esi
    L_004250c7:
        mov dword ptr [esp+10h],ebp
    L_004250cb:
        mov dword ptr [esp+0Ch],ebx
    L_004250cf:
        mov esi,1
    L_004250d4:
        jne short L_004250e5
    L_004250d6:
        mov dword ptr [edi+454h],5
    L_004250e0:
        jmp asm_target_00425169
    L_004250e5:
        mov dl,al
    L_004250e7:
        and dl,60h
    L_004250ea:
        cmp dl,60h
    L_004250ed:
        jne short L_004250fb
    L_004250ef:
        mov dword ptr [edi+454h],7
    L_004250f9:
        jmp short L_00425169
    L_004250fb:
        mov cl,al
    L_004250fd:
        and cl,90h
    L_00425100:
        cmp cl,90h
    L_00425103:
        jne short L_00425111
    L_00425105:
        mov dword ptr [edi+454h],6
    L_0042510f:
        jmp short L_00425169
    L_00425111:
        mov dl,al
    L_00425113:
        and dl,0A0h
    L_00425116:
        cmp dl,0A0h
    L_00425119:
        jne short L_00425127
    L_0042511b:
        mov dword ptr [edi+454h],8
    L_00425125:
        jmp short L_00425169
    L_00425127:
        test al,20h
    L_00425129:
        je short L_00425137
    L_0042512b:
        mov dword ptr [edi+454h],2
    L_00425135:
        jmp short L_00425169
    L_00425137:
        test al,10h
    L_00425139:
        je short L_00425143
    L_0042513b:
        mov dword ptr [edi+454h],esi
    L_00425141:
        jmp short L_00425169
    L_00425143:
        test al,40h
    L_00425145:
        je short L_00425153
    L_00425147:
        mov dword ptr [edi+454h],3
    L_00425151:
        jmp short L_00425169
    L_00425153:
        test al,al
    L_00425155:
        jns short L_00425163
    L_00425157:
        mov dword ptr [edi+454h],4
    L_00425161:
        jmp short L_00425169
    L_00425163:
        mov dword ptr [edi+454h],ebp
    L_00425169:
        mov eax,dword ptr [data_00477704]
    L_0042516e:
        cmp eax,ebp
    L_00425170:
        je short L_004251ca
    L_00425172:
        cmp dword ptr [eax+60h],ebp
    L_00425175:
        je short L_004251ca
    L_00425177:
        cmp dword ptr [edi+48Ch],4
    L_0042517e:
        jl short L_004251ca
    L_00425180:
        mov eax,dword ptr [data_00474e5c]
    L_00425185:
        shr eax,2
    L_00425188:
        and eax,esi
    L_0042518a:
        mov dword ptr [edi+4474h],eax
    L_00425190:
        mov eax,dword ptr [data_00474c68]
    L_00425195:
        mov ecx,dword ptr [data_00474c6c]
    L_0042519b:
        lea edx,[ecx+eax*2]
    L_0042519e:
        add edx,eax
    L_004251a0:
        cmp edx,5
    L_004251a3:
        jne short L_004251da
    L_004251a5:
        test byte ptr [data_00474e5c],4
    L_004251ac:
        je short L_004251b6
    L_004251ae:
        mov dword ptr [edi+4308h],ebp
    L_004251b4:
        jmp short L_004251da
    L_004251b6:
        mov eax,dword ptr [edi+4308h]
    L_004251bc:
        cmp eax,1Eh
    L_004251bf:
        jge short L_004251da
    L_004251c1:
        inc eax
    L_004251c2:
        mov dword ptr [edi+4308h],eax
    L_004251c8:
        jmp short L_004251da
    L_004251ca:
        mov dword ptr [edi+4474h],ebp
    L_004251d0:
        mov dword ptr [edi+4308h],1Eh
    L_004251da:
        cmp dword ptr [edi+4474h],ebp
    L_004251e0:
        je asm_target_004252d0
    L_004251e6:
        cmp dword ptr [edi+329Ch],ebp
    L_004251ec:
        jne short L_0042524b
    L_004251ee:
        mov eax,dword ptr [data_004776f0]
    L_004251f3:
        mov esi,dword ptr [data_00491c10]
    L_004251f9:
        mov ebx,dword ptr [eax+3E0B50h]
    L_004251ff:
        call asm_FUN_00449950_00449950
    L_00425204:
        mov esi,eax
    L_00425206:
        mov edx,dword ptr [esi+35Ch]
    L_0042520c:
        push 160h
    L_00425211:
        or edx,40000000h
    L_00425217:
        push esi
    L_00425218:
        mov ecx,ebx
    L_0042521a:
        mov dword ptr [esi+20h],9
    L_00425221:
        mov dword ptr [esi+35Ch],edx
    L_00425227:
        call asm_FUN_00449870_00449870
    L_0042522c:
        mov edx,dword ptr [data_00491c10]
    L_00425232:
        mov ebx,esi
    L_00425234:
        lea eax,[esp+14h]
    L_00425238:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_0042523d:
        mov ecx,dword ptr [esp+14h]
    L_00425241:
        mov ebx,dword ptr [esp+0Ch]
    L_00425245:
        mov dword ptr [edi+329Ch],ecx
    L_0042524b:
        mov eax,dword ptr [edi+454h]
    L_00425251:
        dec eax
    L_00425252:
        cmp eax,7
    L_00425255:
        ja asm_target_004253b2
    L_0042525b:
        jmp dword ptr [eax*4+4256E8h]
    L_00425262:
        mov ebp,dword ptr [edi+3D8h]
    L_00425268:
        jmp asm_target_00425373
    L_0042526d:
        mov ebp,dword ptr [edi+3D8h]
    L_00425273:
        neg ebp
    L_00425275:
        jmp asm_target_00425373
    L_0042527a:
        mov ebx,dword ptr [edi+3D8h]
    L_00425280:
        neg ebx
    L_00425282:
        mov dword ptr [esp+0Ch],ebx
    L_00425286:
        jmp asm_target_004253b2
    L_0042528b:
        mov ebx,dword ptr [edi+3D8h]
    L_00425291:
        mov dword ptr [esp+0Ch],ebx
    L_00425295:
        jmp asm_target_004253b2
    L_0042529a:
        mov ebp,dword ptr [edi+3E0h]
    L_004252a0:
        neg ebp
    L_004252a2:
        jmp asm_target_0042536d
    L_004252a7:
        mov ebx,dword ptr [edi+3E0h]
    L_004252ad:
        mov ebp,ebx
    L_004252af:
        neg ebp
    L_004252b1:
        jmp asm_target_0042536f
    L_004252b6:
        mov ebp,dword ptr [edi+3E0h]
    L_004252bc:
        mov ebx,ebp
    L_004252be:
        neg ebx
    L_004252c0:
        jmp asm_target_0042536f
    L_004252c5:
        mov ebp,dword ptr [edi+3E0h]
    L_004252cb:
        jmp asm_target_0042536d
    L_004252d0:
        mov edx,dword ptr [edi+329Ch]
    L_004252d6:
        push edx
    L_004252d7:
        mov edx,dword ptr [data_00491c10]
    L_004252dd:
        call asm_AnimationManager_Find_004491c0
    L_004252e2:
        test eax,eax
    L_004252e4:
        je short L_004252f8
    L_004252e6:
        mov eax,dword ptr [edi+329Ch]
    L_004252ec:
        mov edx,dword ptr [data_00491c10]
    L_004252f2:
        push eax
    L_004252f3:
        call asm_AnimationManager_SetStopFrame_00449210
    L_004252f8:
        mov dword ptr [edi+329Ch],0
    L_00425302:
        mov eax,dword ptr [edi+454h]
    L_00425308:
        dec eax
    L_00425309:
        cmp eax,7
    L_0042530c:
        ja asm_target_004253b2
    L_00425312:
        jmp dword ptr [eax*4+425708h]
    L_00425319:
        mov ebp,dword ptr [edi+3D4h]
    L_0042531f:
        jmp short L_00425373
    L_00425321:
        mov ebp,dword ptr [edi+3D4h]
    L_00425327:
        neg ebp
    L_00425329:
        jmp short L_00425373
    L_0042532b:
        mov ebx,dword ptr [edi+3D4h]
    L_00425331:
        neg ebx
    L_00425333:
        mov dword ptr [esp+0Ch],ebx
    L_00425337:
        jmp short L_004253b2
    L_00425339:
        mov ebx,dword ptr [edi+3D4h]
    L_0042533f:
        mov dword ptr [esp+0Ch],ebx
    L_00425343:
        jmp short L_004253b2
    L_00425345:
        mov ebp,dword ptr [edi+3DCh]
    L_0042534b:
        neg ebp
    L_0042534d:
        jmp short L_0042536d
    L_0042534f:
        mov ebx,dword ptr [edi+3DCh]
    L_00425355:
        mov ebp,ebx
    L_00425357:
        neg ebp
    L_00425359:
        jmp short L_0042536f
    L_0042535b:
        mov ebp,dword ptr [edi+3DCh]
    L_00425361:
        mov ebx,ebp
    L_00425363:
        neg ebx
    L_00425365:
        jmp short L_0042536f
    L_00425367:
        mov ebp,dword ptr [edi+3DCh]
    L_0042536d:
        mov ebx,ebp
    L_0042536f:
        mov dword ptr [esp+0Ch],ebx
    L_00425373:
        test ebp,ebp
    L_00425375:
        mov dword ptr [esp+10h],ebp
    L_00425379:
        jge short L_004253b0
    L_0042537b:
        mov eax,dword ptr [edi+44Ch]
    L_00425381:
        test eax,eax
    L_00425383:
        jl short L_004253ae
    L_00425385:
        mov ecx,dword ptr [edi+10h]
    L_00425388:
        lea eax,[edi+14h]
    L_0042538b:
        mov ebx,1
    L_00425390:
        call asm_AnimationObject_LoadScript_0043e710
    L_00425395:
        mov ebx,dword ptr [esp+0Ch]
    L_00425399:
        test ebp,ebp
    L_0042539b:
        jle short L_004253d4
    L_0042539d:
        mov eax,dword ptr [edi+44Ch]
    L_004253a3:
        test eax,eax
    L_004253a5:
        jg short L_004253d2
    L_004253a7:
        mov ebx,3
    L_004253ac:
        jmp short L_004253e5
    L_004253ae:
        test ebp,ebp
    L_004253b0:
        jne short L_00425399
    L_004253b2:
        mov eax,dword ptr [edi+44Ch]
    L_004253b8:
        test eax,eax
    L_004253ba:
        jge short L_004253de
    L_004253bc:
        mov ecx,dword ptr [edi+10h]
    L_004253bf:
        lea eax,[edi+14h]
    L_004253c2:
        mov ebx,2
    L_004253c7:
        call asm_AnimationObject_LoadScript_0043e710
    L_004253cc:
        mov ebx,dword ptr [esp+0Ch]
    L_004253d0:
        jmp short L_004253d6
    L_004253d2:
        test ebp,ebp
    L_004253d4:
        jne short L_004253f4
    L_004253d6:
        mov eax,dword ptr [edi+44Ch]
    L_004253dc:
        test eax,eax
    L_004253de:
        jle short L_004253f4
    L_004253e0:
        mov ebx,4
    L_004253e5:
        mov ecx,dword ptr [edi+10h]
    L_004253e8:
        lea eax,[edi+14h]
    L_004253eb:
        call asm_AnimationObject_LoadScript_0043e710
    L_004253f0:
        mov ebx,dword ptr [esp+0Ch]
    L_004253f4:
        fild dword ptr [esp+10h]
    L_004253f8:
        mov dword ptr [edi+44Ch],ebp
    L_004253fe:
        mov dword ptr [edi+450h],ebx
    L_00425404:
        fmul dword ptr [data_00476f78]
    L_0042540a:
        call asm_FUN_00463b2c_00463b2c
    L_0042540f:
        fild dword ptr [esp+0Ch]
    L_00425413:
        mov dword ptr [edi+3F0h],eax
    L_00425419:
        fmul dword ptr [data_00476f78]
    L_0042541f:
        call asm_FUN_00463b2c_00463b2c
    L_00425424:
        mov ecx,dword ptr [edi+3F0h]
    L_0042542a:
        mov esi,dword ptr [edi+3D0h]
    L_00425430:
        mov dword ptr [edi+3F4h],eax
    L_00425436:
        mov eax,dword ptr [edi+3CCh]
    L_0042543c:
        mov edx,dword ptr [edi+3F4h]
    L_00425442:
        add eax,ecx
    L_00425444:
        add esi,edx
    L_00425446:
        cmp eax,0FFFFB820h
    L_0042544b:
        mov dword ptr [edi+3CCh],eax
    L_00425451:
        mov dword ptr [edi+3D0h],esi
    L_00425457:
        mov ecx,esi
    L_00425459:
        jge short L_00425467
    L_0042545b:
        mov dword ptr [edi+3CCh],0FFFFB820h
    L_00425465:
        jmp short L_00425478
    L_00425467:
        cmp eax,47E0h
    L_0042546c:
        jle short L_00425478
    L_0042546e:
        mov dword ptr [edi+3CCh],47E0h
    L_00425478:
        cmp ecx,0C80h
    L_0042547e:
        jge short L_0042548c
    L_00425480:
        mov dword ptr [edi+3D0h],0C80h
    L_0042548a:
        jmp short L_0042549e
    L_0042548c:
        cmp ecx,0A8C0h
    L_00425492:
        jle short L_0042549e
    L_00425494:
        mov dword ptr [edi+3D0h],0A8C0h
    L_0042549e:
        fild dword ptr [edi+3CCh]
    L_004254a4:
        mov edx,dword ptr [data_00491c10]
    L_004254aa:
        fmul dword ptr [data_00470b00]
    L_004254b0:
        fstp dword ptr [edi+3C0h]
    L_004254b6:
        fild dword ptr [edi+3D0h]
    L_004254bc:
        fmul dword ptr [data_00470b00]
    L_004254c2:
        fstp dword ptr [edi+3C4h]
    L_004254c8:
        mov eax,dword ptr [edi+329Ch]
    L_004254ce:
        push eax
    L_004254cf:
        call asm_AnimationManager_Find_004491c0
    L_004254d4:
        test eax,eax
    L_004254d6:
        jne short L_004254e0
    L_004254d8:
        mov dword ptr [edi+329Ch],eax
    L_004254de:
        jmp short L_00425520
    L_004254e0:
        fld dword ptr [edi+3C0h]
    L_004254e6:
        mov edx,dword ptr [edi+329Ch]
    L_004254ec:
        fadd dword ptr [data_00470b4c]
    L_004254f2:
        mov ecx,dword ptr [edi+3C8h]
    L_004254f8:
        push edx
    L_004254f9:
        mov edx,dword ptr [data_00491c10]
    L_004254ff:
        fstp dword ptr [esp+1Ch]
    L_00425503:
        lea esi,[esp+1Ch]
    L_00425507:
        fld dword ptr [edi+3C4h]
    L_0042550d:
        mov dword ptr [esp+24h],ecx
    L_00425511:
        fadd dword ptr [data_00470b48]
    L_00425517:
        fstp dword ptr [esp+20h]
    L_0042551b:
        call asm_AnimationManager_SetPosition_004492f0
    L_00425520:
        mov eax,dword ptr [edi+4474h]
    L_00425526:
        test eax,eax
    L_00425528:
        TH10_REL8(0x75, 0x00425528, VA_asm_target_004255a1)
    L_0042552a:
        test ebx,ebx
    L_0042552c:
        jne short L_00425532
    L_0042552e:
        test ebp,ebp
    L_00425530:
        TH10_REL8(0x74, 0x00425530, VA_asm_target_004255a1)
    L_00425532:
        mov ecx,dword ptr [edi+3500h]
    L_00425538:
        mov eax,20h
    L_0042553d:
        shl ecx,3
    L_00425540:
        cmp ecx,eax
    L_00425542:
        jge short L_00425584
    L_00425544:
        lea ecx,[edi+446Ch]
    L_0042554a:
        lea ebx,[ebx+force_disp32_zero]
    L_00425550:
        mov edx,dword ptr [edi+3500h]
    L_00425556:
        shl edx,6
    L_00425559:
        mov esi,dword ptr [edx+edi+436Ch]
    L_00425560:
        lea edx,[edx+edi+436Ch]
    L_00425567:
        mov dword ptr [ecx],esi
    L_00425569:
        mov edx,dword ptr [edx+4]
    L_0042556c:
        mov dword ptr [ecx+4],edx
    L_0042556f:
        mov edx,dword ptr [edi+3500h]
    L_00425575:
        dec eax
    L_00425576:
        shl edx,3
    L_00425579:
        sub ecx,8
    L_0042557c:
        cmp eax,edx
    L_0042557e:
        jg short L_00425550
    L_00425580:
        test eax,eax
    L_00425582:
        TH10_REL8(0x7e, 0x00425582, VA_asm_target_004255a1)
    L_00425584:
        lea ecx,[edi+eax*8+4370h]
    L_0042558b:
        TH10_REL8(0xeb, 0x0042558b, VA_asm_FUN_004250b0_part_00425590)
    }
}

// 0x00425590..0x004256E6: FUN_004250b0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004250b0_part_00425590() {
    __asm {
    L_00425590:
        mov edx,dword ptr [ecx-0Ch]
    L_00425593:
        mov dword ptr [ecx-4],edx
    L_00425596:
        mov edx,dword ptr [ecx-8]
    L_00425599:
        mov dword ptr [ecx],edx
    L_0042559b:
        add ecx,0FFFFFFF8h
    L_0042559e:
        dec eax
    L_0042559f:
        jne short L_00425590
    L_004255a1:
        mov eax,dword ptr [edi+3CCh]
    L_004255a7:
        mov dword ptr [edi+436Ch],eax
    L_004255ad:
        mov ecx,dword ptr [edi+3D0h]
    L_004255b3:
        mov dword ptr [edi+4370h],ecx
    L_004255b9:
        lea ebx,[edi+32E0h]
    L_004255bf:
        mov dword ptr [esp+10h],4
    L_004255c7:
        mov eax,dword ptr [ebx-40h]
    L_004255ca:
        test eax,eax
    L_004255cc:
        lea ecx,[ebx-40h]
    L_004255cf:
        je asm_target_004256c9
    L_004255d5:
        mov eax,dword ptr [edi+4474h]
    L_004255db:
        test eax,eax
    L_004255dd:
        lea esi,[ebx+0Ch]
    L_004255e0:
        jne short L_004255e5
    L_004255e2:
        lea esi,[ebx+4]
    L_004255e5:
        mov edx,dword ptr [edi+3CCh]
    L_004255eb:
        mov eax,dword ptr [esi]
    L_004255ed:
        mov ebp,dword ptr [esi+4]
    L_004255f0:
        add eax,edx
    L_004255f2:
        mov edx,dword ptr [edi+3D0h]
    L_004255f8:
        add edx,ebp
    L_004255fa:
        mov dword ptr [ebx-0Ch],eax
    L_004255fd:
        mov dword ptr [ebx-8],edx
    L_00425600:
        mov eax,dword ptr [ebx+50h]
    L_00425603:
        test eax,eax
    L_00425605:
        je short L_00425609
    L_00425607:
        call eax
    L_00425609:
        mov eax,dword ptr [ebx+4Ch]
    L_0042560c:
        test eax,eax
    L_0042560e:
        jne short L_00425676
    L_00425610:
        mov edx,dword ptr [edi+4308h]
    L_00425616:
        cmp edx,1Eh
    L_00425619:
        jl short L_00425688
    L_0042561b:
        mov ebp,dword ptr [ebx-0Ch]
    L_0042561e:
        mov ecx,dword ptr [ebx-4]
    L_00425621:
        mov esi,dword ptr [ebx]
    L_00425623:
        mov eax,ebp
    L_00425625:
        sub eax,ecx
    L_00425627:
        mov ecx,dword ptr [ebx-8]
    L_0042562a:
        imul eax,edx
    L_0042562d:
        sub ecx,esi
    L_0042562f:
        mov esi,eax
    L_00425631:
        imul ecx,edx
    L_00425634:
        mov eax,51EB851Fh
    L_00425639:
        imul esi
    L_0042563b:
        sar edx,5
    L_0042563e:
        mov esi,edx
    L_00425640:
        shr esi,1Fh
    L_00425643:
        add esi,edx
    L_00425645:
        mov eax,51EB851Fh
    L_0042564a:
        imul ecx
    L_0042564c:
        sar edx,5
    L_0042564f:
        mov eax,edx
    L_00425651:
        shr eax,1Fh
    L_00425654:
        add eax,edx
    L_00425656:
        test esi,esi
    L_00425658:
        jne short L_0042565e
    L_0042565a:
        test eax,eax
    L_0042565c:
        je short L_0042566c
    L_0042565e:
        mov edx,dword ptr [ebx-4]
    L_00425661:
        mov ecx,dword ptr [ebx]
    L_00425663:
        add edx,esi
    L_00425665:
        mov dword ptr [ebx-4],edx
    L_00425668:
        add ecx,eax
    L_0042566a:
        jmp short L_00425686
    L_0042566c:
        mov dword ptr [ebx-4],ebp
    L_0042566f:
        mov edx,dword ptr [ebx-8]
    L_00425672:
        mov dword ptr [ebx],edx
    L_00425674:
        jmp short L_00425688
    L_00425676:
        mov dword ptr [ebx+4Ch],0
    L_0042567d:
        mov eax,dword ptr [ebx-0Ch]
    L_00425680:
        mov dword ptr [ebx-4],eax
    L_00425683:
        mov ecx,dword ptr [ebx-8]
    L_00425686:
        mov dword ptr [ebx],ecx
    L_00425688:
        fild dword ptr [ebx-4]
    L_0042568b:
        mov edx,dword ptr [ebx+28h]
    L_0042568e:
        mov ebp,dword ptr [data_00491c10]
    L_00425694:
        push edx
    L_00425695:
        fmul dword ptr [data_00470b00]
    L_0042569b:
        lea esi,[esp+1Ch]
    L_0042569f:
        mov edx,ebp
    L_004256a1:
        mov dword ptr [esp+24h],0
    L_004256a9:
        fstp dword ptr [esp+1Ch]
    L_004256ad:
        fild dword ptr [ebx]
    L_004256af:
        fmul dword ptr [data_00470b00]
    L_004256b5:
        fstp dword ptr [esp+20h]
    L_004256b9:
        call asm_AnimationManager_SetTranslatedPosition_00449350
    L_004256be:
        mov eax,dword ptr [ebx+2Ch]
    L_004256c1:
        push eax
    L_004256c2:
        mov edx,ebp
    L_004256c4:
        call asm_AnimationManager_SetTranslatedPosition_00449350
    L_004256c9:
        mov eax,dword ptr [esp+10h]
    L_004256cd:
        add ebx,98h
    L_004256d3:
        dec eax
    L_004256d4:
        mov dword ptr [esp+10h],eax
    L_004256d8:
        jne asm_target_004255c7
    L_004256de:
        pop esi
    L_004256df:
        pop ebp
    L_004256e0:
        xor eax,eax
    L_004256e2:
        pop ebx
    L_004256e3:
        add esp,18h
    L_004256e6:
        ret
    }
}
