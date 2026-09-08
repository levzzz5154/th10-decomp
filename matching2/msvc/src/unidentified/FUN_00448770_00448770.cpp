#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00448770..0x004487B7: FUN_00448770
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00448770_00448770() {
    __asm {
    L_00448770:
        push esi
    L_00448771:
        push edi
    L_00448772:
        mov edi,491E94h
    L_00448777:
        mov esi,ecx
    L_00448779:
        mov dword ptr [data_00491fac],edi
    L_0044877f:
        call asm_Camera_ApplyRetail_00421480
    L_00448784:
        mov edx,dword ptr [data_00491fac]
    L_0044878a:
        mov eax,dword ptr [data_00491c30]
    L_0044878f:
        mov ecx,dword ptr [eax]
    L_00448791:
        add edx,0CCh
    L_00448797:
        push edx
    L_00448798:
        push eax
    L_00448799:
        call dword ptr [ecx+0BCh]
    L_0044879f:
        mov eax,0Fh
    L_004487a4:
        mov edi,esi
    L_004487a6:
        mov dword ptr [data_00491fb0],1
    L_004487b0:
        call asm_AnimationManager_RenderBucket_00448980
    L_004487b5:
        pop edi
    L_004487b6:
        pop esi
    L_004487b7:
        ret
    }
}
