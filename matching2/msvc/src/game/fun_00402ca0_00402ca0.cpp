#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00402160..0x0040221B: ConstructGameState
// Naked body preserves the retail register/stack ABI.

// 0x00402CA0..0x00403040: FUN_00402ca0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00402ca0_00402ca0() {
    __asm {
    L_00402ca0:
        push ebp
    L_00402ca1:
        mov ebp,dword ptr [esp+8]
    L_00402ca5:
        mov eax,dword ptr [ebp+2A18h]
    L_00402cab:
        test al,8
    L_00402cad:
        je short L_00402cb8
    L_00402caf:
        mov eax,1
    L_00402cb4:
        pop ebp
    L_00402cb5:
        ret 4
    L_00402cb8:
        push ebx
    L_00402cb9:
        push esi
    L_00402cba:
        xor ebx,ebx
    L_00402cbc:
        test al,4
    L_00402cbe:
        push edi
    L_00402cbf:
        je short L_00402cce
    L_00402cc1:
        cmp dword ptr [ebp+2A20h],3Ch
    L_00402cc8:
        jge asm_target_00402e86
    L_00402cce:
        mov esi,dword ptr [data_00491c10]
    L_00402cd4:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402cd9:
        mov eax,dword ptr [data_00491e64]
    L_00402cde:
        mov dword ptr [ebp+2B34h],eax
    L_00402ce4:
        mov ecx,dword ptr [data_00491e68]
    L_00402cea:
        mov dword ptr [ebp+2B38h],ecx
    L_00402cf0:
        lea esi,[ebp+2A4Ch]
    L_00402cf6:
        mov ecx,46h
    L_00402cfb:
        mov edi,491D7Ch
    L_00402d00:
        rep movsd
    L_00402d02:
        mov edi,491D7Ch
    L_00402d07:
        mov dword ptr [data_00491fac],edi
    L_00402d0d:
        call asm_FUN_004215a0_004215a0
    L_00402d12:
        mov ecx,dword ptr [data_00491fac]
    L_00402d18:
        mov eax,dword ptr [data_00491c30]
    L_00402d1d:
        mov edx,dword ptr [eax]
    L_00402d1f:
        add ecx,0CCh
    L_00402d25:
        push ecx
    L_00402d26:
        push eax
    L_00402d27:
        call dword ptr [edx+0BCh]
    L_00402d2d:
        mov eax,dword ptr [data_00492378]
    L_00402d32:
        mov edi,1
    L_00402d37:
        cmp eax,edi
    L_00402d39:
        mov dword ptr [data_00491fb0],ebx
    L_00402d3f:
        je short L_00402d63
    L_00402d41:
        mov esi,dword ptr [data_00491c10]
    L_00402d47:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402d4c:
        mov eax,dword ptr [data_00491c30]
    L_00402d51:
        push edi
    L_00402d52:
        push 1Ch
    L_00402d54:
        mov dword ptr [data_00492378],edi
    L_00402d5a:
        mov edx,dword ptr [eax]
    L_00402d5c:
        push eax
    L_00402d5d:
        call dword ptr [edx+0E4h]
    L_00402d63:
        mov esi,dword ptr [data_00491c10]
    L_00402d69:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402d6e:
        mov eax,dword ptr [data_00491c30]
    L_00402d73:
        mov ecx,dword ptr [eax]
    L_00402d75:
        push ebx
    L_00402d76:
        push 0Eh
    L_00402d78:
        push eax
    L_00402d79:
        call dword ptr [ecx+0E4h]
    L_00402d7f:
        mov esi,dword ptr [data_00491c10]
    L_00402d85:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402d8a:
        mov eax,dword ptr [data_00491c30]
    L_00402d8f:
        mov edx,dword ptr [eax]
    L_00402d91:
        push 8
    L_00402d93:
        push 17h
    L_00402d95:
        push eax
    L_00402d96:
        call dword ptr [edx+0E4h]
    L_00402d9c:
        mov edi,dword ptr [data_00491c10]
    L_00402da2:
        mov eax,11h
    L_00402da7:
        call asm_AnimationManager_RenderBucket_00448980
    L_00402dac:
        mov esi,dword ptr [data_00491c10]
    L_00402db2:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402db7:
        mov eax,dword ptr [data_00491c30]
    L_00402dbc:
        mov ecx,dword ptr [eax]
    L_00402dbe:
        push 4
    L_00402dc0:
        push 17h
    L_00402dc2:
        push eax
    L_00402dc3:
        call dword ptr [ecx+0E4h]
    L_00402dc9:
        cmp dword ptr [data_00492378],ebx
    L_00402dcf:
        je short L_00402df3
    L_00402dd1:
        mov esi,dword ptr [data_00491c10]
    L_00402dd7:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402ddc:
        mov eax,dword ptr [data_00491c30]
    L_00402de1:
        push ebx
    L_00402de2:
        push 1Ch
    L_00402de4:
        mov dword ptr [data_00492378],ebx
    L_00402dea:
        mov edx,dword ptr [eax]
    L_00402dec:
        push eax
    L_00402ded:
        call dword ptr [edx+0E4h]
    L_00402df3:
        mov edi,dword ptr [data_00491c10]
    L_00402df9:
        mov eax,12h
    L_00402dfe:
        call asm_AnimationManager_RenderBucket_00448980
    L_00402e03:
        mov esi,dword ptr [data_00491c10]
    L_00402e09:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402e0e:
        mov eax,dword ptr [data_00491c30]
    L_00402e13:
        mov ecx,dword ptr [eax]
    L_00402e15:
        push 4
    L_00402e17:
        push 17h
    L_00402e19:
        push eax
    L_00402e1a:
        call dword ptr [ecx+0E4h]
    L_00402e20:
        mov esi,dword ptr [data_00491c10]
    L_00402e26:
        mov edi,dword ptr [ebp+2B60h]
    L_00402e2c:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402e31:
        mov eax,dword ptr [data_00491c30]
    L_00402e36:
        mov edx,dword ptr [eax]
    L_00402e38:
        push edi
    L_00402e39:
        push 22h
    L_00402e3b:
        push eax
    L_00402e3c:
        call dword ptr [edx+0E4h]
    L_00402e42:
        mov esi,dword ptr [data_00491c10]
    L_00402e48:
        mov edi,dword ptr [ebp+2B48h]
    L_00402e4e:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402e53:
        mov eax,dword ptr [data_00491c30]
    L_00402e58:
        mov ecx,dword ptr [eax]
    L_00402e5a:
        push edi
    L_00402e5b:
        push 24h
    L_00402e5d:
        push eax
    L_00402e5e:
        call dword ptr [ecx+0E4h]
    L_00402e64:
        mov esi,dword ptr [data_00491c10]
    L_00402e6a:
        mov edi,dword ptr [ebp+2B4Ch]
    L_00402e70:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402e75:
        mov eax,dword ptr [data_00491c30]
    L_00402e7a:
        mov edx,dword ptr [eax]
    L_00402e7c:
        push edi
    L_00402e7d:
        push 25h
    L_00402e7f:
        push eax
    L_00402e80:
        call dword ptr [edx+0E4h]
    L_00402e86:
        mov eax,dword ptr [ebp+2A18h]
    L_00402e8c:
        test al,4
    L_00402e8e:
        je short L_00402e9f
    L_00402e90:
        cmp dword ptr [ebp+2A20h],1Eh
    L_00402e97:
        jl short L_00402e9f
    L_00402e99:
        mov byte ptr [ebp+1EEBh],bl
    L_00402e9f:
        test al,1
    L_00402ea1:
        je short L_00402f1c
    L_00402ea3:
        mov esi,dword ptr [data_00491c10]
    L_00402ea9:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402eae:
        mov eax,dword ptr [data_00491c30]
    L_00402eb3:
        mov ecx,dword ptr [eax]
    L_00402eb5:
        push ebx
    L_00402eb6:
        push 0Eh
    L_00402eb8:
        push eax
    L_00402eb9:
        call dword ptr [ecx+0E4h]
    L_00402ebf:
        mov eax,dword ptr [data_00492378]
    L_00402ec4:
        mov edi,1
    L_00402ec9:
        cmp eax,edi
    L_00402ecb:
        je short L_00402eef
    L_00402ecd:
        mov esi,dword ptr [data_00491c10]
    L_00402ed3:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402ed8:
        mov eax,dword ptr [data_00491c30]
    L_00402edd:
        push edi
    L_00402ede:
        push 1Ch
    L_00402ee0:
        mov dword ptr [data_00492378],edi
    L_00402ee6:
        mov edx,dword ptr [eax]
    L_00402ee8:
        push eax
    L_00402ee9:
        call dword ptr [edx+0E4h]
    L_00402eef:
        push 8
    L_00402ef1:
        push ebp
    L_00402ef2:
        call asm_FUN_00403a30_00403a30
    L_00402ef7:
        push 9
    L_00402ef9:
        push ebp
    L_00402efa:
        call asm_FUN_00403a30_00403a30
    L_00402eff:
        push 0Ah
    L_00402f01:
        push ebp
    L_00402f02:
        call asm_FUN_00403a30_00403a30
    L_00402f07:
        push 0Bh
    L_00402f09:
        push ebp
    L_00402f0a:
        call asm_FUN_00403a30_00403a30
    L_00402f0f:
        mov esi,dword ptr [data_00491c10]
    L_00402f15:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402f1a:
        jmp short L_00402f21
    L_00402f1c:
        mov edi,1
    L_00402f21:
        mov esi,dword ptr [data_00491c10]
    L_00402f27:
        mov dword ptr [esi+73245Ch],ebx
    L_00402f2d:
        mov dword ptr [esi+732458h],80808080h
    L_00402f37:
        cmp dword ptr [ebp+1EECh],ebx
    L_00402f3d:
        je short L_00402f4f
    L_00402f3f:
        mov dword ptr [esi+73245Ch],edi
    L_00402f45:
        mov dword ptr [esi+732458h],0FF404040h
    L_00402f4f:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402f54:
        mov eax,dword ptr [data_00491c30]
    L_00402f59:
        mov ecx,dword ptr [eax]
    L_00402f5b:
        push ebx
    L_00402f5c:
        push 0Eh
    L_00402f5e:
        push eax
    L_00402f5f:
        call dword ptr [ecx+0E4h]
    L_00402f65:
        mov esi,dword ptr [data_00491c10]
    L_00402f6b:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402f70:
        mov eax,dword ptr [data_00491c30]
    L_00402f75:
        mov edx,dword ptr [eax]
    L_00402f77:
        push 8
    L_00402f79:
        push 17h
    L_00402f7b:
        push eax
    L_00402f7c:
        call dword ptr [edx+0E4h]
    L_00402f82:
        cmp dword ptr [ebp+2A20h],ebx
    L_00402f88:
        jle short L_00402fd5
    L_00402f8a:
        push 0BF800000h
    L_00402f8f:
        lea esi,[ebp+2A1Ch]
    L_00402f95:
        call asm_FrameTimer_Advance_0044bf40
    L_00402f9a:
        cmp dword ptr [ebp+2A20h],ebx
    L_00402fa0:
        jg short L_00402fd5
    L_00402fa2:
        mov eax,dword ptr [ebp+2A18h]
    L_00402fa8:
        test al,2
    L_00402faa:
        mov byte ptr [ebp+1EEBh],0FFh
    L_00402fb1:
        je short L_00402fbc
    L_00402fb3:
        or eax,8
    L_00402fb6:
        mov dword ptr [ebp+2A18h],eax
    L_00402fbc:
        mov eax,dword ptr [ebp+2A18h]
    L_00402fc2:
        and eax,0FFFFFFF9h
    L_00402fc5:
        mov dword ptr [ebp+1EE8h],0FFFFFFh
    L_00402fcf:
        mov dword ptr [ebp+2A18h],eax
    L_00402fd5:
        mov esi,dword ptr [data_00491c10]
    L_00402fdb:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402fe0:
        mov eax,dword ptr [data_00491c30]
    L_00402fe5:
        mov ecx,dword ptr [eax]
    L_00402fe7:
        push ebx
    L_00402fe8:
        push 0Eh
    L_00402fea:
        push eax
    L_00402feb:
        call dword ptr [ecx+0E4h]
    L_00402ff1:
        mov esi,dword ptr [data_00491c10]
    L_00402ff7:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402ffc:
        mov eax,dword ptr [data_00491c30]
    L_00403001:
        mov edx,dword ptr [eax]
    L_00403003:
        push 8
    L_00403005:
        push 17h
    L_00403007:
        push eax
    L_00403008:
        call dword ptr [edx+0E4h]
    L_0040300e:
        cmp dword ptr [data_00492378],ebx
    L_00403014:
        je short L_00403038
    L_00403016:
        mov esi,dword ptr [data_00491c10]
    L_0040301c:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00403021:
        mov eax,dword ptr [data_00491c30]
    L_00403026:
        push ebx
    L_00403027:
        push 1Ch
    L_00403029:
        mov dword ptr [data_00492378],ebx
    L_0040302f:
        mov ecx,dword ptr [eax]
    L_00403031:
        push eax
    L_00403032:
        call dword ptr [ecx+0E4h]
    L_00403038:
        mov eax,edi
    L_0040303a:
        pop edi
    L_0040303b:
        pop esi
    L_0040303c:
        pop ebx
    L_0040303d:
        pop ebp
    L_0040303e:
        ret 4
    }
}
