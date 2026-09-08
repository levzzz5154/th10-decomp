#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00448360..0x00448442: FUN_00448360
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00448360_00448360() {
    __asm {
    L_00448360:
        push ecx
    L_00448361:
        push ebp
    L_00448362:
        mov ebp,dword ptr [esp+0Ch]
    L_00448366:
        shl eax,4
    L_00448369:
        push esi
    L_0044836a:
        mov esi,edx
    L_0044836c:
        push edi
    L_0044836d:
        mov edi,eax
    L_0044836f:
        mov eax,dword ptr [esi+ebp*4+3AD06Ch]
    L_00448376:
        mov edx,dword ptr [eax+120h]
    L_0044837c:
        cmp dword ptr [edi+edx],0
    L_00448380:
        je asm_target_0044843c
    L_00448386:
        mov eax,dword ptr [esp+18h]
    L_0044838a:
        shl ecx,4
    L_0044838d:
        push ebx
    L_0044838e:
        mov ebx,ecx
    L_00448390:
        mov ecx,dword ptr [esi+eax*4+3AD06Ch]
    L_00448397:
        mov edx,dword ptr [ecx+120h]
    L_0044839d:
        cmp dword ptr [ebx+edx],0
    L_004483a1:
        je asm_target_0044843b
    L_004483a7:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_004483ac:
        mov eax,dword ptr [esi+ebp*4+3AD06Ch]
    L_004483b3:
        mov ecx,dword ptr [eax+120h]
    L_004483b9:
        mov edi,dword ptr [edi+ecx]
    L_004483bc:
        mov edx,dword ptr [edi]
    L_004483be:
        lea eax,[esp+18h]
    L_004483c2:
        push eax
    L_004483c3:
        push 0
    L_004483c5:
        push edi
    L_004483c6:
        call dword ptr [edx+48h]
    L_004483c9:
        test eax,eax
    L_004483cb:
        jne short L_0044843b
    L_004483cd:
        mov ecx,dword ptr [esp+1Ch]
    L_004483d1:
        mov edx,dword ptr [esi+ecx*4+3AD06Ch]
    L_004483d8:
        mov eax,dword ptr [edx+120h]
    L_004483de:
        mov eax,dword ptr [ebx+eax]
    L_004483e1:
        mov ecx,dword ptr [eax]
    L_004483e3:
        lea edx,[esp+10h]
    L_004483e7:
        push edx
    L_004483e8:
        push 0
    L_004483ea:
        push eax
    L_004483eb:
        call dword ptr [ecx+48h]
    L_004483ee:
        test eax,eax
    L_004483f0:
        je short L_00448404
    L_004483f2:
        mov eax,dword ptr [esp+18h]
    L_004483f6:
        mov ecx,dword ptr [eax]
    L_004483f8:
        push eax
    L_004483f9:
        call dword ptr [ecx+8]
    L_004483fc:
        pop ebx
    L_004483fd:
        pop edi
    L_004483fe:
        pop esi
    L_004483ff:
        pop ebp
    L_00448400:
        pop ecx
    L_00448401:
        ret 10h
    L_00448404:
        mov edx,dword ptr [esp+24h]
    L_00448408:
        mov eax,dword ptr [esp+10h]
    L_0044840c:
        mov ecx,dword ptr [esp+20h]
    L_00448410:
        push 0
    L_00448412:
        push 0FFFFFFFFh
    L_00448414:
        push edx
    L_00448415:
        mov edx,dword ptr [esp+24h]
    L_00448419:
        push 0
    L_0044841b:
        push eax
    L_0044841c:
        push ecx
    L_0044841d:
        push 0
    L_0044841f:
        push edx
    L_00448420:
        call asm_D3DXLoadSurfaceFromSurface_004521d6
    L_00448425:
        test eax,eax
    L_00448427:
        mov eax,dword ptr [esp+18h]
    L_0044842b:
        mov ecx,dword ptr [eax]
    L_0044842d:
        push eax
    L_0044842e:
        call dword ptr [ecx+8]
    L_00448431:
        mov eax,dword ptr [esp+10h]
    L_00448435:
        mov edx,dword ptr [eax]
    L_00448437:
        push eax
    L_00448438:
        call dword ptr [edx+8]
    L_0044843b:
        pop ebx
    L_0044843c:
        pop edi
    L_0044843d:
        pop esi
    L_0044843e:
        pop ebp
    L_0044843f:
        pop ecx
    L_00448440:
        ret 10h
    }
}
