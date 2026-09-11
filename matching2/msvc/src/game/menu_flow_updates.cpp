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
        _emit 0x90
        _emit 0x56
        _emit 0xf5
        _emit 0x42
        _emit 0x00
        _emit 0xdc
        _emit 0xf5
        _emit 0x42
        _emit 0x00
        _emit 0x2b
        _emit 0xf6
        _emit 0x42
        _emit 0x00
        _emit 0x92
        _emit 0xf8
        _emit 0x42
        _emit 0x00
        _emit 0x75
        _emit 0xf8
        _emit 0x42
        _emit 0x00
    }
}


