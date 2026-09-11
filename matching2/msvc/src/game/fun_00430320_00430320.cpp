#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042F540..0x0042F89A: FUN_0042f540
// Naked body preserves the retail register/stack ABI.

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
        _emit 0x8d
        _emit 0x49
        _emit 0x00
        _emit 0x51
        _emit 0x03
        _emit 0x43
        _emit 0x00
        _emit 0xfd
        _emit 0x03
        _emit 0x43
        _emit 0x00
        _emit 0x23
        _emit 0x04
        _emit 0x43
        _emit 0x00
        _emit 0x9a
        _emit 0x05
        _emit 0x43
        _emit 0x00
        _emit 0xfa
        _emit 0x05
        _emit 0x43
        _emit 0x00
    }
}
