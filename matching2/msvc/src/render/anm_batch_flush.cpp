#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00442F50..0x00442FD4: AnimationManager_FlushQuadBatch
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_FlushQuadBatch_00442f50() {
    __asm {
    L_00442f50:
        mov eax,dword ptr [esi+3ADAC8h]
    L_00442f56:
        test eax,eax
    L_00442f58:
        je short L_00442fd4
    L_00442f5a:
        mov eax,dword ptr [data_00491c30]
    L_00442f5f:
        mov ecx,dword ptr [eax]
    L_00442f61:
        push 0
    L_00442f63:
        push 6
    L_00442f65:
        push 0
    L_00442f67:
        push eax
    L_00442f68:
        call dword ptr [ecx+10Ch]
    L_00442f6e:
        mov eax,dword ptr [data_00491c30]
    L_00442f73:
        mov edx,dword ptr [eax]
    L_00442f75:
        push 0
    L_00442f77:
        push 3
    L_00442f79:
        push 0
    L_00442f7b:
        push eax
    L_00442f7c:
        call dword ptr [edx+10Ch]
    L_00442f82:
        mov eax,dword ptr [data_00491c30]
    L_00442f87:
        mov ecx,dword ptr [eax]
    L_00442f89:
        push 144h
    L_00442f8e:
        push eax
    L_00442f8f:
        call dword ptr [ecx+164h]
    L_00442f95:
        mov ecx,dword ptr [esi+72DAD0h]
    L_00442f9b:
        mov eax,dword ptr [data_00491c30]
    L_00442fa0:
        mov edx,dword ptr [eax]
    L_00442fa2:
        push 1Ch
    L_00442fa4:
        push ecx
    L_00442fa5:
        mov ecx,dword ptr [esi+3ADAC8h]
    L_00442fab:
        shl ecx,1
    L_00442fad:
        push ecx
    L_00442fae:
        push 4
    L_00442fb0:
        push eax
    L_00442fb1:
        call dword ptr [edx+14Ch]
    L_00442fb7:
        mov eax,dword ptr [esi+58h]
    L_00442fba:
        mov edx,dword ptr [esi+72DACCh]
    L_00442fc0:
        inc eax
    L_00442fc1:
        mov dword ptr [esi+72DAD0h],edx
    L_00442fc7:
        mov dword ptr [esi+3ADAC8h],0
    L_00442fd1:
        mov dword ptr [esi+58h],eax
    L_00442fd4:
        ret
    }
}
