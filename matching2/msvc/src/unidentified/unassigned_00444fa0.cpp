#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00444FA0..0x004450DA: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00444fa0() {
    __asm {
    L_00444fa0:
        push esi
    L_00444fa1:
        mov esi,eax
    L_00444fa3:
        mov eax,dword ptr [esi+3ADAC8h]
    L_00444fa9:
        test eax,eax
    L_00444fab:
        je short L_00444fb2
    L_00444fad:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00444fb2:
        cmp byte ptr [esi+3ADA6Ah],4
    L_00444fb9:
        je short L_00444fd2
    L_00444fbb:
        mov eax,dword ptr [data_00491c30]
    L_00444fc0:
        mov ecx,dword ptr [eax]
    L_00444fc2:
        push 44h
    L_00444fc4:
        push eax
    L_00444fc5:
        call dword ptr [ecx+164h]
    L_00444fcb:
        mov byte ptr [esi+3ADA6Ah],4
    L_00444fd2:
        mov eax,esi
    L_00444fd4:
        call asm_AnmManager_SyncEntityRenderStateRetail_004425a0
    L_00444fd9:
        mov eax,dword ptr [data_00491c30]
    L_00444fde:
        mov edx,dword ptr [eax]
    L_00444fe0:
        push 2
    L_00444fe2:
        push 4
    L_00444fe4:
        push 0
    L_00444fe6:
        push eax
    L_00444fe7:
        call dword ptr [edx+10Ch]
    L_00444fed:
        mov eax,dword ptr [data_00491c30]
    L_00444ff2:
        mov ecx,dword ptr [eax]
    L_00444ff4:
        push 2
    L_00444ff6:
        push 1
    L_00444ff8:
        push 0
    L_00444ffa:
        push eax
    L_00444ffb:
        call dword ptr [ecx+10Ch]
    L_00445001:
        mov eax,dword ptr [data_00491c30]
    L_00445006:
        mov edx,dword ptr [eax]
    L_00445008:
        push 0
    L_0044500a:
        push 5
    L_0044500c:
        push 0
    L_0044500e:
        push eax
    L_0044500f:
        call dword ptr [edx+10Ch]
    L_00445015:
        mov eax,dword ptr [data_00491c30]
    L_0044501a:
        mov ecx,dword ptr [eax]
    L_0044501c:
        push 0
    L_0044501e:
        push 2
    L_00445020:
        push 0
    L_00445022:
        push eax
    L_00445023:
        call dword ptr [ecx+10Ch]
    L_00445029:
        mov esi,dword ptr [data_00491c10]
    L_0044502f:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00445034:
        mov eax,dword ptr [data_00491c30]
    L_00445039:
        mov edx,dword ptr [eax]
    L_0044503b:
        push 0
    L_0044503d:
        push 0Eh
    L_0044503f:
        push eax
    L_00445040:
        call dword ptr [edx+0E4h]
    L_00445046:
        mov edx,dword ptr [esp+8]
    L_0044504a:
        mov eax,dword ptr [data_00491c30]
    L_0044504f:
        mov ecx,dword ptr [eax]
    L_00445051:
        push 14h
    L_00445053:
        push edx
    L_00445054:
        mov edx,dword ptr [esp+14h]
    L_00445058:
        add edx,0FFFFFFFEh
    L_0044505b:
        push edx
    L_0044505c:
        push 6
    L_0044505e:
        push eax
    L_0044505f:
        call dword ptr [ecx+14Ch]
    L_00445065:
        mov eax,dword ptr [data_00491c10]
    L_0044506a:
        push 4
    L_0044506c:
        mov cl,0FFh
    L_0044506e:
        push 4
    L_00445070:
        mov byte ptr [eax+3ADA6Ah],cl
    L_00445076:
        mov byte ptr [eax+3ADA69h],cl
    L_0044507c:
        mov byte ptr [eax+3ADA68h],3
    L_00445083:
        mov byte ptr [eax+3ADA6Bh],cl
    L_00445089:
        mov eax,dword ptr [data_00491c30]
    L_0044508e:
        mov ecx,dword ptr [eax]
    L_00445090:
        push 0
    L_00445092:
        push eax
    L_00445093:
        call dword ptr [ecx+10Ch]
    L_00445099:
        mov eax,dword ptr [data_00491c30]
    L_0044509e:
        mov edx,dword ptr [eax]
    L_004450a0:
        push 4
    L_004450a2:
        push 1
    L_004450a4:
        push 0
    L_004450a6:
        push eax
    L_004450a7:
        call dword ptr [edx+10Ch]
    L_004450ad:
        mov eax,dword ptr [data_00491c30]
    L_004450b2:
        mov ecx,dword ptr [eax]
    L_004450b4:
        push 2
    L_004450b6:
        push 5
    L_004450b8:
        push 0
    L_004450ba:
        push eax
    L_004450bb:
        call dword ptr [ecx+10Ch]
    L_004450c1:
        mov eax,dword ptr [data_00491c30]
    L_004450c6:
        mov edx,dword ptr [eax]
    L_004450c8:
        push 2
    L_004450ca:
        push 2
    L_004450cc:
        push 0
    L_004450ce:
        push eax
    L_004450cf:
        call dword ptr [edx+10Ch]
    L_004450d5:
        xor eax,eax
    L_004450d7:
        pop esi
    L_004450d8:
        ret 8
    }
}
