#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00418190..0x00418797: FUN_00418190
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00418190_00418190() {
    __asm {
    L_00418190:
        sub esp,40h
    L_00418193:
        push ebx
    L_00418194:
        push ebp
    L_00418195:
        push esi
    L_00418196:
        push edi
    L_00418197:
        mov edi,dword ptr [esp+54h]
    L_0041819b:
        mov eax,dword ptr [edi+14h]
    L_0041819e:
        xor ebp,ebp
    L_004181a0:
        cmp eax,ebp
    L_004181a2:
        jne asm_target_0041840b
    L_004181a8:
        test byte ptr [edi+58h],8
    L_004181ac:
        je short L_004181dc
    L_004181ae:
        mov esi,492254h
    L_004181b3:
        call asm_Platform_StopWorker_0044c150
    L_004181b8:
        mov eax,dword ptr [data_00491ff4]
    L_004181bd:
        shr eax,0Ch
    L_004181c0:
        not eax
    L_004181c2:
        pop edi
    L_004181c3:
        and eax,1
    L_004181c6:
        pop esi
    L_004181c7:
        or eax,2
    L_004181ca:
        pop ebp
    L_004181cb:
        mov dword ptr [data_00491fb8],eax
    L_004181d0:
        mov eax,1
    L_004181d5:
        pop ebx
    L_004181d6:
        add esp,40h
    L_004181d9:
        ret 4
    L_004181dc:
        mov ecx,dword ptr [data_004776e8]
    L_004181e2:
        push ecx
    L_004181e3:
        call asm_FUN_00404450_00404450
    L_004181e8:
        mov esi,dword ptr [data_004776e4]
    L_004181ee:
        cmp esi,ebp
    L_004181f0:
        je short L_0041821c
    L_004181f2:
        call asm_FUN_00404530_00404530
    L_004181f7:
        mov eax,dword ptr [data_004776e8]
    L_004181fc:
        call asm_PlayerManager_StartMode_004045b0
    L_00418201:
        or dword ptr [edi+58h],800h
    L_00418208:
        mov eax,dword ptr [data_0047770c]
    L_0041820d:
        add eax,9E14h
    L_00418212:
        call asm_FUN_00409e50_00409e50
    L_00418217:
        jmp asm_target_00418622
    L_0041821c:
        mov ebx,dword ptr [edi+58h]
    L_0041821f:
        mov esi,dword ptr [data_004776f0]
    L_00418225:
        and ebx,0FFFFF7FFh
    L_0041822b:
        mov dword ptr [edi+58h],ebx
    L_0041822e:
        call asm_BulletPool_ResetRetail_00405ed0
    L_00418233:
        mov esi,dword ptr [data_00477834]
    L_00418239:
        call asm_FUN_00424d90_00424d90
    L_0041823e:
        mov edi,dword ptr [data_00477818]
    L_00418244:
        mov edx,dword ptr [data_00477704]
    L_0041824a:
        xor eax,eax
    L_0041824c:
        mov ecx,873A8h
    L_00418251:
        add edi,14h
    L_00418254:
        push edx
    L_00418255:
        rep stosd
    L_00418257:
        call asm_FUN_00409f90_00409f90
    L_0041825c:
        mov eax,dword ptr [data_0047781c]
    L_00418261:
        call asm_RecoveryLinkedCleanup_00417770
    L_00418266:
        mov ebx,dword ptr [data_00477838]
    L_0041826c:
        mov dword ptr [data_00474c88],ebp
    L_00418272:
        mov dword ptr [data_00474c8c],ebp
    L_00418278:
        call asm_FUN_0042a450_0042a450
    L_0041827d:
        xor eax,eax
    L_0041827f:
        mov ecx,10h
    L_00418284:
        lea edi,[esp+10h]
    L_00418288:
        rep stosd
    L_0041828a:
        mov eax,dword ptr [data_00477704]
    L_0041828f:
        push 46D278h
    L_00418294:
        push eax
    L_00418295:
        lea eax,[esp+18h]
    L_00418299:
        call asm_FUN_0040cfb0_0040cfb0
    L_0041829e:
        mov edi,dword ptr [data_0047770c]
    L_004182a4:
        call asm_FUN_00413bc0_00413bc0
    L_004182a9:
        mov eax,dword ptr [data_00477830]
    L_004182ae:
        mov ecx,dword ptr [eax+8]
    L_004182b1:
        cmp ecx,ebp
    L_004182b3:
        mov esi,2
    L_004182b8:
        je short L_004182bd
    L_004182ba:
        or dword ptr [ecx+4],esi
    L_004182bd:
        mov ecx,dword ptr [eax+0Ch]
    L_004182c0:
        cmp ecx,ebp
    L_004182c2:
        je short L_004182c9
    L_004182c4:
        mov eax,ecx
    L_004182c6:
        or dword ptr [eax+4],esi
    L_004182c9:
        mov eax,dword ptr [data_00477834]
    L_004182ce:
        mov ecx,dword ptr [eax+8]
    L_004182d1:
        or dword ptr [ecx+4],esi
    L_004182d4:
        mov ecx,dword ptr [eax+0Ch]
    L_004182d7:
        mov edi,dword ptr [ecx+4]
    L_004182da:
        or edi,esi
    L_004182dc:
        push eax
    L_004182dd:
        mov dword ptr [ecx+4],edi
    L_004182e0:
        call asm_FUN_00426f70_00426f70
    L_004182e5:
        mov eax,dword ptr [data_004776f0]
    L_004182ea:
        mov ecx,dword ptr [eax+8]
    L_004182ed:
        cmp ecx,ebp
    L_004182ef:
        je short L_004182f4
    L_004182f1:
        or dword ptr [ecx+4],esi
    L_004182f4:
        mov ecx,dword ptr [eax+0Ch]
    L_004182f7:
        cmp ecx,ebp
    L_004182f9:
        je short L_00418300
    L_004182fb:
        mov eax,ecx
    L_004182fd:
        or dword ptr [eax+4],esi
    L_00418300:
        mov eax,dword ptr [data_00477704]
    L_00418305:
        mov ecx,dword ptr [eax+8]
    L_00418308:
        cmp ecx,ebp
    L_0041830a:
        je short L_0041830f
    L_0041830c:
        or dword ptr [ecx+4],esi
    L_0041830f:
        mov ecx,dword ptr [eax+0Ch]
    L_00418312:
        cmp ecx,ebp
    L_00418314:
        je short L_0041831b
    L_00418316:
        mov eax,ecx
    L_00418318:
        or dword ptr [eax+4],esi
    L_0041831b:
        mov eax,dword ptr [data_00477818]
    L_00418320:
        mov ecx,dword ptr [eax+8]
    L_00418323:
        cmp ecx,ebp
    L_00418325:
        je short L_0041832a
    L_00418327:
        or dword ptr [ecx+4],esi
    L_0041832a:
        mov ecx,dword ptr [eax+0Ch]
    L_0041832d:
        cmp ecx,ebp
    L_0041832f:
        je short L_00418336
    L_00418331:
        mov eax,ecx
    L_00418333:
        or dword ptr [eax+4],esi
    L_00418336:
        mov eax,dword ptr [data_0047781c]
    L_0041833b:
        mov ecx,dword ptr [eax+8]
    L_0041833e:
        cmp ecx,ebp
    L_00418340:
        je short L_00418345
    L_00418342:
        or dword ptr [ecx+4],esi
    L_00418345:
        mov ecx,dword ptr [eax+0Ch]
    L_00418348:
        cmp ecx,ebp
    L_0041834a:
        je short L_00418351
    L_0041834c:
        mov eax,ecx
    L_0041834e:
        or dword ptr [eax+4],esi
    L_00418351:
        mov ecx,dword ptr [data_004776fc]
    L_00418357:
        mov eax,dword ptr [ecx+8]
    L_0041835a:
        or dword ptr [eax+4],esi
    L_0041835d:
        mov eax,dword ptr [ecx+0Ch]
    L_00418360:
        or dword ptr [eax+4],esi
    L_00418363:
        mov eax,dword ptr [data_004776ec]
    L_00418368:
        mov ecx,dword ptr [eax+8]
    L_0041836b:
        cmp ecx,ebp
    L_0041836d:
        je short L_00418372
    L_0041836f:
        or dword ptr [ecx+4],esi
    L_00418372:
        mov ecx,dword ptr [eax+0Ch]
    L_00418375:
        cmp ecx,ebp
    L_00418377:
        je short L_0041837e
    L_00418379:
        mov eax,ecx
    L_0041837b:
        or dword ptr [eax+4],esi
    L_0041837e:
        mov ecx,dword ptr [data_00477840]
    L_00418384:
        mov eax,dword ptr [ecx+8]
    L_00418387:
        or dword ptr [eax+4],esi
    L_0041838a:
        mov eax,dword ptr [ecx+0Ch]
    L_0041838d:
        or dword ptr [eax+4],esi
    L_00418390:
        mov eax,dword ptr [data_004776f4]
    L_00418395:
        mov ecx,dword ptr [eax+8]
    L_00418398:
        cmp ecx,ebp
    L_0041839a:
        je short L_0041839f
    L_0041839c:
        or dword ptr [ecx+4],esi
    L_0041839f:
        mov ecx,dword ptr [eax+0Ch]
    L_004183a2:
        cmp ecx,ebp
    L_004183a4:
        je short L_004183a9
    L_004183a6:
        or dword ptr [ecx+4],esi
    L_004183a9:
        mov eax,dword ptr [eax+37ACh]
    L_004183af:
        or dword ptr [eax+4],esi
    L_004183b2:
        mov eax,dword ptr [data_00477814]
    L_004183b7:
        mov ecx,dword ptr [eax+8]
    L_004183ba:
        cmp ecx,ebp
    L_004183bc:
        je short L_004183c1
    L_004183be:
        or dword ptr [ecx+4],esi
    L_004183c1:
        mov ecx,dword ptr [eax+0Ch]
    L_004183c4:
        cmp ecx,ebp
    L_004183c6:
        je short L_004183cd
    L_004183c8:
        mov eax,ecx
    L_004183ca:
        or dword ptr [eax+4],esi
    L_004183cd:
        test byte ptr [data_00474ca0],20h
    L_004183d4:
        jne short L_004183e6
    L_004183d6:
        mov ecx,dword ptr [data_00477848]
    L_004183dc:
        mov edx,dword ptr [ecx+24h]
    L_004183df:
        push edx
    L_004183e0:
        push ebp
    L_004183e1:
        call asm_Sound_PlayDummyRetail_00420b10
    L_004183e6:
        mov esi,dword ptr [data_004776e0]
    L_004183ec:
        lea eax,[esi+89A0h]
    L_004183f2:
        call asm_FUN_00409e50_00409e50
    L_004183f7:
        add esi,89A4h
    L_004183fd:
        mov eax,esi
    L_004183ff:
        call asm_FUN_00409e50_00409e50
    L_00418404:
        mov dword ptr [esi],ebp
    L_00418406:
        jmp asm_target_0041861e
    L_0041840b:
        cmp eax,1Eh
    L_0041840e:
        jne asm_target_00418622
    L_00418414:
        mov eax,dword ptr [edi+58h]
    L_00418417:
        test ah,8
    L_0041841a:
        je asm_target_00418622
    L_00418420:
        mov esi,dword ptr [data_004776f0]
    L_00418426:
        and eax,0FFFFF7FFh
    L_0041842b:
        mov dword ptr [edi+58h],eax
    L_0041842e:
        call asm_BulletPool_ResetRetail_00405ed0
    L_00418433:
        mov esi,dword ptr [data_00477834]
    L_00418439:
        call asm_FUN_00424d90_00424d90
    L_0041843e:
        mov edi,dword ptr [data_00477818]
    L_00418444:
        xor eax,eax
    L_00418446:
        mov ecx,873A8h
    L_0041844b:
        add edi,14h
    L_0041844e:
        rep stosd
    L_00418450:
        mov eax,dword ptr [data_00477704]
    L_00418455:
        push eax
    L_00418456:
        call asm_FUN_00409f90_00409f90
    L_0041845b:
        mov eax,dword ptr [data_0047781c]
    L_00418460:
        call asm_RecoveryLinkedCleanup_00417770
    L_00418465:
        mov ebx,dword ptr [data_00477838]
    L_0041846b:
        mov dword ptr [data_00474c88],ebp
    L_00418471:
        mov dword ptr [data_00474c8c],ebp
    L_00418477:
        call asm_FUN_0042a450_0042a450
    L_0041847c:
        xor eax,eax
    L_0041847e:
        mov ecx,10h
    L_00418483:
        lea edi,[esp+10h]
    L_00418487:
        rep stosd
    L_00418489:
        mov ecx,dword ptr [data_00477704]
    L_0041848f:
        push 46D278h
    L_00418494:
        push ecx
    L_00418495:
        lea eax,[esp+18h]
    L_00418499:
        call asm_FUN_0040cfb0_0040cfb0
    L_0041849e:
        mov edi,dword ptr [data_0047770c]
    L_004184a4:
        call asm_FUN_00413bc0_00413bc0
    L_004184a9:
        mov eax,dword ptr [data_00477830]
    L_004184ae:
        mov ecx,dword ptr [eax+8]
    L_004184b1:
        cmp ecx,ebp
    L_004184b3:
        mov esi,2
    L_004184b8:
        je short L_004184bd
    L_004184ba:
        or dword ptr [ecx+4],esi
    L_004184bd:
        mov ecx,dword ptr [eax+0Ch]
    L_004184c0:
        cmp ecx,ebp
    L_004184c2:
        je short L_004184c9
    L_004184c4:
        mov eax,ecx
    L_004184c6:
        or dword ptr [eax+4],esi
    L_004184c9:
        mov eax,dword ptr [data_00477834]
    L_004184ce:
        mov ecx,dword ptr [eax+8]
    L_004184d1:
        or dword ptr [ecx+4],esi
    L_004184d4:
        mov ecx,dword ptr [eax+0Ch]
    L_004184d7:
        mov edi,dword ptr [ecx+4]
    L_004184da:
        or edi,esi
    L_004184dc:
        push eax
    L_004184dd:
        mov dword ptr [ecx+4],edi
    L_004184e0:
        call asm_FUN_00426f70_00426f70
    L_004184e5:
        mov eax,dword ptr [data_004776f0]
    L_004184ea:
        mov ecx,dword ptr [eax+8]
    L_004184ed:
        cmp ecx,ebp
    L_004184ef:
        je short L_004184f4
    L_004184f1:
        or dword ptr [ecx+4],esi
    L_004184f4:
        mov ecx,dword ptr [eax+0Ch]
    L_004184f7:
        cmp ecx,ebp
    L_004184f9:
        je short L_00418500
    L_004184fb:
        mov eax,ecx
    L_004184fd:
        or dword ptr [eax+4],esi
    L_00418500:
        mov eax,dword ptr [data_00477704]
    L_00418505:
        mov ecx,dword ptr [eax+8]
    L_00418508:
        cmp ecx,ebp
    L_0041850a:
        je short L_0041850f
    L_0041850c:
        or dword ptr [ecx+4],esi
    L_0041850f:
        mov ecx,dword ptr [eax+0Ch]
    L_00418512:
        cmp ecx,ebp
    L_00418514:
        je short L_0041851b
    L_00418516:
        mov eax,ecx
    L_00418518:
        or dword ptr [eax+4],esi
    L_0041851b:
        mov eax,dword ptr [data_00477818]
    L_00418520:
        mov ecx,dword ptr [eax+8]
    L_00418523:
        cmp ecx,ebp
    L_00418525:
        je short L_0041852a
    L_00418527:
        or dword ptr [ecx+4],esi
    L_0041852a:
        mov ecx,dword ptr [eax+0Ch]
    L_0041852d:
        cmp ecx,ebp
    L_0041852f:
        je short L_00418536
    L_00418531:
        mov eax,ecx
    L_00418533:
        or dword ptr [eax+4],esi
    L_00418536:
        mov eax,dword ptr [data_0047781c]
    L_0041853b:
        mov ecx,dword ptr [eax+8]
    L_0041853e:
        cmp ecx,ebp
    L_00418540:
        je short L_00418545
    L_00418542:
        or dword ptr [ecx+4],esi
    L_00418545:
        mov ecx,dword ptr [eax+0Ch]
    L_00418548:
        cmp ecx,ebp
    L_0041854a:
        je short L_00418551
    L_0041854c:
        mov eax,ecx
    L_0041854e:
        or dword ptr [eax+4],esi
    L_00418551:
        mov ecx,dword ptr [data_004776fc]
    L_00418557:
        mov eax,dword ptr [ecx+8]
    L_0041855a:
        or dword ptr [eax+4],esi
    L_0041855d:
        mov eax,dword ptr [ecx+0Ch]
    L_00418560:
        or dword ptr [eax+4],esi
    L_00418563:
        mov eax,dword ptr [data_004776ec]
    L_00418568:
        mov ecx,dword ptr [eax+8]
    L_0041856b:
        cmp ecx,ebp
    L_0041856d:
        je short L_00418572
    L_0041856f:
        or dword ptr [ecx+4],esi
    L_00418572:
        mov ecx,dword ptr [eax+0Ch]
    L_00418575:
        cmp ecx,ebp
    L_00418577:
        je short L_0041857e
    L_00418579:
        mov eax,ecx
    L_0041857b:
        or dword ptr [eax+4],esi
    L_0041857e:
        mov ecx,dword ptr [data_00477840]
    L_00418584:
        mov eax,dword ptr [ecx+8]
    L_00418587:
        or dword ptr [eax+4],esi
    L_0041858a:
        mov eax,dword ptr [ecx+0Ch]
    L_0041858d:
        or dword ptr [eax+4],esi
    L_00418590:
        mov eax,dword ptr [data_004776f4]
    L_00418595:
        mov ecx,dword ptr [eax+8]
    L_00418598:
        cmp ecx,ebp
    L_0041859a:
        je short L_0041859f
    L_0041859c:
        or dword ptr [ecx+4],esi
    L_0041859f:
        mov ecx,dword ptr [eax+0Ch]
    L_004185a2:
        cmp ecx,ebp
    L_004185a4:
        je short L_004185a9
    L_004185a6:
        or dword ptr [ecx+4],esi
    L_004185a9:
        mov eax,dword ptr [eax+37ACh]
    L_004185af:
        or dword ptr [eax+4],esi
    L_004185b2:
        mov eax,dword ptr [data_00477814]
    L_004185b7:
        mov ecx,dword ptr [eax+8]
    L_004185ba:
        cmp ecx,ebp
    L_004185bc:
        je short L_004185c1
    L_004185be:
        or dword ptr [ecx+4],esi
    L_004185c1:
        mov ecx,dword ptr [eax+0Ch]
    L_004185c4:
        cmp ecx,ebp
    L_004185c6:
        je short L_004185cd
    L_004185c8:
        mov eax,ecx
    L_004185ca:
        or dword ptr [eax+4],esi
    L_004185cd:
        test byte ptr [data_00491d78],10h
    L_004185d4:
        mov edx,46DF98h
    L_004185d9:
        push ebp
    L_004185da:
        mov eax,492590h
    L_004185df:
        je short L_004185e5
    L_004185e1:
        push 4
    L_004185e3:
        jmp short L_004185e7
    L_004185e5:
        push 3
    L_004185e7:
        call asm_AnimationManager_RegisterResource_0043e460
    L_004185ec:
        mov edx,dword ptr [data_00477848]
    L_004185f2:
        mov eax,dword ptr [edx+24h]
    L_004185f5:
        push eax
    L_004185f6:
        push ebp
    L_004185f7:
        call asm_Sound_PlayDummyRetail_00420b10
    L_004185fc:
        mov esi,dword ptr [data_004776e0]
    L_00418602:
        add esi,89A4h
    L_00418608:
        mov eax,esi
    L_0041860a:
        call asm_FUN_00409e50_00409e50
    L_0041860f:
        mov eax,dword ptr [esp+54h]
    L_00418613:
        push ebp
    L_00418614:
        add eax,10h
    L_00418617:
        mov dword ptr [esi],ebp
    L_00418619:
        call asm_Player_SetSchedulerValue_00405410
    L_0041861e:
        mov edi,dword ptr [esp+54h]
    L_00418622:
        mov esi,dword ptr [data_004776e4]
    L_00418628:
        cmp esi,ebp
    L_0041862a:
        je short L_00418648
    L_0041862c:
        test byte ptr [esi+2A18h],8
    L_00418633:
        je short L_00418648
    L_00418635:
        cmp esi,ebp
    L_00418637:
        je short L_00418648
    L_00418639:
        push esi
    L_0041863a:
        call asm_DestroyGameState_00402440
    L_0041863f:
        push esi
    L_00418640:
        call asm_free_004524a1
    L_00418645:
        add esp,4
    L_00418648:
        mov eax,dword ptr [edi+58h]
    L_0041864b:
        test al,4
    L_0041864d:
        je short L_00418666
    L_0041864f:
        or eax,80h
    L_00418654:
        mov dword ptr [edi+58h],eax
    L_00418657:
        pop edi
    L_00418658:
        pop esi
    L_00418659:
        pop ebp
    L_0041865a:
        mov eax,1
    L_0041865f:
        pop ebx
    L_00418660:
        add esp,40h
    L_00418663:
        ret 4
    L_00418666:
        mov esi,492254h
    L_0041866b:
        call asm_Platform_StopWorker_0044c150
    L_00418670:
        test byte ptr [data_00474ca0],20h
    L_00418677:
        je short L_004186d7
    L_00418679:
        test dword ptr [data_00474e30],160Bh
    L_00418683:
        jne short L_0041868b
    L_00418685:
        test byte ptr [edi+58h],70h
    L_00418689:
        je short L_004186a7
    L_0041868b:
        mov ecx,dword ptr [data_00491ff4]
    L_00418691:
        and ecx,1000h
    L_00418697:
        neg ecx
    L_00418699:
        sbb ecx,ecx
    L_0041869b:
        and ecx,0FFFFFFFEh
    L_0041869e:
        add ecx,4
    L_004186a1:
        mov dword ptr [data_00491fb8],ecx
    L_004186a7:
        mov eax,dword ptr [edi+14h]
    L_004186aa:
        cmp eax,0B7Ch
    L_004186af:
        jne short L_004186c4
    L_004186b1:
        push ebp
    L_004186b2:
        push ebp
    L_004186b3:
        push ebp
    L_004186b4:
        push 3Ch
    L_004186b6:
        push 5
    L_004186b8:
        mov ebx,2Bh
    L_004186bd:
        call asm_AsciiManager_CreateRetail_0043c8b0
    L_004186c2:
        jmp short L_004186d7
    L_004186c4:
        cmp eax,0BB8h
    L_004186c9:
        jne short L_004186d7
    L_004186cb:
        push 4
    L_004186cd:
        mov eax,491C28h
    L_004186d2:
        call asm_SetInputMode_0040ac90
    L_004186d7:
        mov esi,dword ptr [data_0047770c]
    L_004186dd:
        call asm_FUN_00417040_00417040
    L_004186e2:
        mov eax,dword ptr [edi+58h]
    L_004186e5:
        test al,10h
    L_004186e7:
        jne short L_004186f1
    L_004186e9:
        test al,20h
    L_004186eb:
        jne short L_004186f1
    L_004186ed:
        test al,40h
    L_004186ef:
        je short L_00418700
    L_004186f1:
        pop edi
    L_004186f2:
        pop esi
    L_004186f3:
        pop ebp
    L_004186f4:
        mov eax,3
    L_004186f9:
        pop ebx
    L_004186fa:
        add esp,40h
    L_004186fd:
        ret 4
    L_00418700:
        mov edx,dword ptr [data_00477838]
    L_00418706:
        cmp dword ptr [edx+10h],1
    L_0041870a:
        je short L_00418740
    L_0041870c:
        mov eax,dword ptr [data_00474c68]
    L_00418711:
        mov ecx,dword ptr [data_00474c6c]
    L_00418717:
        lea edx,[ecx+eax*2]
    L_0041871a:
        add edx,eax
    L_0041871c:
        mov eax,dword ptr [data_0047783c]
    L_00418721:
        imul edx,437Ch
    L_00418727:
        mov ecx,dword ptr [edx+eax+4CCh]
    L_0041872e:
        cmp ecx,0CDFE5FFh
    L_00418734:
        lea eax,[edx+eax+4CCh]
    L_0041873b:
        jge short L_00418740
    L_0041873d:
        inc ecx
    L_0041873e:
        mov dword ptr [eax],ecx
    L_00418740:
        mov ecx,dword ptr [data_00477704]
    L_00418746:
        cmp dword ptr [ecx+10h],ebp
    L_00418749:
        jne short L_00418769
    L_0041874b:
        mov edx,dword ptr [data_0047770c]
    L_00418751:
        cmp dword ptr [edx+9EB8h],ebp
    L_00418757:
        jne short L_00418769
    L_00418759:
        cmp dword ptr [edi+14h],5Ah
    L_0041875d:
        jl short L_00418769
    L_0041875f:
        mov eax,474C40h
    L_00418764:
        call asm_Recovery_DecayCounter_00418a00
    L_00418769:
        mov ecx,dword ptr [data_00474c88]
    L_0041876f:
        mov eax,dword ptr [data_00474c8c]
    L_00418774:
        inc ecx
    L_00418775:
        inc eax
    L_00418776:
        lea esi,[edi+10h]
    L_00418779:
        mov dword ptr [data_00474c88],ecx
    L_0041877f:
        mov dword ptr [data_00474c8c],eax
    L_00418784:
        call asm_FrameTimer_Tick_00404ed0
    L_00418789:
        pop edi
    L_0041878a:
        pop esi
    L_0041878b:
        pop ebp
    L_0041878c:
        mov eax,1
    L_00418791:
        pop ebx
    L_00418792:
        add esp,40h
    L_00418795:
        ret 4
    }
}
