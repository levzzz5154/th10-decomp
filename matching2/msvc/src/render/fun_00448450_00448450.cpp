#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421480..0x0042159E: Camera_ApplyRetail
// Naked body preserves the retail register/stack ABI.

// 0x00448450..0x004485CA: FUN_00448450
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00448450_00448450() {
    __asm {
    L_00448450:
        sub esp,20h
    L_00448453:
        push ebx
    L_00448454:
        push ebp
    L_00448455:
        mov ebp,dword ptr [esp+4Ch]
    L_00448459:
        push esi
    L_0044845a:
        push edi
    L_0044845b:
        mov edi,eax
    L_0044845d:
        mov esi,edi
    L_0044845f:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00448464:
        mov esi,dword ptr [esp+34h]
    L_00448468:
        mov eax,dword ptr [edi+esi*4+3AD4E0h]
    L_0044846f:
        test eax,eax
    L_00448471:
        lea ebx,[edi+esi*4+3AD4E0h]
    L_00448478:
        je short L_0044847f
    L_0044847a:
        call asm_AnimationManager_ClearIndexedResources_00447f70
    L_0044847f:
        mov ecx,dword ptr [esp+38h]
    L_00448483:
        mov edx,dword ptr [esp+40h]
    L_00448487:
        mov eax,dword ptr [esp+3Ch]
    L_0044848b:
        mov dword ptr [esp+10h],ecx
    L_0044848f:
        add ecx,edx
    L_00448491:
        mov edx,dword ptr [esp+50h]
    L_00448495:
        mov dword ptr [esp+18h],ecx
    L_00448499:
        mov ecx,dword ptr [esp+44h]
    L_0044849d:
        mov dword ptr [esp+14h],eax
    L_004484a1:
        add eax,ecx
    L_004484a3:
        mov ecx,dword ptr [esp+48h]
    L_004484a7:
        mov dword ptr [esp+20h],ecx
    L_004484ab:
        add ecx,edx
    L_004484ad:
        mov dword ptr [esp+1Ch],eax
    L_004484b1:
        mov eax,dword ptr [esp+4Ch]
    L_004484b5:
        lea edx,[esp+54h]
    L_004484b9:
        push edx
    L_004484ba:
        mov dword ptr [esp+28h],eax
    L_004484be:
        push 0
    L_004484c0:
        add eax,ebp
    L_004484c2:
        push 0
    L_004484c4:
        mov dword ptr [esp+38h],eax
    L_004484c8:
        mov eax,dword ptr [data_00491c30]
    L_004484cd:
        push 0
    L_004484cf:
        mov dword ptr [esp+38h],ecx
    L_004484d3:
        mov ecx,dword ptr [eax]
    L_004484d5:
        push eax
    L_004484d6:
        call dword ptr [ecx+48h]
    L_004484d9:
        test eax,eax
    L_004484db:
        jne asm_target_004485c1
    L_004484e1:
        mov eax,dword ptr [esp+50h]
    L_004484e5:
        imul esi,1Ch
    L_004484e8:
        push 0
    L_004484ea:
        push ebx
    L_004484eb:
        push 1
    L_004484ed:
        push 0
    L_004484ef:
        add esi,edi
    L_004484f1:
        mov dword ptr [esi+3AD6E0h],eax
    L_004484f7:
        mov dword ptr [esi+3AD6E4h],ebp
    L_004484fd:
        mov edx,dword ptr [data_00491d14]
    L_00448503:
        mov eax,dword ptr [data_00491c30]
    L_00448508:
        mov ecx,dword ptr [eax]
    L_0044850a:
        push 0
    L_0044850c:
        push edx
    L_0044850d:
        mov edx,dword ptr [esp+68h]
    L_00448511:
        push ebp
    L_00448512:
        push edx
    L_00448513:
        push eax
    L_00448514:
        call dword ptr [ecx+70h]
    L_00448517:
        test eax,eax
    L_00448519:
        je short L_00448547
    L_0044851b:
        mov edx,dword ptr [data_00491d14]
    L_00448521:
        mov eax,dword ptr [data_00491c30]
    L_00448526:
        mov ecx,dword ptr [eax]
    L_00448528:
        push 0
    L_0044852a:
        push ebx
    L_0044852b:
        push 3
    L_0044852d:
        push edx
    L_0044852e:
        mov edx,dword ptr [esi+3AD6E4h]
    L_00448534:
        push edx
    L_00448535:
        mov edx,dword ptr [esi+3AD6E0h]
    L_0044853b:
        push edx
    L_0044853c:
        push eax
    L_0044853d:
        call dword ptr [ecx+90h]
    L_00448543:
        test eax,eax
    L_00448545:
        jne short L_004485b3
    L_00448547:
        mov ecx,dword ptr [esp+34h]
    L_0044854b:
        mov eax,dword ptr [data_00491c30]
    L_00448550:
        mov edx,dword ptr [eax]
    L_00448552:
        push 0
    L_00448554:
        lea edi,[edi+ecx*4+3AD560h]
    L_0044855b:
        mov ecx,dword ptr [data_00491d14]
    L_00448561:
        push edi
    L_00448562:
        push 3
    L_00448564:
        push ecx
    L_00448565:
        mov ecx,dword ptr [esi+3AD6E4h]
    L_0044856b:
        push ecx
    L_0044856c:
        mov ecx,dword ptr [esi+3AD6E0h]
    L_00448572:
        push ecx
    L_00448573:
        push eax
    L_00448574:
        call dword ptr [edx+90h]
    L_0044857a:
        test eax,eax
    L_0044857c:
        jne short L_004485b3
    L_0044857e:
        push eax
    L_0044857f:
        push 0FFFFFFFFh
    L_00448581:
        lea edx,[esp+18h]
    L_00448585:
        push edx
    L_00448586:
        mov edx,dword ptr [ebx]
    L_00448588:
        push eax
    L_00448589:
        mov eax,dword ptr [esp+64h]
    L_0044858d:
        push eax
    L_0044858e:
        lea ecx,[esp+34h]
    L_00448592:
        push ecx
    L_00448593:
        push 0
    L_00448595:
        push edx
    L_00448596:
        call asm_D3DXLoadSurfaceFromSurface_004521d6
    L_0044859b:
        test eax,eax
    L_0044859d:
        jne short L_004485b3
    L_0044859f:
        mov ecx,dword ptr [edi]
    L_004485a1:
        push eax
    L_004485a2:
        push 0FFFFFFFFh
    L_004485a4:
        push eax
    L_004485a5:
        push eax
    L_004485a6:
        mov eax,dword ptr [ebx]
    L_004485a8:
        push eax
    L_004485a9:
        push 0
    L_004485ab:
        push 0
    L_004485ad:
        push ecx
    L_004485ae:
        call asm_D3DXLoadSurfaceFromSurface_004521d6
    L_004485b3:
        mov eax,dword ptr [esp+54h]
    L_004485b7:
        test eax,eax
    L_004485b9:
        je short L_004485c1
    L_004485bb:
        mov edx,dword ptr [eax]
    L_004485bd:
        push eax
    L_004485be:
        call dword ptr [edx+8]
    L_004485c1:
        pop edi
    L_004485c2:
        pop esi
    L_004485c3:
        pop ebp
    L_004485c4:
        pop ebx
    L_004485c5:
        add esp,20h
    L_004485c8:
        ret 24h
    }
}
