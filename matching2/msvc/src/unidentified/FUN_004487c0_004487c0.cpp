#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004487C0..0x00448807: FUN_004487c0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004487c0_004487c0() {
    __asm {
    L_004487c0:
        push esi
    L_004487c1:
        push edi
    L_004487c2:
        mov edi,491E94h
    L_004487c7:
        mov esi,ecx
    L_004487c9:
        mov dword ptr [data_00491fac],edi
    L_004487cf:
        call asm_Camera_ApplyRetail_00421480
    L_004487d4:
        mov edx,dword ptr [data_00491fac]
    L_004487da:
        mov eax,dword ptr [data_00491c30]
    L_004487df:
        mov ecx,dword ptr [eax]
    L_004487e1:
        add edx,0CCh
    L_004487e7:
        push edx
    L_004487e8:
        push eax
    L_004487e9:
        call dword ptr [ecx+0BCh]
    L_004487ef:
        mov eax,10h
    L_004487f4:
        mov edi,esi
    L_004487f6:
        mov dword ptr [data_00491fb0],1
    L_00448800:
        call asm_AnimationManager_RenderBucket_00448980
    L_00448805:
        pop edi
    L_00448806:
        pop esi
    L_00448807:
        ret
    }
}
