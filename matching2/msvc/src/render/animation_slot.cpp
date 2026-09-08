#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004136C0..0x00413720: AnimationSlot_ReleaseRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationSlot_ReleaseRetail_004136c0() {
    __asm {
    L_004136c0:
        mov eax,dword ptr [esi+40h]
    L_004136c3:
        push ebx
    L_004136c4:
        push edi
    L_004136c5:
        mov edi,dword ptr [data_00491c10]
    L_004136cb:
        push eax
    L_004136cc:
        mov edx,edi
    L_004136ce:
        call asm_AnimationManager_SetFlag_004492a0
    L_004136d3:
        xor ebx,ebx
    L_004136d5:
        mov dword ptr [esi+40h],ebx
    L_004136d8:
        mov ecx,dword ptr [esi+44h]
    L_004136db:
        push ecx
    L_004136dc:
        mov edx,edi
    L_004136de:
        call asm_AnimationManager_SetFlag_004492a0
    L_004136e3:
        mov dword ptr [esi+44h],ebx
    L_004136e6:
        mov edx,dword ptr [esi+48h]
    L_004136e9:
        push edx
    L_004136ea:
        mov edx,edi
    L_004136ec:
        call asm_AnimationManager_SetFlag_004492a0
    L_004136f1:
        mov dword ptr [esi+48h],ebx
    L_004136f4:
        mov eax,dword ptr [esi+4Ch]
    L_004136f7:
        push eax
    L_004136f8:
        mov edx,edi
    L_004136fa:
        call asm_AnimationManager_SetFlag_004492a0
    L_004136ff:
        mov dword ptr [esi+4Ch],ebx
    L_00413702:
        mov ecx,dword ptr [esi+50h]
    L_00413705:
        push ecx
    L_00413706:
        mov edx,edi
    L_00413708:
        call asm_AnimationManager_SetFlag_004492a0
    L_0041370d:
        mov dword ptr [esi+50h],ebx
    L_00413710:
        mov edx,dword ptr [esi+54h]
    L_00413713:
        push edx
    L_00413714:
        mov edx,edi
    L_00413716:
        call asm_AnimationManager_SetFlag_004492a0
    L_0041371b:
        pop edi
    L_0041371c:
        mov dword ptr [esi+54h],ebx
    L_0041371f:
        pop ebx
    L_00413720:
        ret
    }
}
