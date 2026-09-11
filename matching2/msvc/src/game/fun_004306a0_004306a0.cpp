#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042F540..0x0042F89A: FUN_0042f540
// Naked body preserves the retail register/stack ABI.

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
