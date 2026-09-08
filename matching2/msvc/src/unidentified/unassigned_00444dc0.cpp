#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00444DC0..0x00444E50: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00444dc0() {
    __asm {
    L_00444dc0:
        push esi
    L_00444dc1:
        push edi
    L_00444dc2:
        mov edi,eax
    L_00444dc4:
        mov eax,dword ptr [edi+35Ch]
    L_00444dca:
        test al,1
    L_00444dcc:
        mov esi,ecx
    L_00444dce:
        je short L_00444dd4
    L_00444dd0:
        test al,2
    L_00444dd2:
        jne short L_00444ddc
    L_00444dd4:
        pop edi
    L_00444dd5:
        or eax,0FFFFFFFFh
    L_00444dd8:
        pop esi
    L_00444dd9:
        ret 4
    L_00444ddc:
        mov al,byte ptr [edi+2FFh]
    L_00444de2:
        test al,al
    L_00444de4:
        jne short L_00444df0
    L_00444de6:
        pop edi
    L_00444de7:
        mov eax,0FFFFFFFFh
    L_00444dec:
        pop esi
    L_00444ded:
        ret 4
    L_00444df0:
        mov eax,dword ptr [edi+394h]
    L_00444df6:
        mov eax,dword ptr [eax+4]
    L_00444df9:
        cmp dword ptr [esi+3ADA64h],eax
    L_00444dff:
        je short L_00444e23
    L_00444e01:
        mov dword ptr [esi+3ADA64h],eax
    L_00444e07:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00444e0c:
        mov edx,dword ptr [esi+3ADA64h]
    L_00444e12:
        mov eax,dword ptr [data_00491c30]
    L_00444e17:
        mov ecx,dword ptr [eax]
    L_00444e19:
        push edx
    L_00444e1a:
        push 0
    L_00444e1c:
        push eax
    L_00444e1d:
        call dword ptr [ecx+104h]
    L_00444e23:
        cmp byte ptr [esi+3ADA6Ah],1
    L_00444e2a:
        je short L_00444e38
    L_00444e2c:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00444e31:
        mov byte ptr [esi+3ADA6Ah],1
    L_00444e38:
        mov eax,esi
    L_00444e3a:
        call asm_AnmManager_SyncEntityRenderStateRetail_004425a0
    L_00444e3f:
        mov edx,dword ptr [esp+0Ch]
    L_00444e43:
        mov eax,esi
    L_00444e45:
        call asm_AnimationManager_AppendQuadVertices_00442fe0
    L_00444e4a:
        pop edi
    L_00444e4b:
        xor eax,eax
    L_00444e4d:
        pop esi
    L_00444e4e:
        ret 4
    }
}
