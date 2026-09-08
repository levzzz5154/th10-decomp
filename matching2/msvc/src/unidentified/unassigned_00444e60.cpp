#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00444E60..0x00444F9A: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00444e60() {
    __asm {
    L_00444e60:
        push esi
    L_00444e61:
        mov esi,eax
    L_00444e63:
        mov eax,dword ptr [esi+3ADAC8h]
    L_00444e69:
        test eax,eax
    L_00444e6b:
        je short L_00444e72
    L_00444e6d:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00444e72:
        cmp byte ptr [esi+3ADA6Ah],4
    L_00444e79:
        je short L_00444e92
    L_00444e7b:
        mov eax,dword ptr [data_00491c30]
    L_00444e80:
        mov ecx,dword ptr [eax]
    L_00444e82:
        push 44h
    L_00444e84:
        push eax
    L_00444e85:
        call dword ptr [ecx+164h]
    L_00444e8b:
        mov byte ptr [esi+3ADA6Ah],4
    L_00444e92:
        mov eax,esi
    L_00444e94:
        call asm_AnmManager_SyncEntityRenderStateRetail_004425a0
    L_00444e99:
        mov eax,dword ptr [data_00491c30]
    L_00444e9e:
        mov edx,dword ptr [eax]
    L_00444ea0:
        push 2
    L_00444ea2:
        push 4
    L_00444ea4:
        push 0
    L_00444ea6:
        push eax
    L_00444ea7:
        call dword ptr [edx+10Ch]
    L_00444ead:
        mov eax,dword ptr [data_00491c30]
    L_00444eb2:
        mov ecx,dword ptr [eax]
    L_00444eb4:
        push 2
    L_00444eb6:
        push 1
    L_00444eb8:
        push 0
    L_00444eba:
        push eax
    L_00444ebb:
        call dword ptr [ecx+10Ch]
    L_00444ec1:
        mov eax,dword ptr [data_00491c30]
    L_00444ec6:
        mov edx,dword ptr [eax]
    L_00444ec8:
        push 0
    L_00444eca:
        push 5
    L_00444ecc:
        push 0
    L_00444ece:
        push eax
    L_00444ecf:
        call dword ptr [edx+10Ch]
    L_00444ed5:
        mov eax,dword ptr [data_00491c30]
    L_00444eda:
        mov ecx,dword ptr [eax]
    L_00444edc:
        push 0
    L_00444ede:
        push 2
    L_00444ee0:
        push 0
    L_00444ee2:
        push eax
    L_00444ee3:
        call dword ptr [ecx+10Ch]
    L_00444ee9:
        mov esi,dword ptr [data_00491c10]
    L_00444eef:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00444ef4:
        mov eax,dword ptr [data_00491c30]
    L_00444ef9:
        mov edx,dword ptr [eax]
    L_00444efb:
        push 0
    L_00444efd:
        push 0Eh
    L_00444eff:
        push eax
    L_00444f00:
        call dword ptr [edx+0E4h]
    L_00444f06:
        mov edx,dword ptr [esp+8]
    L_00444f0a:
        mov eax,dword ptr [data_00491c30]
    L_00444f0f:
        mov ecx,dword ptr [eax]
    L_00444f11:
        push 14h
    L_00444f13:
        push edx
    L_00444f14:
        mov edx,dword ptr [esp+14h]
    L_00444f18:
        add edx,0FFFFFFFEh
    L_00444f1b:
        push edx
    L_00444f1c:
        push 5
    L_00444f1e:
        push eax
    L_00444f1f:
        call dword ptr [ecx+14Ch]
    L_00444f25:
        mov eax,dword ptr [data_00491c10]
    L_00444f2a:
        push 4
    L_00444f2c:
        mov cl,0FFh
    L_00444f2e:
        push 4
    L_00444f30:
        mov byte ptr [eax+3ADA6Ah],cl
    L_00444f36:
        mov byte ptr [eax+3ADA69h],cl
    L_00444f3c:
        mov byte ptr [eax+3ADA68h],3
    L_00444f43:
        mov byte ptr [eax+3ADA6Bh],cl
    L_00444f49:
        mov eax,dword ptr [data_00491c30]
    L_00444f4e:
        mov ecx,dword ptr [eax]
    L_00444f50:
        push 0
    L_00444f52:
        push eax
    L_00444f53:
        call dword ptr [ecx+10Ch]
    L_00444f59:
        mov eax,dword ptr [data_00491c30]
    L_00444f5e:
        mov edx,dword ptr [eax]
    L_00444f60:
        push 4
    L_00444f62:
        push 1
    L_00444f64:
        push 0
    L_00444f66:
        push eax
    L_00444f67:
        call dword ptr [edx+10Ch]
    L_00444f6d:
        mov eax,dword ptr [data_00491c30]
    L_00444f72:
        mov ecx,dword ptr [eax]
    L_00444f74:
        push 2
    L_00444f76:
        push 5
    L_00444f78:
        push 0
    L_00444f7a:
        push eax
    L_00444f7b:
        call dword ptr [ecx+10Ch]
    L_00444f81:
        mov eax,dword ptr [data_00491c30]
    L_00444f86:
        mov edx,dword ptr [eax]
    L_00444f88:
        push 2
    L_00444f8a:
        push 2
    L_00444f8c:
        push 0
    L_00444f8e:
        push eax
    L_00444f8f:
        call dword ptr [edx+10Ch]
    L_00444f95:
        xor eax,eax
    L_00444f97:
        pop esi
    L_00444f98:
        ret 8
    }
}
