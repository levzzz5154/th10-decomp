#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00444CE0..0x00444DBF: FUN_00444ce0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00444ce0_00444ce0() {
    __asm {
    L_00444ce0:
        push esi
    L_00444ce1:
        push edi
    L_00444ce2:
        mov edi,eax
    L_00444ce4:
        mov eax,dword ptr [edi+35Ch]
    L_00444cea:
        test al,1
    L_00444cec:
        mov esi,ecx
    L_00444cee:
        je short L_00444cf4
    L_00444cf0:
        test al,2
    L_00444cf2:
        jne short L_00444cfc
    L_00444cf4:
        pop edi
    L_00444cf5:
        or eax,0FFFFFFFFh
    L_00444cf8:
        pop esi
    L_00444cf9:
        ret 8
    L_00444cfc:
        mov al,byte ptr [edi+2FFh]
    L_00444d02:
        test al,al
    L_00444d04:
        jne short L_00444d10
    L_00444d06:
        pop edi
    L_00444d07:
        mov eax,0FFFFFFFFh
    L_00444d0c:
        pop esi
    L_00444d0d:
        ret 8
    L_00444d10:
        mov eax,dword ptr [esi+3ADAC8h]
    L_00444d16:
        test eax,eax
    L_00444d18:
        je short L_00444d1f
    L_00444d1a:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00444d1f:
        mov eax,dword ptr [edi+394h]
    L_00444d25:
        mov eax,dword ptr [eax+4]
    L_00444d28:
        cmp dword ptr [esi+3ADA64h],eax
    L_00444d2e:
        je short L_00444d48
    L_00444d30:
        push eax
    L_00444d31:
        mov dword ptr [esi+3ADA64h],eax
    L_00444d37:
        mov ecx,dword ptr [data_00491c30]
    L_00444d3d:
        mov edx,dword ptr [ecx]
    L_00444d3f:
        push 0
    L_00444d41:
        push ecx
    L_00444d42:
        call dword ptr [edx+104h]
    L_00444d48:
        cmp byte ptr [esi+3ADA6Ah],3
    L_00444d4f:
        je short L_00444d6b
    L_00444d51:
        mov eax,dword ptr [data_00491c30]
    L_00444d56:
        mov ecx,dword ptr [eax]
    L_00444d58:
        push 144h
    L_00444d5d:
        push eax
    L_00444d5e:
        call dword ptr [ecx+164h]
    L_00444d64:
        mov byte ptr [esi+3ADA6Ah],3
    L_00444d6b:
        mov eax,esi
    L_00444d6d:
        call asm_AnmManager_SyncEntityRenderStateRetail_004425a0
    L_00444d72:
        mov eax,dword ptr [data_00491c30]
    L_00444d77:
        mov edx,dword ptr [eax]
    L_00444d79:
        push 0
    L_00444d7b:
        push 6
    L_00444d7d:
        push 0
    L_00444d7f:
        push eax
    L_00444d80:
        call dword ptr [edx+10Ch]
    L_00444d86:
        mov eax,dword ptr [data_00491c30]
    L_00444d8b:
        mov ecx,dword ptr [eax]
    L_00444d8d:
        push 0
    L_00444d8f:
        push 3
    L_00444d91:
        push 0
    L_00444d93:
        push eax
    L_00444d94:
        call dword ptr [ecx+10Ch]
    L_00444d9a:
        mov ecx,dword ptr [esp+0Ch]
    L_00444d9e:
        mov eax,dword ptr [data_00491c30]
    L_00444da3:
        mov edx,dword ptr [eax]
    L_00444da5:
        push 1Ch
    L_00444da7:
        push ecx
    L_00444da8:
        mov ecx,dword ptr [esp+18h]
    L_00444dac:
        add ecx,0FFFFFFFEh
    L_00444daf:
        push ecx
    L_00444db0:
        push 5
    L_00444db2:
        push eax
    L_00444db3:
        call dword ptr [edx+14Ch]
    L_00444db9:
        pop edi
    L_00444dba:
        xor eax,eax
    L_00444dbc:
        pop esi
    L_00444dbd:
        ret 8
    }
}
