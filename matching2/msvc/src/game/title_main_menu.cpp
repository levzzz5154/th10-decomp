#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042D420..0x0042D8CA: FUN_0042d420
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042d420_0042d420() {
    __asm {
    L_0042d420:
        mov eax,dword ptr [ebx+20h]
    L_0042d423:
        cmp eax,4
    L_0042d426:
        push ebp
    L_0042d427:
        ja asm_target_0042d8c4
    L_0042d42d:
        push esi
    L_0042d42e:
        push edi
    L_0042d42f:
        jmp dword ptr [eax*4+42D8CCh]
    L_0042d436:
        mov eax,dword ptr [data_0047783c]
    L_0042d43b:
        mov dword ptr [ebx+2Ch],8
    L_0042d442:
        call asm_GameProgress_HasAnyPlayRecord_0042c850
    L_0042d447:
        test eax,eax
    L_0042d449:
        jne short L_0042d462
    L_0042d44b:
        mov eax,dword ptr [ebx+0F8h]
    L_0042d451:
        mov dword ptr [ebx+eax*4+0B4h],1
    L_0042d45c:
        inc dword ptr [ebx+0F8h]
    L_0042d462:
        test byte ptr [data_00474ca0],10h
    L_0042d469:
        je short L_0042d495
    L_0042d46b:
        mov eax,dword ptr [ebx+2Ch]
    L_0042d46e:
        test eax,eax
    L_0042d470:
        je short L_0042d487
    L_0042d472:
        cmp eax,2
    L_0042d475:
        jg short L_0042d47d
    L_0042d477:
        dec eax
    L_0042d478:
        mov dword ptr [ebx+24h],eax
    L_0042d47b:
        jmp short L_0042d48e
    L_0042d47d:
        mov eax,2
    L_0042d482:
        mov dword ptr [ebx+24h],eax
    L_0042d485:
        jmp short L_0042d48e
    L_0042d487:
        mov dword ptr [ebx+24h],2
    L_0042d48e:
        and dword ptr [data_00474ca0],0FFFFFFEFh
    L_0042d495:
        mov ecx,dword ptr [ebx+424h]
    L_0042d49b:
        mov edx,dword ptr [data_00491c10]
    L_0042d4a1:
        push ecx
    L_0042d4a2:
        call asm_AnimationManager_Find_004491c0
    L_0042d4a7:
        test eax,eax
    L_0042d4a9:
        jne short L_0042d4b6
    L_0042d4ab:
        push ebx
    L_0042d4ac:
        mov edi,58h
    L_0042d4b1:
        call asm_Recovery_InstallAnimationSlot_0042c670
    L_0042d4b6:
        push ebx
    L_0042d4b7:
        xor edi,edi
    L_0042d4b9:
        call asm_Recovery_InstallAnimationSlot_0042c670
    L_0042d4be:
        mov ecx,1
    L_0042d4c3:
        mov eax,ebx
    L_0042d4c5:
        call asm_GameState_SetTimerTarget_0042c620
    L_0042d4ca:
        cmp dword ptr [ebx+2B4h],0Ah
    L_0042d4d1:
        jle asm_target_0042d8c2
    L_0042d4d7:
        mov ecx,2
    L_0042d4dc:
        mov eax,ebx
    L_0042d4de:
        call asm_GameState_SetTimerTarget_0042c620
    L_0042d4e3:
        mov edx,dword ptr [ebx+2C4h]
    L_0042d4e9:
        push edx
    L_0042d4ea:
        mov edx,dword ptr [data_00491c10]
    L_0042d4f0:
        mov edi,3
    L_0042d4f5:
        call asm_AnimationManager_SetStopFrameAndRun_00449250
    L_0042d4fa:
        xor esi,esi
    L_0042d4fc:
        mov si,word ptr [ebx+24h]
    L_0042d500:
        add si,11h
    L_0042d504:
        xor ecx,ecx
    L_0042d506:
        mov eax,ebx
    L_0042d508:
        call asm_FUN_0042c770_0042c770
    L_0042d50d:
        pop edi
    L_0042d50e:
        pop esi
    L_0042d50f:
        mov eax,1
    L_0042d514:
        pop ebp
    L_0042d515:
        ret
    L_0042d516:
        mov eax,dword ptr [ebx+24h]
    L_0042d519:
        lea ebp,[ebx+24h]
    L_0042d51c:
        mov dword ptr [ebp+4],eax
    L_0042d51f:
        mov cl,byte ptr [data_00474e36]
    L_0042d525:
        mov al,10h
    L_0042d527:
        test cl,al
    L_0042d529:
        jne short L_0042d533
    L_0042d52b:
        test byte ptr [data_00474e34],al
    L_0042d531:
        je short L_0042d53c
    L_0042d533:
        push 0FFFFFFFFh
    L_0042d535:
        mov eax,ebp
    L_0042d537:
        call asm_MenuCursor_Advance_0044bea0
    L_0042d53c:
        mov cl,byte ptr [data_00474e36]
    L_0042d542:
        mov al,20h
    L_0042d544:
        test cl,al
    L_0042d546:
        jne short L_0042d550
    L_0042d548:
        test byte ptr [data_00474e34],al
    L_0042d54e:
        je short L_0042d559
    L_0042d550:
        push 1
    L_0042d552:
        mov eax,ebp
    L_0042d554:
        call asm_MenuCursor_Advance_0044bea0
    L_0042d559:
        mov ecx,dword ptr [ebp+4]
    L_0042d55c:
        cmp ecx,dword ptr [ebp]
    L_0042d55f:
        je short L_0042d59c
    L_0042d561:
        push 0
    L_0042d563:
        mov edi,0Ch
    L_0042d568:
        mov ecx,492590h
    L_0042d56d:
        call asm_AnimationManager_QueueResource_0043dc90
    L_0042d572:
        mov edx,dword ptr [ebx+2C4h]
    L_0042d578:
        push edx
    L_0042d579:
        mov edx,dword ptr [data_00491c10]
    L_0042d57f:
        mov edi,3
    L_0042d584:
        call asm_AnimationManager_SetStopFrameAndRun_00449250
    L_0042d589:
        xor esi,esi
    L_0042d58b:
        mov si,word ptr [ebp]
    L_0042d58f:
        add si,7
    L_0042d593:
        xor ecx,ecx
    L_0042d595:
        mov eax,ebx
    L_0042d597:
        call asm_FUN_0042c770_0042c770
    L_0042d59c:
        test byte ptr [data_00474e36],0Ah
    L_0042d5a3:
        je short L_0042d5ff
    L_0042d5a5:
        cmp dword ptr [ebp],7
    L_0042d5a9:
        je asm_target_0042d700
    L_0042d5af:
        push 0
    L_0042d5b1:
        mov edi,0Bh
    L_0042d5b6:
        mov ecx,492590h
    L_0042d5bb:
        call asm_AnimationManager_QueueResource_0043dc90
    L_0042d5c0:
        mov eax,dword ptr [ebp+8]
    L_0042d5c3:
        test eax,eax
    L_0042d5c5:
        je short L_0042d5dc
    L_0042d5c7:
        cmp eax,7
    L_0042d5ca:
        jg short L_0042d5d2
    L_0042d5cc:
        dec eax
    L_0042d5cd:
        mov dword ptr [ebp],eax
    L_0042d5d0:
        jmp short L_0042d5e3
    L_0042d5d2:
        mov eax,7
    L_0042d5d7:
        mov dword ptr [ebp],eax
    L_0042d5da:
        jmp short L_0042d5e3
    L_0042d5dc:
        mov dword ptr [ebp],7
    L_0042d5e3:
        xor ecx,ecx
    L_0042d5e5:
        mov eax,ebx
    L_0042d5e7:
        call asm_GameState_DispatchAnimationSlotSecondary_0042c750
    L_0042d5ec:
        xor esi,esi
    L_0042d5ee:
        mov si,word ptr [ebp]
    L_0042d5f2:
        add si,7
    L_0042d5f6:
        xor ecx,ecx
    L_0042d5f8:
        mov eax,ebx
    L_0042d5fa:
        call asm_FUN_0042c770_0042c770
    L_0042d5ff:
        test dword ptr [data_00474e36],1001h
    L_0042d609:
        je asm_target_0042d8c2
    L_0042d60f:
        mov esi,6
    L_0042d614:
        xor ecx,ecx
    L_0042d616:
        mov eax,ebx
    L_0042d618:
        call asm_FUN_0042c770_0042c770
    L_0042d61d:
        mov ebp,dword ptr [ebp]
    L_0042d620:
        cmp ebp,7
    L_0042d623:
        ja asm_target_0042d8c2
    L_0042d629:
        jmp dword ptr [ebp*4+42D8E0h]
    L_0042d630:
        push 0
    L_0042d632:
        mov edi,0Ah
    L_0042d637:
        mov ecx,492590h
    L_0042d63c:
        call asm_AnimationManager_QueueResource_0043dc90
    L_0042d641:
        mov esi,7
    L_0042d646:
        mov ecx,5Ah
    L_0042d64b:
        mov eax,ebx
    L_0042d64d:
        call asm_FUN_0042c770_0042c770
    L_0042d652:
        mov ecx,5Bh
    L_0042d657:
        mov eax,ebx
    L_0042d659:
        call asm_FUN_0042c770_0042c770
    L_0042d65e:
        mov ecx,4
    L_0042d663:
        mov eax,ebx
    L_0042d665:
        call asm_GameState_SetTimerTarget_0042c620
    L_0042d66a:
        pop edi
    L_0042d66b:
        pop esi
    L_0042d66c:
        mov eax,1
    L_0042d671:
        pop ebp
    L_0042d672:
        ret
    L_0042d673:
        push 0
    L_0042d675:
        mov edi,0Ah
    L_0042d67a:
        mov ecx,492590h
    L_0042d67f:
        call asm_AnimationManager_QueueResource_0043dc90
    L_0042d684:
        mov esi,7
    L_0042d689:
        mov ecx,5Ah
    L_0042d68e:
        mov eax,ebx
    L_0042d690:
        call asm_FUN_0042c770_0042c770
    L_0042d695:
        mov ecx,5Bh
    L_0042d69a:
        mov eax,ebx
    L_0042d69c:
        call asm_FUN_0042c770_0042c770
    L_0042d6a1:
        mov ecx,4
    L_0042d6a6:
        mov eax,ebx
    L_0042d6a8:
        call asm_GameState_SetTimerTarget_0042c620
    L_0042d6ad:
        push 0
    L_0042d6af:
        mov ecx,492590h
    L_0042d6b4:
        call asm_AnimationManager_QueueResource_0043dc90
    L_0042d6b9:
        pop edi
    L_0042d6ba:
        pop esi
    L_0042d6bb:
        mov eax,1
    L_0042d6c0:
        pop ebp
    L_0042d6c1:
        ret
    L_0042d6c2:
        push 0
    L_0042d6c4:
        mov edi,0Ah
    L_0042d6c9:
        mov ecx,492590h
    L_0042d6ce:
        call asm_AnimationManager_QueueResource_0043dc90
    L_0042d6d3:
        mov ecx,4
    L_0042d6d8:
        mov eax,ebx
    L_0042d6da:
        call asm_GameState_SetTimerTarget_0042c620
    L_0042d6df:
        mov ecx,5Ah
    L_0042d6e4:
        mov eax,ebx
    L_0042d6e6:
        call asm_GameState_DispatchAnimationSlotSecondary_0042c750
    L_0042d6eb:
        mov ecx,5Bh
    L_0042d6f0:
        mov eax,ebx
    L_0042d6f2:
        call asm_GameState_DispatchAnimationSlotSecondary_0042c750
    L_0042d6f7:
        pop edi
    L_0042d6f8:
        pop esi
    L_0042d6f9:
        mov eax,1
    L_0042d6fe:
        pop ebp
    L_0042d6ff:
        ret
    L_0042d700:
        push 0
    L_0042d702:
        mov edi,0Bh
    L_0042d707:
        mov ecx,492590h
    L_0042d70c:
        call asm_AnimationManager_QueueResource_0043dc90
    L_0042d711:
        mov ecx,4
    L_0042d716:
        mov eax,ebx
    L_0042d718:
        call asm_GameState_SetTimerTarget_0042c620
    L_0042d71d:
        pop edi
    L_0042d71e:
        pop esi
    L_0042d71f:
        mov eax,1
    L_0042d724:
        pop ebp
    L_0042d725:
        ret
    L_0042d726:
        cmp dword ptr [ebx+2B4h],14h
    L_0042d72d:
        jl asm_target_0042d8c2
    L_0042d733:
        mov eax,dword ptr [ebx+24h]
    L_0042d736:
        cmp eax,7
    L_0042d739:
        lea ebp,[ebx+24h]
    L_0042d73c:
        ja asm_target_0042d8c2
    L_0042d742:
        jmp dword ptr [eax*4+42D900h]
    L_0042d749:
        mov ecx,dword ptr [data_00474ca0]
    L_0042d74f:
        and ecx,0FFFFFFEFh
    L_0042d752:
        jmp asm_target_0042d7d7
    L_0042d757:
        mov edx,dword ptr [data_00474ca0]
    L_0042d75d:
        and edx,0FFFFFFEFh
    L_0042d760:
        mov esi,58h
    L_0042d765:
        mov edi,ebx
    L_0042d767:
        mov dword ptr [data_00474ca0],edx
    L_0042d76d:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_0042d772:
        mov ecx,6
    L_0042d777:
        mov eax,ebx
    L_0042d779:
        call asm_GameState_DisableTimerWithOwner_0042c5c0
    L_0042d77e:
        mov eax,ebp
    L_0042d780:
        call asm_Score_InputHistorySave_0044be20
    L_0042d785:
        mov eax,dword ptr [data_00474c74]
    L_0042d78a:
        mov dword ptr [ebx+58F0h],eax
    L_0042d790:
        mov dword ptr [data_00474c74],4
    L_0042d79a:
        mov eax,dword ptr [ebp+8]
    L_0042d79d:
        test eax,eax
    L_0042d79f:
        je short L_0042d7be
    L_0042d7a1:
        jg short L_0042d7b0
    L_0042d7a3:
        pop edi
    L_0042d7a4:
        dec eax
    L_0042d7a5:
        mov dword ptr [ebp],eax
    L_0042d7a8:
        pop esi
    L_0042d7a9:
        mov eax,1
    L_0042d7ae:
        pop ebp
    L_0042d7af:
        ret
    L_0042d7b0:
        pop edi
    L_0042d7b1:
        xor eax,eax
    L_0042d7b3:
        mov dword ptr [ebp],eax
    L_0042d7b6:
        pop esi
    L_0042d7b7:
        mov eax,1
    L_0042d7bc:
        pop ebp
    L_0042d7bd:
        ret
    L_0042d7be:
        pop edi
    L_0042d7bf:
        pop esi
    L_0042d7c0:
        mov dword ptr [ebp],0
    L_0042d7c7:
        mov eax,1
    L_0042d7cc:
        pop ebp
    L_0042d7cd:
        ret
    L_0042d7ce:
        mov ecx,dword ptr [data_00474ca0]
    L_0042d7d4:
        or ecx,10h
    L_0042d7d7:
        mov edi,ebx
    L_0042d7d9:
        mov esi,58h
    L_0042d7de:
        mov dword ptr [data_00474ca0],ecx
    L_0042d7e4:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_0042d7e9:
        mov eax,ebx
    L_0042d7eb:
        mov ecx,6
    L_0042d7f0:
        call asm_GameState_DisableTimerWithOwner_0042c5c0
    L_0042d7f5:
        mov eax,ebp
    L_0042d7f7:
        call asm_Score_InputHistorySave_0044be20
    L_0042d7fc:
        mov ecx,dword ptr [data_00474c74]
    L_0042d802:
        cmp ecx,4
    L_0042d805:
        jl short L_0042d812
    L_0042d807:
        mov ecx,1
    L_0042d80c:
        mov dword ptr [data_00474c74],ecx
    L_0042d812:
        mov edx,ebp
    L_0042d814:
        call asm_FUN_0040ad20_0040ad20
    L_0042d819:
        pop edi
    L_0042d81a:
        pop esi
    L_0042d81b:
        mov eax,1
    L_0042d820:
        pop ebp
    L_0042d821:
        ret
    L_0042d822:
        mov esi,58h
    L_0042d827:
        mov edi,ebx
    L_0042d829:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_0042d82e:
        mov ecx,0Ch
    L_0042d833:
        mov eax,ebx
    L_0042d835:
        call asm_GameState_DisableTimerWithOwner_0042c5c0
    L_0042d83a:
        mov eax,ebp
    L_0042d83c:
        call asm_Score_InputHistorySave_0044be20
    L_0042d841:
        pop edi
    L_0042d842:
        pop esi
    L_0042d843:
        mov eax,1
    L_0042d848:
        pop ebp
    L_0042d849:
        ret
    L_0042d84a:
        mov esi,58h
    L_0042d84f:
        mov edi,ebx
    L_0042d851:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_0042d856:
        mov ecx,0Bh
    L_0042d85b:
        mov eax,ebx
    L_0042d85d:
        call asm_GameState_DisableTimerWithOwner_0042c5c0
    L_0042d862:
        mov eax,ebp
    L_0042d864:
        call asm_Score_InputHistorySave_0044be20
    L_0042d869:
        pop edi
    L_0042d86a:
        pop esi
    L_0042d86b:
        mov eax,1
    L_0042d870:
        pop ebp
    L_0042d871:
        ret
    L_0042d872:
        mov esi,58h
    L_0042d877:
        mov edi,ebx
    L_0042d879:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_0042d87e:
        mov ecx,0Eh
    L_0042d883:
        mov eax,ebx
    L_0042d885:
        call asm_GameState_DisableTimerWithOwner_0042c5c0
    L_0042d88a:
        mov eax,ebp
    L_0042d88c:
        call asm_Score_InputHistorySave_0044be20
    L_0042d891:
        pop edi
    L_0042d892:
        pop esi
    L_0042d893:
        mov eax,1
    L_0042d898:
        pop ebp
    L_0042d899:
        ret
    L_0042d89a:
        mov ecx,4
    L_0042d89f:
        mov eax,ebx
    L_0042d8a1:
        call asm_GameState_DisableTimerWithOwner_0042c5c0
    L_0042d8a6:
        mov eax,ebp
    L_0042d8a8:
        call asm_Score_InputHistorySave_0044be20
    L_0042d8ad:
        pop edi
    L_0042d8ae:
        pop esi
    L_0042d8af:
        mov eax,1
    L_0042d8b4:
        pop ebp
    L_0042d8b5:
        ret
    L_0042d8b6:
        mov ecx,3
    L_0042d8bb:
        mov eax,ebx
    L_0042d8bd:
        call asm_GameState_DisableTimerWithOwner_0042c5c0
    L_0042d8c2:
        pop edi
    L_0042d8c3:
        pop esi
    L_0042d8c4:
        mov eax,1
    L_0042d8c9:
        pop ebp
    L_0042d8ca:
        ret
        _emit 0x90
        _emit 0x36
        _emit 0xd4
        _emit 0x42
        _emit 0x00
        _emit 0xca
        _emit 0xd4
        _emit 0x42
        _emit 0x00
        _emit 0x16
        _emit 0xd5
        _emit 0x42
        _emit 0x00
        _emit 0xc2
        _emit 0xd8
        _emit 0x42
        _emit 0x00
        _emit 0x26
        _emit 0xd7
        _emit 0x42
        _emit 0x00
        _emit 0x30
        _emit 0xd6
        _emit 0x42
        _emit 0x00
        _emit 0x30
        _emit 0xd6
        _emit 0x42
        _emit 0x00
        _emit 0x30
        _emit 0xd6
        _emit 0x42
        _emit 0x00
        _emit 0x30
        _emit 0xd6
        _emit 0x42
        _emit 0x00
        _emit 0x30
        _emit 0xd6
        _emit 0x42
        _emit 0x00
        _emit 0x73
        _emit 0xd6
        _emit 0x42
        _emit 0x00
        _emit 0xc2
        _emit 0xd6
        _emit 0x42
        _emit 0x00
        _emit 0x00
        _emit 0xd7
        _emit 0x42
        _emit 0x00
        _emit 0x49
        _emit 0xd7
        _emit 0x42
        _emit 0x00
        _emit 0x57
        _emit 0xd7
        _emit 0x42
        _emit 0x00
        _emit 0xce
        _emit 0xd7
        _emit 0x42
        _emit 0x00
        _emit 0x22
        _emit 0xd8
        _emit 0x42
        _emit 0x00
        _emit 0x4a
        _emit 0xd8
        _emit 0x42
        _emit 0x00
        _emit 0x72
        _emit 0xd8
        _emit 0x42
        _emit 0x00
        _emit 0x9a
        _emit 0xd8
        _emit 0x42
        _emit 0x00
        _emit 0xb6
        _emit 0xd8
        _emit 0x42
        _emit 0x00
    }
}
