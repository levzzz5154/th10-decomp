#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004450E0..0x004451B2: FUN_004450e0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004450e0_004450e0() {
    __asm {
    L_004450e0:
        push esi
    L_004450e1:
        push edi
    L_004450e2:
        mov esi,ecx
    L_004450e4:
        mov edi,eax
    L_004450e6:
        mov eax,dword ptr [esi+3ADAC8h]
    L_004450ec:
        test eax,eax
    L_004450ee:
        je short L_004450f5
    L_004450f0:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_004450f5:
        cmp byte ptr [esi+3ADA6Ah],3
    L_004450fc:
        je short L_00445118
    L_004450fe:
        mov eax,dword ptr [data_00491c30]
    L_00445103:
        mov ecx,dword ptr [eax]
    L_00445105:
        push 144h
    L_0044510a:
        push eax
    L_0044510b:
        call dword ptr [ecx+164h]
    L_00445111:
        mov byte ptr [esi+3ADA6Ah],3
    L_00445118:
        mov eax,esi
    L_0044511a:
        call asm_AnmManager_SyncEntityRenderStateRetail_004425a0
    L_0044511f:
        mov edx,dword ptr [edi+394h]
    L_00445125:
        mov eax,dword ptr [edx+4]
    L_00445128:
        cmp dword ptr [esi+3ADA64h],eax
    L_0044512e:
        je short L_00445148
    L_00445130:
        push eax
    L_00445131:
        mov dword ptr [esi+3ADA64h],eax
    L_00445137:
        mov ecx,dword ptr [data_00491c30]
    L_0044513d:
        mov edx,dword ptr [ecx]
    L_0044513f:
        push 0
    L_00445141:
        push ecx
    L_00445142:
        call dword ptr [edx+104h]
    L_00445148:
        mov esi,dword ptr [data_00491c10]
    L_0044514e:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00445153:
        mov eax,dword ptr [data_00491c30]
    L_00445158:
        mov ecx,dword ptr [eax]
    L_0044515a:
        push 0
    L_0044515c:
        push 0Eh
    L_0044515e:
        push eax
    L_0044515f:
        call dword ptr [ecx+0E4h]
    L_00445165:
        mov eax,dword ptr [data_00491c30]
    L_0044516a:
        mov edx,dword ptr [eax]
    L_0044516c:
        push 0
    L_0044516e:
        push 6
    L_00445170:
        push 0
    L_00445172:
        push eax
    L_00445173:
        call dword ptr [edx+10Ch]
    L_00445179:
        mov eax,dword ptr [data_00491c30]
    L_0044517e:
        mov ecx,dword ptr [eax]
    L_00445180:
        push 0
    L_00445182:
        push 3
    L_00445184:
        push 0
    L_00445186:
        push eax
    L_00445187:
        call dword ptr [ecx+10Ch]
    L_0044518d:
        mov ecx,dword ptr [esp+0Ch]
    L_00445191:
        mov eax,dword ptr [data_00491c30]
    L_00445196:
        mov edx,dword ptr [eax]
    L_00445198:
        push 1Ch
    L_0044519a:
        push ecx
    L_0044519b:
        mov ecx,dword ptr [esp+18h]
    L_0044519f:
        add ecx,0FFFFFFFEh
    L_004451a2:
        push ecx
    L_004451a3:
        push 6
    L_004451a5:
        push eax
    L_004451a6:
        call dword ptr [edx+14Ch]
    L_004451ac:
        pop edi
    L_004451ad:
        xor eax,eax
    L_004451af:
        pop esi
    L_004451b0:
        ret 8
    }
}
