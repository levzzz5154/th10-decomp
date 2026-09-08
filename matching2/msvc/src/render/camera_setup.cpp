#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421480..0x0042159E: Camera_ApplyRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Camera_ApplyRetail_00421480() {
    __asm {
    L_00421480:
        sub esp,2Ch
    L_00421483:
        push ebx
    L_00421484:
        push esi
    L_00421485:
        mov esi,dword ptr [data_00491c10]
    L_0042148b:
        test esi,esi
    L_0042148d:
        je short L_00421494
    L_0042148f:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00421494:
        mov eax,dword ptr [edi+0D4h]
    L_0042149a:
        fild dword ptr [edi+0D4h]
    L_004214a0:
        test eax,eax
    L_004214a2:
        jge short L_004214aa
    L_004214a4:
        fadd dword ptr [data_00470b98]
    L_004214aa:
        mov ecx,dword ptr [edi+0D8h]
    L_004214b0:
        fst dword ptr [esp+8]
    L_004214b4:
        test ecx,ecx
    L_004214b6:
        fmul dword ptr [data_00470b0c]
    L_004214bc:
        fild dword ptr [edi+0D8h]
    L_004214c2:
        jge short L_004214ca
    L_004214c4:
        fadd dword ptr [data_00470b98]
    L_004214ca:
        fst dword ptr [esp+0Ch]
    L_004214ce:
        lea edx,[esp+10h]
    L_004214d2:
        fmul dword ptr [data_00470b0c]
    L_004214d8:
        push edx
    L_004214d9:
        fld dword ptr [esp+0Ch]
    L_004214dd:
        lea eax,[esp+20h]
    L_004214e1:
        fdiv dword ptr [esp+10h]
    L_004214e5:
        push eax
    L_004214e6:
        lea ecx,[esp+30h]
    L_004214ea:
        push ecx
    L_004214eb:
        lea esi,[edi+4Ch]
    L_004214ee:
        push esi
    L_004214ef:
        mov dword ptr [esp+34h],0
    L_004214f7:
        mov dword ptr [esp+20h],0
    L_004214ff:
        mov dword ptr [esp+24h],0BF800000h
    L_00421507:
        mov dword ptr [esp+28h],0
    L_0042150f:
        fstp dword ptr [esp+1Ch]
    L_00421513:
        fld st(1)
    L_00421515:
        fstp dword ptr [esp+38h]
    L_00421519:
        fst dword ptr [esp+3Ch]
    L_0042151d:
        fld qword ptr [data_00470ba0]
    L_00421523:
        fptan
    L_00421525:
        fstp st(0)
    L_00421527:
        fdivr st,st(1)
    L_00421529:
        fstp dword ptr [esp+40h]
    L_0042152d:
        fxch
    L_0042152f:
        fstp dword ptr [esp+2Ch]
    L_00421533:
        fstp dword ptr [esp+30h]
    L_00421537:
        call asm_D3DXMatrixLookAtLH_00452194
    L_0042153c:
        mov edx,dword ptr [esp+0Ch]
    L_00421540:
        push 461C4000h
    L_00421545:
        push 3F800000h
    L_0042154a:
        push edx
    L_0042154b:
        push 3EA0D97Ch
    L_00421550:
        lea ebx,[edi+8Ch]
    L_00421556:
        push ebx
    L_00421557:
        call asm_D3DXMatrixPerspectiveFovLH_0045219a
    L_0042155c:
        mov eax,dword ptr [data_00491c30]
    L_00421561:
        mov ecx,dword ptr [eax]
    L_00421563:
        push esi
    L_00421564:
        push 2
    L_00421566:
        push eax
    L_00421567:
        call dword ptr [ecx+0B0h]
    L_0042156d:
        mov eax,dword ptr [data_00491c30]
    L_00421572:
        mov edx,dword ptr [eax]
    L_00421574:
        push ebx
    L_00421575:
        push 3
    L_00421577:
        push eax
    L_00421578:
        call dword ptr [edx+0B0h]
    L_0042157e:
        mov eax,dword ptr [data_00491c10]
    L_00421583:
        test eax,eax
    L_00421585:
        pop esi
    L_00421586:
        pop ebx
    L_00421587:
        je short L_0042159b
    L_00421589:
        mov ecx,dword ptr [edi+0E8h]
    L_0042158f:
        mov dword ptr [eax+5Ch],ecx
    L_00421592:
        mov edx,dword ptr [edi+0ECh]
    L_00421598:
        mov dword ptr [eax+60h],edx
    L_0042159b:
        add esp,2Ch
    L_0042159e:
        ret
    }
}

// 0x0043BCD0..0x0043BD3B: Viewport_ApplyDefaultRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Viewport_ApplyDefaultRetail_0043bcd0() {
    __asm {
    L_0043bcd0:
        push esi
    L_0043bcd1:
        mov esi,dword ptr [data_00491c10]
    L_0043bcd7:
        test esi,esi
    L_0043bcd9:
        je short L_0043bce0
    L_0043bcdb:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_0043bce0:
        mov eax,dword ptr [data_00491c30]
    L_0043bce5:
        push 491CF4h
    L_0043bcea:
        mov dword ptr [data_00491cf4],0
    L_0043bcf4:
        mov dword ptr [data_00491cf8],0
    L_0043bcfe:
        mov dword ptr [data_00491cfc],280h
    L_0043bd08:
        mov dword ptr [data_00491d00],1E0h
    L_0043bd12:
        mov dword ptr [data_00491d04],0
    L_0043bd1c:
        mov dword ptr [data_00491d08],3F800000h
    L_0043bd26:
        mov ecx,dword ptr [eax]
    L_0043bd28:
        push eax
    L_0043bd29:
        call dword ptr [ecx+0BCh]
    L_0043bd2f:
        mov esi,dword ptr [esp+8]
    L_0043bd33:
        call asm_Recovery_ResetDeviceStreams_0043bc40
    L_0043bd38:
        pop esi
    L_0043bd39:
        ret 4
    }
}

// 0x00448270..0x0044835F: FUN_00448270
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00448270_00448270() {
    __asm {
    L_00448270:
        sub esp,24h
    L_00448273:
        push ebp
    L_00448274:
        mov ebp,dword ptr [esp+40h]
    L_00448278:
        shl eax,4
    L_0044827b:
        push esi
    L_0044827c:
        mov esi,ecx
    L_0044827e:
        push edi
    L_0044827f:
        mov edi,eax
    L_00448281:
        mov eax,dword ptr [esi+ebx*4+3AD06Ch]
    L_00448288:
        mov ecx,dword ptr [eax+120h]
    L_0044828e:
        cmp dword ptr [edi+ecx],0
    L_00448292:
        je asm_target_00448357
    L_00448298:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_0044829d:
        mov eax,dword ptr [data_00491c30]
    L_004482a2:
        mov edx,dword ptr [eax]
    L_004482a4:
        lea ecx,[esp+48h]
    L_004482a8:
        push ecx
    L_004482a9:
        push 0
    L_004482ab:
        push 0
    L_004482ad:
        push 0
    L_004482af:
        push eax
    L_004482b0:
        call dword ptr [edx+48h]
    L_004482b3:
        test eax,eax
    L_004482b5:
        jne asm_target_00448357
    L_004482bb:
        mov edx,dword ptr [esi+ebx*4+3AD06Ch]
    L_004482c2:
        mov eax,dword ptr [edx+120h]
    L_004482c8:
        mov edi,dword ptr [edi+eax]
    L_004482cb:
        mov ecx,dword ptr [edi]
    L_004482cd:
        lea edx,[esp+0Ch]
    L_004482d1:
        push edx
    L_004482d2:
        push 0
    L_004482d4:
        push edi
    L_004482d5:
        call dword ptr [ecx+48h]
    L_004482d8:
        test eax,eax
    L_004482da:
        jne short L_0044834d
    L_004482dc:
        mov ecx,dword ptr [esp+34h]
    L_004482e0:
        mov edx,dword ptr [esp+3Ch]
    L_004482e4:
        mov eax,dword ptr [esp+38h]
    L_004482e8:
        mov dword ptr [esp+10h],ecx
    L_004482ec:
        add ecx,edx
    L_004482ee:
        mov edx,dword ptr [esp+4Ch]
    L_004482f2:
        mov dword ptr [esp+14h],eax
    L_004482f6:
        mov dword ptr [esp+18h],ecx
    L_004482fa:
        mov ecx,dword ptr [esp+40h]
    L_004482fe:
        add eax,ecx
    L_00448300:
        push 0
    L_00448302:
        mov dword ptr [esp+20h],eax
    L_00448306:
        mov eax,dword ptr [esp+48h]
    L_0044830a:
        push 2
    L_0044830c:
        mov dword ptr [esp+28h],eax
    L_00448310:
        add eax,edx
    L_00448312:
        mov edx,dword ptr [esp+50h]
    L_00448316:
        lea ecx,[esp+18h]
    L_0044831a:
        push ecx
    L_0044831b:
        mov ecx,dword ptr [esp+18h]
    L_0044831f:
        mov dword ptr [esp+34h],eax
    L_00448323:
        mov eax,dword ptr [esp+5Ch]
    L_00448327:
        push 0
    L_00448329:
        mov dword ptr [esp+34h],ebp
    L_0044832d:
        add ebp,eax
    L_0044832f:
        push edx
    L_00448330:
        lea eax,[esp+34h]
    L_00448334:
        push eax
    L_00448335:
        push 0
    L_00448337:
        push ecx
    L_00448338:
        mov dword ptr [esp+4Ch],ebp
    L_0044833c:
        call asm_D3DXLoadSurfaceFromSurface_004521d6
    L_00448341:
        test eax,eax
    L_00448343:
        mov eax,dword ptr [esp+0Ch]
    L_00448347:
        mov edx,dword ptr [eax]
    L_00448349:
        push eax
    L_0044834a:
        call dword ptr [edx+8]
    L_0044834d:
        mov eax,dword ptr [esp+48h]
    L_00448351:
        mov ecx,dword ptr [eax]
    L_00448353:
        push eax
    L_00448354:
        call dword ptr [ecx+8]
    L_00448357:
        pop edi
    L_00448358:
        pop esi
    L_00448359:
        pop ebp
    L_0044835a:
        add esp,24h
    L_0044835d:
        ret 20h
    }
}

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
