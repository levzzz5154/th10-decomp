#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042F540..0x0042F89A: FUN_0042f540
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042f540_0042f540() {
    __asm {
    L_0042f540:
        mov eax,dword ptr [ebx+20h]
    L_0042f543:
        cmp eax,4
    L_0042f546:
        push ebp
    L_0042f547:
        push edi
    L_0042f548:
        ja asm_target_0042f893
    L_0042f54e:
        push esi
    L_0042f54f:
        jmp dword ptr [eax*4+42F89Ch]
    L_0042f556:
        mov dword ptr [ebx+2Ch],7
    L_0042f55d:
        mov eax,dword ptr [ebx+2Ch]
    L_0042f560:
        test eax,eax
    L_0042f562:
        je short L_0042f573
    L_0042f564:
        jg short L_0042f56c
    L_0042f566:
        dec eax
    L_0042f567:
        mov dword ptr [ebx+24h],eax
    L_0042f56a:
        jmp short L_0042f57a
    L_0042f56c:
        xor eax,eax
    L_0042f56e:
        mov dword ptr [ebx+24h],eax
    L_0042f571:
        jmp short L_0042f57a
    L_0042f573:
        mov dword ptr [ebx+24h],0
    L_0042f57a:
        push ebx
    L_0042f57b:
        mov edi,2
    L_0042f580:
        call asm_Recovery_InstallAnimationSlot_0042c670
    L_0042f585:
        mov ecx,1
    L_0042f58a:
        mov eax,ebx
    L_0042f58c:
        call asm_GameState_SetTimerTarget_0042c620
    L_0042f591:
        mov ax,word ptr [data_00474e88]
    L_0042f597:
        mov word ptr [ebx+59CCh],ax
    L_0042f59e:
        mov cx,word ptr [data_00474e8a]
    L_0042f5a5:
        mov word ptr [ebx+59CEh],cx
    L_0042f5ac:
        mov dx,word ptr [data_00474e8c]
    L_0042f5b3:
        mov word ptr [ebx+59D0h],dx
    L_0042f5ba:
        mov ax,word ptr [data_00474e8e]
    L_0042f5c0:
        mov word ptr [ebx+59D2h],ax
    L_0042f5c7:
        mov cx,word ptr [data_00474e98]
    L_0042f5ce:
        mov eax,ebx
    L_0042f5d0:
        mov word ptr [ebx+59D4h],cx
    L_0042f5d7:
        call asm_FUN_0042f8b0_0042f8b0
    L_0042f5dc:
        cmp dword ptr [ebx+2B4h],6
    L_0042f5e3:
        jle asm_target_0042f892
    L_0042f5e9:
        mov ecx,2
    L_0042f5ee:
        mov eax,ebx
    L_0042f5f0:
        call asm_GameState_SetTimerTarget_0042c620
    L_0042f5f5:
        mov edx,dword ptr [ebx+2CCh]
    L_0042f5fb:
        push edx
    L_0042f5fc:
        mov edx,dword ptr [data_00491c10]
    L_0042f602:
        mov edi,3
    L_0042f607:
        call asm_AnimationManager_SetStopFrameAndRun_00449250
    L_0042f60c:
        xor esi,esi
    L_0042f60e:
        mov si,word ptr [ebx+24h]
    L_0042f612:
        add si,11h
    L_0042f616:
        mov ecx,2
    L_0042f61b:
        mov eax,ebx
    L_0042f61d:
        call asm_FUN_0042c770_0042c770
    L_0042f622:
        pop esi
    L_0042f623:
        pop edi
    L_0042f624:
        mov eax,1
    L_0042f629:
        pop ebp
    L_0042f62a:
        ret
    L_0042f62b:
        mov eax,dword ptr [ebx+24h]
    L_0042f62e:
        lea ebp,[ebx+24h]
    L_0042f631:
        mov dword ptr [ebp+4],eax
    L_0042f634:
        mov cl,byte ptr [data_00474e36]
    L_0042f63a:
        mov al,10h
    L_0042f63c:
        test cl,al
    L_0042f63e:
        jne short L_0042f648
    L_0042f640:
        test byte ptr [data_00474e34],al
    L_0042f646:
        je short L_0042f651
    L_0042f648:
        push 0FFFFFFFFh
    L_0042f64a:
        mov eax,ebp
    L_0042f64c:
        call asm_MenuCursor_Advance_0044bea0
    L_0042f651:
        mov cl,byte ptr [data_00474e36]
    L_0042f657:
        mov al,20h
    L_0042f659:
        test cl,al
    L_0042f65b:
        jne short L_0042f665
    L_0042f65d:
        test byte ptr [data_00474e34],al
    L_0042f663:
        je short L_0042f66e
    L_0042f665:
        push 1
    L_0042f667:
        mov eax,ebp
    L_0042f669:
        call asm_MenuCursor_Advance_0044bea0
    L_0042f66e:
        mov ecx,dword ptr [ebp+4]
    L_0042f671:
        cmp ecx,dword ptr [ebp]
    L_0042f674:
        je short L_0042f6b4
    L_0042f676:
        push 0
    L_0042f678:
        mov edi,0Ch
    L_0042f67d:
        mov ecx,492590h
    L_0042f682:
        call asm_AnimationManager_QueueResource_0043dc90
    L_0042f687:
        mov edx,dword ptr [ebx+2CCh]
    L_0042f68d:
        push edx
    L_0042f68e:
        mov edx,dword ptr [data_00491c10]
    L_0042f694:
        mov edi,3
    L_0042f699:
        call asm_AnimationManager_SetStopFrameAndRun_00449250
    L_0042f69e:
        xor esi,esi
    L_0042f6a0:
        mov si,word ptr [ebp]
    L_0042f6a4:
        add si,7
    L_0042f6a8:
        mov ecx,2
    L_0042f6ad:
        mov eax,ebx
    L_0042f6af:
        call asm_FUN_0042c770_0042c770
    L_0042f6b4:
        xor ecx,ecx
    L_0042f6b6:
        call asm_Input_PollJoystickButtons_0044a4e0
    L_0042f6bb:
        xor edx,edx
    L_0042f6bd:
        TH10_NOP_LEA_ECX_DISP8()
    L_0042f6c0:
        cmp byte ptr [edx+eax],0
    L_0042f6c4:
        js short L_0042f6ce
    L_0042f6c6:
        inc edx
    L_0042f6c7:
        cmp edx,1Fh
    L_0042f6ca:
        jl short L_0042f6c0
    L_0042f6cc:
        jmp short L_0042f6dd
    L_0042f6ce:
        mov ecx,dword ptr [ebp]
    L_0042f6d1:
        cmp ecx,4
    L_0042f6d4:
        jg short L_0042f6dd
    L_0042f6d6:
        mov eax,ebx
    L_0042f6d8:
        call asm_KeyConfig_ReassignSlotRetail_00430250
    L_0042f6dd:
        test byte ptr [data_00474e36],0Ah
    L_0042f6e4:
        je short L_0042f73c
    L_0042f6e6:
        cmp dword ptr [ebp],6
    L_0042f6ea:
        jne short L_0042f73c
    L_0042f6ec:
        mov ax,word ptr [data_00474e88]
    L_0042f6f2:
        mov word ptr [ebx+59CCh],ax
    L_0042f6f9:
        mov cx,word ptr [data_00474e8a]
    L_0042f700:
        mov word ptr [ebx+59CEh],cx
    L_0042f707:
        mov dx,word ptr [data_00474e8c]
    L_0042f70e:
        mov word ptr [ebx+59D0h],dx
    L_0042f715:
        mov ax,word ptr [data_00474e8e]
    L_0042f71b:
        mov word ptr [ebx+59D2h],ax
    L_0042f722:
        mov cx,word ptr [data_00474e98]
    L_0042f729:
        mov eax,ebx
    L_0042f72b:
        mov word ptr [ebx+59D4h],cx
    L_0042f732:
        call asm_FUN_0042f8b0_0042f8b0
    L_0042f737:
        jmp asm_target_0042f7d9
    L_0042f73c:
        test dword ptr [data_00474e36],1001h
    L_0042f746:
        je asm_target_0042f892
    L_0042f74c:
        mov ebp,dword ptr [ebp]
    L_0042f74f:
        sub ebp,5
    L_0042f752:
        je asm_target_0042f810
    L_0042f758:
        dec ebp
    L_0042f759:
        jne asm_target_0042f892
    L_0042f75f:
        mov dx,word ptr [ebx+59CCh]
    L_0042f766:
        mov word ptr [data_00474e88],dx
    L_0042f76d:
        mov ax,word ptr [ebx+59CEh]
    L_0042f774:
        mov word ptr [data_00474e8a],ax
    L_0042f77a:
        mov cx,word ptr [ebx+59D0h]
    L_0042f781:
        mov word ptr [data_00474e8c],cx
    L_0042f788:
        mov dx,word ptr [ebx+59D2h]
    L_0042f78f:
        mov ecx,dword ptr [data_00474e88]
    L_0042f795:
        mov word ptr [data_00474e8e],dx
    L_0042f79c:
        mov ax,word ptr [ebx+59D4h]
    L_0042f7a3:
        mov edx,dword ptr [data_00474e8c]
    L_0042f7a9:
        mov dword ptr [data_00491d4c],ecx
    L_0042f7af:
        mov ecx,dword ptr [data_00474e90]
    L_0042f7b5:
        mov dword ptr [data_00491d50],edx
    L_0042f7bb:
        mov edx,dword ptr [data_00474e94]
    L_0042f7c1:
        mov word ptr [data_00474e98],ax
    L_0042f7c7:
        mov dword ptr [data_00491d54],ecx
    L_0042f7cd:
        mov dword ptr [data_00491d58],edx
    L_0042f7d3:
        mov word ptr [data_00491d5c],ax
    L_0042f7d9:
        push 0
    L_0042f7db:
        mov edi,0Bh
    L_0042f7e0:
        mov ecx,492590h
    L_0042f7e5:
        call asm_AnimationManager_QueueResource_0043dc90
    L_0042f7ea:
        mov esi,6
    L_0042f7ef:
        mov ecx,2
    L_0042f7f4:
        mov eax,ebx
    L_0042f7f6:
        call asm_FUN_0042c770_0042c770
    L_0042f7fb:
        mov ecx,4
    L_0042f800:
        mov eax,ebx
    L_0042f802:
        call asm_GameState_SetTimerTarget_0042c620
    L_0042f807:
        pop esi
    L_0042f808:
        pop edi
    L_0042f809:
        mov eax,1
    L_0042f80e:
        pop ebp
    L_0042f80f:
        ret
    L_0042f810:
        mov ax,word ptr [data_00474e88]
    L_0042f816:
        mov word ptr [ebx+59CCh],ax
    L_0042f81d:
        mov cx,word ptr [data_00474e8a]
    L_0042f824:
        mov word ptr [ebx+59CEh],cx
    L_0042f82b:
        mov dx,word ptr [data_00474e8c]
    L_0042f832:
        mov word ptr [ebx+59D0h],dx
    L_0042f839:
        mov ax,word ptr [data_00474e8e]
    L_0042f83f:
        mov word ptr [ebx+59D2h],ax
    L_0042f846:
        mov cx,word ptr [data_00474e98]
    L_0042f84d:
        mov eax,ebx
    L_0042f84f:
        mov word ptr [ebx+59D4h],cx
    L_0042f856:
        call asm_FUN_0042f8b0_0042f8b0
    L_0042f85b:
        push 0
    L_0042f85d:
        mov edi,0Ah
    L_0042f862:
        mov ecx,492590h
    L_0042f867:
        call asm_AnimationManager_QueueResource_0043dc90
    L_0042f86c:
        pop esi
    L_0042f86d:
        pop edi
    L_0042f86e:
        mov eax,1
    L_0042f873:
        pop ebp
    L_0042f874:
        ret
    L_0042f875:
        cmp dword ptr [ebx+2B4h],0Ah
    L_0042f87c:
        jl short L_0042f892
    L_0042f87e:
        mov ecx,4
    L_0042f883:
        mov eax,ebx
    L_0042f885:
        call asm_GameState_DisableTimerWithOwner_0042c5c0
    L_0042f88a:
        lea eax,[ebx+24h]
    L_0042f88d:
        call asm_Score_InputHistoryStep_0044be70
    L_0042f892:
        pop esi
    L_0042f893:
        pop edi
    L_0042f894:
        mov eax,1
    L_0042f899:
        pop ebp
    L_0042f89a:
        ret
    }
}

// 0x00430320..0x00430680: FUN_00430320
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00430320_00430320() {
    __asm {
    L_00430320:
        push ecx
    L_00430321:
        push ebx
    L_00430322:
        push ebp
    L_00430323:
        mov ebp,dword ptr [esp+10h]
    L_00430327:
        mov eax,dword ptr [ebp+20h]
    L_0043032a:
        xor ebx,ebx
    L_0043032c:
        push esi
    L_0043032d:
        mov esi,dword ptr [data_00474c74]
    L_00430333:
        cmp esi,4
    L_00430336:
        setge bl
    L_00430339:
        add ebx,77h
    L_0043033c:
        cmp eax,4
    L_0043033f:
        mov dword ptr [esp+14h],ebx
    L_00430343:
        ja asm_target_00430675
    L_00430349:
        push edi
    L_0043034a:
        jmp dword ptr [eax*4+430684h]
    L_00430351:
        mov eax,dword ptr [ebp+43Ch]
    L_00430357:
        mov edx,dword ptr [data_00491c10]
    L_0043035d:
        push eax
    L_0043035e:
        call asm_AnimationManager_Find_004491c0
    L_00430363:
        test eax,eax
    L_00430365:
        jne short L_0043039a
    L_00430367:
        push ebp
    L_00430368:
        mov edi,5Eh
    L_0043036d:
        call asm_Recovery_InstallAnimationSlot_0042c670
    L_00430372:
        mov ecx,dword ptr [data_004776e0]
    L_00430378:
        mov eax,dword ptr [ecx+8994h]
    L_0043037e:
        push 0Fh
    L_00430380:
        push 8
    L_00430382:
        push eax
    L_00430383:
        lea edi,[esp+1Ch]
    L_00430387:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_0043038c:
        mov edx,dword ptr [eax]
    L_0043038e:
        mov dword ptr [ebp+5D0h],edx
    L_00430394:
        mov esi,dword ptr [data_00474c74]
    L_0043039a:
        xor eax,eax
    L_0043039c:
        cmp esi,4
    L_0043039f:
        setge al
    L_004303a2:
        mov esi,ebx
    L_004303a4:
        mov edi,ebp
    L_004303a6:
        dec eax
    L_004303a7:
        and eax,3
    L_004303aa:
        inc eax
    L_004303ab:
        mov dword ptr [ebp+2Ch],eax
    L_004303ae:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_004303b3:
        push ebp
    L_004303b4:
        mov edi,ebx
    L_004303b6:
        call asm_Recovery_InstallAnimationSlot_0042c670
    L_004303bb:
        mov ecx,dword ptr [ebp+ebx*4+2C4h]
    L_004303c2:
        mov edx,dword ptr [data_00491c10]
    L_004303c8:
        push ecx
    L_004303c9:
        mov edi,3
    L_004303ce:
        call asm_AnimationManager_SetStopFrameAndRun_00449250
    L_004303d3:
        xor esi,esi
    L_004303d5:
        mov si,word ptr [ebp+24h]
    L_004303d9:
        add si,11h
    L_004303dd:
        mov ecx,ebx
    L_004303df:
        mov eax,ebp
    L_004303e1:
        call asm_FUN_0042c770_0042c770
    L_004303e6:
        push ebp
    L_004303e7:
        mov edi,62h
    L_004303ec:
        call asm_Recovery_InstallAnimationSlot_0042c670
    L_004303f1:
        mov ecx,1
    L_004303f6:
        mov eax,ebp
    L_004303f8:
        call asm_GameState_SetTimerTarget_0042c620
    L_004303fd:
        cmp dword ptr [ebp+2B4h],6
    L_00430404:
        jle asm_target_00430674
    L_0043040a:
        mov ecx,2
    L_0043040f:
        mov eax,ebp
    L_00430411:
        call asm_GameState_SetTimerTarget_0042c620
    L_00430416:
        pop edi
    L_00430417:
        pop esi
    L_00430418:
        pop ebp
    L_00430419:
        mov eax,1
    L_0043041e:
        pop ebx
    L_0043041f:
        pop ecx
    L_00430420:
        ret 4
    L_00430423:
        cmp esi,4
    L_00430426:
        jge short L_0043049c
    L_00430428:
        mov edx,dword ptr [ebp+24h]
    L_0043042b:
        lea esi,[ebp+24h]
    L_0043042e:
        mov eax,10h
    L_00430433:
        mov ecx,474E30h
    L_00430438:
        mov dword ptr [esi+4],edx
    L_0043043b:
        call asm_InputMaskActive_0040ace0
    L_00430440:
        test ax,ax
    L_00430443:
        je short L_0043044e
    L_00430445:
        push 0FFFFFFFFh
    L_00430447:
        mov eax,esi
    L_00430449:
        call asm_MenuCursor_Advance_0044bea0
    L_0043044e:
        mov eax,20h
    L_00430453:
        mov ecx,474E30h
    L_00430458:
        call asm_InputMaskActive_0040ace0
    L_0043045d:
        test ax,ax
    L_00430460:
        je short L_0043046b
    L_00430462:
        push 1
    L_00430464:
        mov eax,esi
    L_00430466:
        call asm_MenuCursor_Advance_0044bea0
    L_0043046b:
        mov eax,dword ptr [esi+4]
    L_0043046e:
        cmp eax,dword ptr [esi]
    L_00430470:
        je short L_0043049c
    L_00430472:
        push 0
    L_00430474:
        mov edi,0Ch
    L_00430479:
        mov ecx,492590h
    L_0043047e:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00430483:
        mov ecx,ebx
    L_00430485:
        mov eax,ebp
    L_00430487:
        call asm_GameState_DispatchAnimationSlotSecondary_0042c750
    L_0043048c:
        movsx esi,word ptr [esi]
    L_0043048f:
        add si,7
    L_00430493:
        mov ecx,ebx
    L_00430495:
        mov eax,ebp
    L_00430497:
        call asm_FUN_0042c770_0042c770
    L_0043049c:
        mov eax,dword ptr [data_00474e36]
    L_004304a1:
        test al,0Ah
    L_004304a3:
        je short L_004304d8
    L_004304a5:
        mov ecx,4
    L_004304aa:
        mov eax,ebp
    L_004304ac:
        call asm_GameState_SetTimerTarget_0042c620
    L_004304b1:
        push 0
    L_004304b3:
        mov edi,0Bh
    L_004304b8:
        mov ecx,492590h
    L_004304bd:
        call asm_AnimationManager_QueueResource_0043dc90
    L_004304c2:
        mov esi,ebx
    L_004304c4:
        mov edi,ebp
    L_004304c6:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_004304cb:
        pop edi
    L_004304cc:
        pop esi
    L_004304cd:
        pop ebp
    L_004304ce:
        mov eax,1
    L_004304d3:
        pop ebx
    L_004304d4:
        pop ecx
    L_004304d5:
        ret 4
    L_004304d8:
        test eax,1001h
    L_004304dd:
        je asm_target_00430674
    L_004304e3:
        mov esi,6
    L_004304e8:
        mov ecx,ebx
    L_004304ea:
        mov eax,ebp
    L_004304ec:
        call asm_FUN_0042c770_0042c770
    L_004304f1:
        cmp dword ptr [data_00474c74],4
    L_004304f8:
        jge short L_00430516
    L_004304fa:
        mov ebx,dword ptr [ebp+24h]
    L_004304fd:
        mov ecx,dword ptr [esp+18h]
    L_00430501:
        add ebx,6Dh
    L_00430504:
        lea esi,[ebp+ecx*4+2C4h]
    L_0043050b:
        lea edi,[esp+18h]
    L_0043050f:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_00430514:
        jmp short L_00430558
    L_00430516:
        mov edx,dword ptr [ebp+ebx*4+2C4h]
    L_0043051d:
        push edx
    L_0043051e:
        mov edx,dword ptr [data_00491c10]
    L_00430524:
        call asm_AnimationManager_Find_004491c0
    L_00430529:
        xor edx,edx
    L_0043052b:
        cmp eax,edx
    L_0043052d:
        jne short L_00430536
    L_0043052f:
        mov dword ptr [ebp+ebx*4+2C4h],edx
    L_00430536:
        add eax,10h
    L_00430539:
        cmp eax,edx
    L_0043053b:
        je short L_00430554
    L_0043053d:
        mov ecx,71h
    L_00430542:
        mov esi,dword ptr [eax]
    L_00430544:
        cmp word ptr [esi+38Ah],cx
    L_0043054b:
        je short L_00430590
    L_0043054d:
        mov eax,dword ptr [eax+4]
    L_00430550:
        cmp eax,edx
    L_00430552:
        jne short L_00430542
    L_00430554:
        mov dword ptr [esp+18h],edx
    L_00430558:
        lea eax,[esp+18h]
    L_0043055c:
        mov esi,2
    L_00430561:
        call asm_AnimationManager_SetStopFrameFromHandleRetail_00449470
    L_00430566:
        mov ecx,3
    L_0043056b:
        mov eax,ebp
    L_0043056d:
        call asm_GameState_SetTimerTarget_0042c620
    L_00430572:
        push 0
    L_00430574:
        mov edi,0Ah
    L_00430579:
        mov ecx,492590h
    L_0043057e:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00430583:
        pop edi
    L_00430584:
        pop esi
    L_00430585:
        pop ebp
    L_00430586:
        mov eax,1
    L_0043058b:
        pop ebx
    L_0043058c:
        pop ecx
    L_0043058d:
        ret 4
    L_00430590:
        mov eax,dword ptr [eax]
    L_00430592:
        mov ecx,dword ptr [eax]
    L_00430594:
        mov dword ptr [esp+18h],ecx
    L_00430598:
        jmp short L_00430558
    L_0043059a:
        cmp dword ptr [ebp+2B4h],0Eh
    L_004305a1:
        jl asm_target_00430674
    L_004305a7:
        mov esi,62h
    L_004305ac:
        mov edi,ebp
    L_004305ae:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_004305b3:
        mov ecx,7
    L_004305b8:
        mov eax,ebp
    L_004305ba:
        call asm_GameState_DisableTimerWithOwner_0042c5c0
    L_004305bf:
        cmp dword ptr [data_00474c74],4
    L_004305c6:
        jge short L_004305d1
    L_004305c8:
        mov edx,dword ptr [ebp+24h]
    L_004305cb:
        mov dword ptr [data_00474c74],edx
    L_004305d1:
        lea eax,[ebp+24h]
    L_004305d4:
        call asm_Score_InputHistorySave_0044be20
    L_004305d9:
        mov dword ptr [ebp+2Ch],2
    L_004305e0:
        mov ecx,dword ptr [data_00474c68]
    L_004305e6:
        mov edx,eax
    L_004305e8:
        call asm_FUN_0040ad20_0040ad20
    L_004305ed:
        pop edi
    L_004305ee:
        pop esi
    L_004305ef:
        pop ebp
    L_004305f0:
        mov eax,1
    L_004305f5:
        pop ebx
    L_004305f6:
        pop ecx
    L_004305f7:
        ret 4
    L_004305fa:
        cmp dword ptr [ebp+2B4h],6
    L_00430601:
        jl short L_00430674
    L_00430603:
        mov esi,62h
    L_00430608:
        mov edi,ebp
    L_0043060a:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_0043060f:
        mov esi,8
    L_00430614:
        mov ecx,5Ah
    L_00430619:
        mov eax,ebp
    L_0043061b:
        call asm_FUN_0042c770_0042c770
    L_00430620:
        mov ecx,5Bh
    L_00430625:
        mov eax,ebp
    L_00430627:
        call asm_FUN_0042c770_0042c770
    L_0043062c:
        mov esi,5Eh
    L_00430631:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_00430636:
        lea eax,[ebp+5D0h]
    L_0043063c:
        call asm_FUN_00409e50_00409e50
    L_00430641:
        mov ecx,2
    L_00430646:
        mov eax,ebp
    L_00430648:
        call asm_GameState_DisableTimerWithOwner_0042c5c0
    L_0043064d:
        cmp dword ptr [data_00474c74],4
    L_00430654:
        jge short L_00430660
    L_00430656:
        mov eax,dword ptr [ebp+24h]
    L_00430659:
        mov dword ptr [data_00474c74],eax
    L_0043065e:
        jmp short L_0043066c
    L_00430660:
        mov ecx,dword ptr [ebp+58F0h]
    L_00430666:
        mov dword ptr [data_00474c74],ecx
    L_0043066c:
        lea eax,[ebp+24h]
    L_0043066f:
        call asm_Score_InputHistoryStep_0044be70
    L_00430674:
        pop edi
    L_00430675:
        pop esi
    L_00430676:
        pop ebp
    L_00430677:
        mov eax,1
    L_0043067c:
        pop ebx
    L_0043067d:
        pop ecx
    L_0043067e:
        ret 4
    }
}

// 0x004306A0..0x00430A47: FUN_004306a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004306a0_004306a0() {
    __asm {
    L_004306a0:
        push ebx
    L_004306a1:
        push ebp
    L_004306a2:
        mov ebp,dword ptr [esp+0Ch]
    L_004306a6:
        mov eax,dword ptr [ebp+20h]
    L_004306a9:
        cmp eax,4
    L_004306ac:
        ja asm_target_00430a3e
    L_004306b2:
        push esi
    L_004306b3:
        push edi
    L_004306b4:
        jmp dword ptr [eax*4+430A48h]
    L_004306bb:
        mov dword ptr [ebp+2Ch],2
    L_004306c2:
        cmp dword ptr [data_00474c74],4
    L_004306c9:
        jne asm_target_0043077c
    L_004306cf:
        mov ecx,dword ptr [data_0047783c]
    L_004306d5:
        mov al,byte ptr [ecx+1D888h]
    L_004306db:
        xor edx,edx
    L_004306dd:
        cmp al,dl
    L_004306df:
        jne short L_0043072c
    L_004306e1:
        cmp byte ptr [ecx+1D889h],dl
    L_004306e7:
        jne short L_0043072c
    L_004306e9:
        cmp byte ptr [ecx+1D88Ah],dl
    L_004306ef:
        jne short L_0043072c
    L_004306f1:
        cmp dword ptr [ebp+24h],edx
    L_004306f4:
        jne short L_00430719
    L_004306f6:
        mov eax,dword ptr [ebp+2Ch]
    L_004306f9:
        cmp eax,edx
    L_004306fb:
        je short L_00430712
    L_004306fd:
        cmp eax,1
    L_00430700:
        jg short L_00430708
    L_00430702:
        dec eax
    L_00430703:
        mov dword ptr [ebp+24h],eax
    L_00430706:
        jmp short L_00430719
    L_00430708:
        mov eax,1
    L_0043070d:
        mov dword ptr [ebp+24h],eax
    L_00430710:
        jmp short L_00430719
    L_00430712:
        mov dword ptr [ebp+24h],1
    L_00430719:
        mov eax,dword ptr [ebp+0F8h]
    L_0043071f:
        mov dword ptr [ebp+eax*4+0B4h],edx
    L_00430726:
        inc dword ptr [ebp+0F8h]
    L_0043072c:
        cmp byte ptr [ecx+1D88Bh],dl
    L_00430732:
        jne short L_0043077c
    L_00430734:
        cmp byte ptr [ecx+1D88Ch],dl
    L_0043073a:
        jne short L_0043077c
    L_0043073c:
        cmp byte ptr [ecx+1D88Dh],dl
    L_00430742:
        jne short L_0043077c
    L_00430744:
        mov eax,dword ptr [ebp+24h]
    L_00430747:
        mov ecx,1
    L_0043074c:
        cmp eax,ecx
    L_0043074e:
        jne short L_00430769
    L_00430750:
        mov eax,dword ptr [ebp+2Ch]
    L_00430753:
        cmp eax,edx
    L_00430755:
        je short L_00430766
    L_00430757:
        jg short L_0043075f
    L_00430759:
        dec eax
    L_0043075a:
        mov dword ptr [ebp+24h],eax
    L_0043075d:
        jmp short L_00430769
    L_0043075f:
        xor eax,eax
    L_00430761:
        mov dword ptr [ebp+24h],eax
    L_00430764:
        jmp short L_00430769
    L_00430766:
        mov dword ptr [ebp+24h],edx
    L_00430769:
        mov edx,dword ptr [ebp+0F8h]
    L_0043076f:
        mov dword ptr [ebp+edx*4+0B4h],ecx
    L_00430776:
        inc dword ptr [ebp+0F8h]
    L_0043077c:
        push ebp
    L_0043077d:
        mov edi,63h
    L_00430782:
        call asm_Recovery_InstallAnimationSlot_0042c670
    L_00430787:
        mov esi,7Dh
    L_0043078c:
        mov edi,ebp
    L_0043078e:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_00430793:
        push ebp
    L_00430794:
        mov edi,esi
    L_00430796:
        call asm_Recovery_InstallAnimationSlot_0042c670
    L_0043079b:
        mov eax,dword ptr [ebp+4B8h]
    L_004307a1:
        mov edx,dword ptr [data_00491c10]
    L_004307a7:
        push eax
    L_004307a8:
        mov edi,3
    L_004307ad:
        call asm_AnimationManager_SetStopFrameAndRun_00449250
    L_004307b2:
        xor esi,esi
    L_004307b4:
        mov si,word ptr [ebp+24h]
    L_004307b8:
        add si,11h
    L_004307bc:
        mov ecx,7Dh
    L_004307c1:
        mov eax,ebp
    L_004307c3:
        call asm_FUN_0042c770_0042c770
    L_004307c8:
        mov ecx,1
    L_004307cd:
        mov eax,ebp
    L_004307cf:
        call asm_GameState_SetTimerTarget_0042c620
    L_004307d4:
        cmp dword ptr [ebp+2B4h],6
    L_004307db:
        jle asm_target_00430a3c
    L_004307e1:
        mov ecx,2
    L_004307e6:
        mov eax,ebp
    L_004307e8:
        call asm_GameState_SetTimerTarget_0042c620
    L_004307ed:
        pop edi
    L_004307ee:
        pop esi
    L_004307ef:
        pop ebp
    L_004307f0:
        mov eax,1
    L_004307f5:
        pop ebx
    L_004307f6:
        ret 4
    L_004307f9:
        mov ecx,dword ptr [ebp+24h]
    L_004307fc:
        lea ebx,[ebp+24h]
    L_004307ff:
        mov dword ptr [ebx+4],ecx
    L_00430802:
        mov cl,byte ptr [data_00474e36]
    L_00430808:
        mov al,40h
    L_0043080a:
        test cl,al
    L_0043080c:
        jne short L_00430816
    L_0043080e:
        test byte ptr [data_00474e34],al
    L_00430814:
        je short L_0043081f
    L_00430816:
        push 0FFFFFFFFh
    L_00430818:
        mov eax,ebx
    L_0043081a:
        call asm_MenuCursor_Advance_0044bea0
    L_0043081f:
        mov cl,byte ptr [data_00474e36]
    L_00430825:
        mov al,80h
    L_00430827:
        test cl,al
    L_00430829:
        jne short L_00430833
    L_0043082b:
        test byte ptr [data_00474e34],al
    L_00430831:
        je short L_0043083c
    L_00430833:
        push 1
    L_00430835:
        mov eax,ebx
    L_00430837:
        call asm_MenuCursor_Advance_0044bea0
    L_0043083c:
        mov edx,dword ptr [ebx+4]
    L_0043083f:
        cmp edx,dword ptr [ebx]
    L_00430841:
        je short L_00430875
    L_00430843:
        push 0
    L_00430845:
        mov edi,0Ch
    L_0043084a:
        mov ecx,492590h
    L_0043084f:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00430854:
        mov ecx,7Dh
    L_00430859:
        mov eax,ebp
    L_0043085b:
        call asm_GameState_DispatchAnimationSlotSecondary_0042c750
    L_00430860:
        xor esi,esi
    L_00430862:
        mov si,word ptr [ebx]
    L_00430865:
        add si,7
    L_00430869:
        mov ecx,7Dh
    L_0043086e:
        mov eax,ebp
    L_00430870:
        call asm_FUN_0042c770_0042c770
    L_00430875:
        mov eax,dword ptr [data_00474e36]
    L_0043087a:
        test al,0Ah
    L_0043087c:
        je short L_004308a7
    L_0043087e:
        mov ecx,4
    L_00430883:
        mov eax,ebp
    L_00430885:
        call asm_GameState_SetTimerTarget_0042c620
    L_0043088a:
        push 0
    L_0043088c:
        mov edi,0Bh
    L_00430891:
        mov ecx,492590h
    L_00430896:
        call asm_AnimationManager_QueueResource_0043dc90
    L_0043089b:
        pop edi
    L_0043089c:
        pop esi
    L_0043089d:
        pop ebp
    L_0043089e:
        mov eax,1
    L_004308a3:
        pop ebx
    L_004308a4:
        ret 4
    L_004308a7:
        test eax,1001h
    L_004308ac:
        je asm_target_00430a3c
    L_004308b2:
        mov ebx,dword ptr [ebx]
    L_004308b4:
        lea esi,[ebp+4B8h]
    L_004308ba:
        add ebx,79h
    L_004308bd:
        lea edi,[esp+14h]
    L_004308c1:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_004308c6:
        mov esi,6
    L_004308cb:
        mov eax,edi
    L_004308cd:
        call asm_AnimationManager_SetStopFrameFromHandleRetail_00449470
    L_004308d2:
        mov ebx,dword ptr [ebp+24h]
    L_004308d5:
        add ebx,7Bh
    L_004308d8:
        lea edi,[esp+14h]
    L_004308dc:
        lea esi,[ebp+4B8h]
    L_004308e2:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_004308e7:
        mov esi,6
    L_004308ec:
        mov eax,edi
    L_004308ee:
        call asm_AnimationManager_SetStopFrameFromHandleRetail_00449470
    L_004308f3:
        mov edx,dword ptr [ebp+24h]
    L_004308f6:
        mov ebx,7Ah
    L_004308fb:
        sub ebx,edx
    L_004308fd:
        lea edi,[esp+14h]
    L_00430901:
        lea esi,[ebp+4B8h]
    L_00430907:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_0043090c:
        mov esi,1
    L_00430911:
        mov eax,edi
    L_00430913:
        call asm_AnimationManager_SetStopFrameFromHandleRetail_00449470
    L_00430918:
        mov ecx,dword ptr [ebp+24h]
    L_0043091b:
        mov ebx,7Ch
    L_00430920:
        sub ebx,ecx
    L_00430922:
        lea edi,[esp+14h]
    L_00430926:
        lea esi,[ebp+4B8h]
    L_0043092c:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_00430931:
        mov esi,1
    L_00430936:
        mov eax,edi
    L_00430938:
        call asm_AnimationManager_SetStopFrameFromHandleRetail_00449470
    L_0043093d:
        push 0
    L_0043093f:
        mov edi,0Ah
    L_00430944:
        mov ecx,492590h
    L_00430949:
        call asm_AnimationManager_QueueResource_0043dc90
    L_0043094e:
        mov ecx,3
    L_00430953:
        mov eax,ebp
    L_00430955:
        call asm_GameState_SetTimerTarget_0042c620
    L_0043095a:
        pop edi
    L_0043095b:
        pop esi
    L_0043095c:
        pop ebp
    L_0043095d:
        mov eax,1
    L_00430962:
        pop ebx
    L_00430963:
        ret 4
    L_00430966:
        cmp dword ptr [ebp+2B4h],0Eh
    L_0043096d:
        jl asm_target_00430a3c
    L_00430973:
        mov esi,63h
    L_00430978:
        mov edi,ebp
    L_0043097a:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_0043097f:
        mov ecx,8
    L_00430984:
        mov eax,ebp
    L_00430986:
        call asm_GameState_DisableTimerWithOwner_0042c5c0
    L_0043098b:
        mov esi,dword ptr [ebp+24h]
    L_0043098e:
        mov edi,dword ptr [data_00474c68]
    L_00430994:
        lea eax,[ebp+24h]
    L_00430997:
        mov dword ptr [data_00474c68],esi
    L_0043099d:
        call asm_Score_InputHistorySave_0044be20
    L_004309a2:
        cmp edi,esi
    L_004309a4:
        mov dword ptr [ebp+2Ch],3
    L_004309ab:
        je short L_004309e7
    L_004309ad:
        mov ecx,dword ptr [eax+8]
    L_004309b0:
        test ecx,ecx
    L_004309b2:
        je short L_004309d5
    L_004309b4:
        jg short L_004309c5
    L_004309b6:
        pop edi
    L_004309b7:
        pop esi
    L_004309b8:
        dec ecx
    L_004309b9:
        pop ebp
    L_004309ba:
        mov dword ptr [eax],ecx
    L_004309bc:
        mov eax,1
    L_004309c1:
        pop ebx
    L_004309c2:
        ret 4
    L_004309c5:
        pop edi
    L_004309c6:
        pop esi
    L_004309c7:
        xor ecx,ecx
    L_004309c9:
        pop ebp
    L_004309ca:
        mov dword ptr [eax],ecx
    L_004309cc:
        mov eax,1
    L_004309d1:
        pop ebx
    L_004309d2:
        ret 4
    L_004309d5:
        pop edi
    L_004309d6:
        pop esi
    L_004309d7:
        pop ebp
    L_004309d8:
        mov dword ptr [eax],0
    L_004309de:
        mov eax,1
    L_004309e3:
        pop ebx
    L_004309e4:
        ret 4
    L_004309e7:
        mov ecx,dword ptr [data_00474c6c]
    L_004309ed:
        mov edx,eax
    L_004309ef:
        call asm_FUN_0040ad20_0040ad20
    L_004309f4:
        pop edi
    L_004309f5:
        pop esi
    L_004309f6:
        pop ebp
    L_004309f7:
        mov eax,1
    L_004309fc:
        pop ebx
    L_004309fd:
        ret 4
    L_00430a00:
        cmp dword ptr [ebp+2B4h],6
    L_00430a07:
        jl short L_00430a3c
    L_00430a09:
        mov esi,7Dh
    L_00430a0e:
        mov edi,ebp
    L_00430a10:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_00430a15:
        mov esi,63h
    L_00430a1a:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_00430a1f:
        mov ecx,6
    L_00430a24:
        mov eax,ebp
    L_00430a26:
        call asm_GameState_DisableTimerWithOwner_0042c5c0
    L_00430a2b:
        mov ecx,dword ptr [ebp+24h]
    L_00430a2e:
        lea eax,[ebp+24h]
    L_00430a31:
        mov dword ptr [data_00474c68],ecx
    L_00430a37:
        call asm_Score_InputHistoryStep_0044be70
    L_00430a3c:
        pop edi
    L_00430a3d:
        pop esi
    L_00430a3e:
        pop ebp
    L_00430a3f:
        mov eax,1
    L_00430a44:
        pop ebx
    L_00430a45:
        ret 4
    }
}
