#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C3C0..0x0040C43D: StageBackground_RebindTextureRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_StageBackground_RebindTextureRetail_0040c3c0() {
    __asm {
    L_0040c3c0:
        mov eax,dword ptr [ebx+70h]
    L_0040c3c3:
        push esi
    L_0040c3c4:
        push edi
    L_0040c3c5:
        mov byte ptr [data_00497c38],0
    L_0040c3cc:
        mov esi,eax
    L_0040c3ce:
        mov edi,edi
    L_0040c3d0:
        mov cl,byte ptr [eax]
    L_0040c3d2:
        inc eax
    L_0040c3d3:
        test cl,cl
    L_0040c3d5:
        jne short L_0040c3d0
    L_0040c3d7:
        mov edi,497C38h
    L_0040c3dc:
        sub eax,esi
    L_0040c3de:
        dec edi
    L_0040c3df:
        nop
    L_0040c3e0:
        mov cl,byte ptr [edi+1]
    L_0040c3e3:
        inc edi
    L_0040c3e4:
        test cl,cl
    L_0040c3e6:
        jne short L_0040c3e0
    L_0040c3e8:
        mov edx,dword ptr [data_00491c10]
    L_0040c3ee:
        mov ecx,eax
    L_0040c3f0:
        shr ecx,2
    L_0040c3f3:
        rep movsd
    L_0040c3f5:
        mov ecx,eax
    L_0040c3f7:
        and ecx,3
    L_0040c3fa:
        rep movsb
    L_0040c3fc:
        mov eax,dword ptr [ebx+54h]
    L_0040c3ff:
        mov ecx,dword ptr [eax+4]
    L_0040c402:
        push 497C38h
    L_0040c407:
        add ecx,1Dh
    L_0040c40a:
        call asm_Recovery_LoadCachedResource_00447280
    L_0040c40f:
        mov ecx,dword ptr [ebx+54h]
    L_0040c412:
        mov edx,dword ptr [ecx+4]
    L_0040c415:
        mov esi,dword ptr [data_004776e0]
    L_0040c41b:
        mov dword ptr [ebx+edx*4+80h],eax
    L_0040c422:
        and dword ptr [ebx+74h],0FFFFFFFBh
    L_0040c426:
        add esi,89A4h
    L_0040c42c:
        mov eax,esi
    L_0040c42e:
        call asm_FUN_00409e50_00409e50
    L_0040c433:
        pop edi
    L_0040c434:
        mov dword ptr [esi],0
    L_0040c43a:
        xor eax,eax
    L_0040c43c:
        pop esi
    L_0040c43d:
        ret
    }
}

