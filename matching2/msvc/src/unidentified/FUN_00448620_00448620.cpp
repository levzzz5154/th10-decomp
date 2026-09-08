#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00448620..0x00448692: FUN_00448620
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00448620_00448620() {
    __asm {
    L_00448620:
        push ebx
    L_00448621:
        push edi
    L_00448622:
        mov edi,491D7Ch
    L_00448627:
        mov ebx,ecx
    L_00448629:
        mov dword ptr [data_00491fac],edi
    L_0044862f:
        call asm_Camera_ApplyRetail_00421480
    L_00448634:
        mov edx,dword ptr [data_00491fac]
    L_0044863a:
        mov eax,dword ptr [data_00491c30]
    L_0044863f:
        mov ecx,dword ptr [eax]
    L_00448641:
        add edx,0CCh
    L_00448647:
        push edx
    L_00448648:
        push eax
    L_00448649:
        call dword ptr [ecx+0BCh]
    L_0044864f:
        mov eax,dword ptr [data_00492378]
    L_00448654:
        xor edi,edi
    L_00448656:
        cmp eax,edi
    L_00448658:
        mov dword ptr [data_00491fb0],edi
    L_0044865e:
        je short L_00448684
    L_00448660:
        push esi
    L_00448661:
        mov esi,dword ptr [data_00491c10]
    L_00448667:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_0044866c:
        mov eax,dword ptr [data_00491c30]
    L_00448671:
        push edi
    L_00448672:
        push 1Ch
    L_00448674:
        mov dword ptr [data_00492378],edi
    L_0044867a:
        mov ecx,dword ptr [eax]
    L_0044867c:
        push eax
    L_0044867d:
        call dword ptr [ecx+0E4h]
    L_00448683:
        pop esi
    L_00448684:
        mov eax,3
    L_00448689:
        mov edi,ebx
    L_0044868b:
        call asm_AnimationManager_RenderBucket_00448980
    L_00448690:
        pop edi
    L_00448691:
        pop ebx
    L_00448692:
        ret
    }
}
