#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004315C0..0x004316E9: FUN_004315c0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004315c0_004315c0() {
    __asm {
    L_004315c0:
        sub esp,188h
    L_004315c6:
        mov eax,dword ptr [data_00473660]
    L_004315cb:
        xor eax,esp
    L_004315cd:
        push ebp
    L_004315ce:
        mov ebp,dword ptr [esp+190h]
    L_004315d5:
        mov dword ptr [esp+188h],eax
    L_004315dc:
        mov eax,dword ptr [ebp+20h]
    L_004315df:
        cmp eax,5
    L_004315e2:
        ja asm_target_00431b5d
    L_004315e8:
        push ebx
    L_004315e9:
        push esi
    L_004315ea:
        push edi
    L_004315eb:
        jmp dword ptr [eax*4+431B7Ch]
    L_004315f2:
        mov ecx,dword ptr [data_00491c04]
    L_004315f8:
        lea edx,[ebp+24h]
    L_004315fb:
        mov dword ptr [ebp+2Ch],19h
    L_00431602:
        call asm_FUN_0040ad20_0040ad20
    L_00431607:
        mov eax,dword ptr [ebp+43Ch]
    L_0043160d:
        mov edx,dword ptr [data_00491c10]
    L_00431613:
        xor ebx,ebx
    L_00431615:
        push eax
    L_00431616:
        mov dword ptr [data_00491c04],ebx
    L_0043161c:
        call asm_AnimationManager_Find_004491c0
    L_00431621:
        test eax,eax
    L_00431623:
        jne short L_00431652
    L_00431625:
        push ebp
    L_00431626:
        mov edi,5Eh
    L_0043162b:
        call asm_Recovery_InstallAnimationSlot_0042c670
    L_00431630:
        mov ecx,dword ptr [data_004776e0]
    L_00431636:
        mov eax,dword ptr [ecx+8994h]
    L_0043163c:
        push 0Fh
    L_0043163e:
        push 8
    L_00431640:
        push eax
    L_00431641:
        lea edi,[esp+1Ch]
    L_00431645:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_0043164a:
        mov edx,dword ptr [eax]
    L_0043164c:
        mov dword ptr [ebp+5D0h],edx
    L_00431652:
        push ebp
    L_00431653:
        mov edi,65h
    L_00431658:
        call asm_Recovery_InstallAnimationSlot_0042c670
    L_0043165d:
        mov ecx,1
    L_00431662:
        mov eax,ebp
    L_00431664:
        call asm_GameState_SetTimerTarget_0042c620
    L_00431669:
        lea edx,[ebp+59E4h]
    L_0043166f:
        mov ecx,32h
    L_00431674:
        xor eax,eax
    L_00431676:
        mov edi,edx
    L_00431678:
        rep stosd
    L_0043167a:
        mov esi,1
    L_0043167f:
        mov edi,edx
    L_00431681:
        push esi
    L_00431682:
        lea eax,[esp+158h]
    L_00431689:
        push 46E0C8h
    L_0043168e:
        push eax
    L_0043168f:
        call asm_sprintf_00452ae8
    L_00431694:
        add esp,0Ch
    L_00431697:
        lea ecx,[esp+154h]
    L_0043169e:
        push ecx
    L_0043169f:
        call asm_StageManager_CreateRetail_004296f0
    L_004316a4:
        mov dword ptr [edi],eax
    L_004316a6:
        inc esi
    L_004316a7:
        add edi,4
    L_004316aa:
        cmp esi,19h
    L_004316ad:
        jle short L_00431681
    L_004316af:
        push 46E650h
    L_004316b4:
        call asm_FUN_00452abc_00452abc
    L_004316b9:
        push 46E650h
    L_004316be:
        call asm_FUN_00453111_00453111
    L_004316c3:
        add esp,8
    L_004316c6:
        lea edx,[esp+14h]
    L_004316ca:
        push edx
    L_004316cb:
        push 46EFECh
    L_004316d0:
        call dword ptr [data_004660a0]
    L_004316d6:
        mov edi,eax
    L_004316d8:
        cmp edi,0FFFFFFFFh
    L_004316db:
        TH10_REL8(0x74, 0x004316db, VA_asm_target_00431731)
    L_004316dd:
        mov ebx,19h
    L_004316e2:
        lea esi,[ebp+5A48h]
    L_004316e8:
        TH10_REL8(0xeb, 0x004316e8, VA_asm_FUN_004315c0_part_004316f0)
    }
}

// 0x004316F0..0x004318A5: FUN_004315c0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004315c0_part_004316f0() {
    __asm {
    L_004316f0:
        push 46EFE8h
    L_004316f5:
        call asm_FUN_00453111_00453111
    L_004316fa:
        add esp,4
    L_004316fd:
        lea eax,[esp+40h]
    L_00431701:
        push eax
    L_00431702:
        call asm_StageManager_CreateRetail_004296f0
    L_00431707:
        push 46E650h
    L_0043170c:
        mov dword ptr [esi],eax
    L_0043170e:
        call asm_FUN_00453111_00453111
    L_00431713:
        add esp,4
    L_00431716:
        lea ecx,[esp+14h]
    L_0043171a:
        push ecx
    L_0043171b:
        push edi
    L_0043171c:
        call dword ptr [data_004660a4]
    L_00431722:
        test eax,eax
    L_00431724:
        je short L_0043172f
    L_00431726:
        inc ebx
    L_00431727:
        add esi,4
    L_0043172a:
        cmp ebx,32h
    L_0043172d:
        jl short L_004316f0
    L_0043172f:
        xor ebx,ebx
    L_00431731:
        push edi
    L_00431732:
        call dword ptr [data_004660a8]
    L_00431738:
        push 46EFE8h
    L_0043173d:
        call asm_FUN_00453111_00453111
    L_00431742:
        add esp,4
    L_00431745:
        mov dword ptr [ebp+59D8h],ebx
    L_0043174b:
        jmp short L_0043174f
    L_0043174d:
        xor ebx,ebx
    L_0043174f:
        cmp dword ptr [ebp+2B4h],6
    L_00431756:
        jle asm_target_00431b5a
    L_0043175c:
        mov dword ptr [ebp+20h],2
    L_00431763:
        mov eax,dword ptr [ebp+2C0h]
    L_00431769:
        test al,1
    L_0043176b:
        jne short L_00431796
    L_0043176d:
        or eax,1
    L_00431770:
        mov dword ptr [ebp+2B4h],ebx
    L_00431776:
        mov dword ptr [ebp+2B0h],0FFF0BDC1h
    L_00431780:
        mov dword ptr [ebp+2B8h],ebx
    L_00431786:
        mov dword ptr [ebp+2BCh],476F78h
    L_00431790:
        mov dword ptr [ebp+2C0h],eax
    L_00431796:
        mov dword ptr [ebp+2B4h],ebx
    L_0043179c:
        mov dword ptr [ebp+2B8h],ebx
    L_004317a2:
        mov dword ptr [ebp+2B0h],0FFFFFFFFh
    L_004317ac:
        jmp asm_target_00431b5a
    L_004317b1:
        mov edx,dword ptr [ebp+24h]
    L_004317b4:
        lea esi,[ebp+24h]
    L_004317b7:
        mov dword ptr [esi+4],edx
    L_004317ba:
        mov cl,byte ptr [data_00474e36]
    L_004317c0:
        mov al,10h
    L_004317c2:
        test cl,al
    L_004317c4:
        jne short L_004317ce
    L_004317c6:
        test byte ptr [data_00474e34],al
    L_004317cc:
        je short L_004317d7
    L_004317ce:
        push 0FFFFFFFFh
    L_004317d0:
        mov eax,esi
    L_004317d2:
        call asm_MenuCursor_Advance_0044bea0
    L_004317d7:
        mov cl,byte ptr [data_00474e36]
    L_004317dd:
        mov al,20h
    L_004317df:
        test cl,al
    L_004317e1:
        jne short L_004317eb
    L_004317e3:
        test byte ptr [data_00474e34],al
    L_004317e9:
        je short L_004317f4
    L_004317eb:
        push 1
    L_004317ed:
        mov eax,esi
    L_004317ef:
        call asm_MenuCursor_Advance_0044bea0
    L_004317f4:
        mov eax,dword ptr [esi+4]
    L_004317f7:
        cmp eax,dword ptr [esi]
    L_004317f9:
        je short L_0043180c
    L_004317fb:
        push 0
    L_004317fd:
        mov edi,0Ch
    L_00431802:
        mov ecx,492590h
    L_00431807:
        call asm_AnimationManager_QueueResource_0043dc90
    L_0043180c:
        mov eax,dword ptr [data_00474e36]
    L_00431811:
        test al,0Ah
    L_00431813:
        je short L_00431837
    L_00431815:
        mov ecx,5
    L_0043181a:
        mov eax,ebp
    L_0043181c:
        call asm_GameState_SetTimerTarget_0042c620
    L_00431821:
        push 0
    L_00431823:
        mov edi,0Bh
    L_00431828:
        mov ecx,492590h
    L_0043182d:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00431832:
        jmp asm_target_00431b5a
    L_00431837:
        test eax,1001h
    L_0043183c:
        je asm_target_00431b5a
    L_00431842:
        mov ecx,dword ptr [esi]
    L_00431844:
        mov eax,dword ptr [ebp+ecx*4+59E4h]
    L_0043184b:
        test eax,eax
    L_0043184d:
        je asm_target_00431b5a
    L_00431853:
        mov ecx,4
    L_00431858:
        mov eax,ebp
    L_0043185a:
        call asm_GameState_SetTimerTarget_0042c620
    L_0043185f:
        mov edx,dword ptr [esi]
    L_00431861:
        mov eax,esi
    L_00431863:
        mov dword ptr [ebp+59DCh],edx
    L_00431869:
        call asm_Score_InputHistorySave_0044be20
    L_0043186e:
        push 0
    L_00431870:
        mov edi,0Ah
    L_00431875:
        mov ecx,492590h
    L_0043187a:
        call asm_AnimationManager_QueueResource_0043dc90
    L_0043187f:
        mov dword ptr [ebp+2Ch],7
    L_00431886:
        mov eax,dword ptr [esi+8]
    L_00431889:
        test eax,eax
    L_0043188b:
        je short L_0043189a
    L_0043188d:
        jg short L_00431894
    L_0043188f:
        dec eax
    L_00431890:
        mov dword ptr [esi],eax
    L_00431892:
        jmp short L_004318a0
    L_00431894:
        xor eax,eax
    L_00431896:
        mov dword ptr [esi],eax
    L_00431898:
        jmp short L_004318a0
    L_0043189a:
        mov dword ptr [esi],0
    L_004318a0:
        xor ecx,ecx
    L_004318a2:
        xor eax,eax
    L_004318a4:
        TH10_REL8(0xeb, 0x004318a4, VA_asm_FUN_004315c0_part_004318b0)
    }
}

// 0x004318B0..0x00431B79: FUN_004315c0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004315c0_part_004318b0() {
    __asm {
    L_004318b0:
        mov edx,dword ptr [ebp+59DCh]
    L_004318b6:
        mov edx,dword ptr [ebp+edx*4+59E4h]
    L_004318bd:
        mov edi,dword ptr [edx+eax+0D4h]
    L_004318c4:
        test edi,edi
    L_004318c6:
        jne short L_004318db
    L_004318c8:
        mov edx,dword ptr [esi+0D4h]
    L_004318ce:
        mov dword ptr [esi+edx*4+90h],ecx
    L_004318d5:
        inc dword ptr [esi+0D4h]
    L_004318db:
        add eax,24h
    L_004318de:
        inc ecx
    L_004318df:
        cmp eax,0FCh
    L_004318e4:
        jl short L_004318b0
    L_004318e6:
        push 0FFFFFFFFh
    L_004318e8:
        mov eax,esi
    L_004318ea:
        call asm_MenuCursor_Advance_0044bea0
    L_004318ef:
        push 1
    L_004318f1:
        mov eax,esi
    L_004318f3:
        call asm_MenuCursor_Advance_0044bea0
    L_004318f8:
        jmp asm_target_00431b5a
    L_004318fd:
        cmp dword ptr [ebp+2B4h],0Fh
    L_00431904:
        jl asm_target_00431b5a
    L_0043190a:
        mov eax,dword ptr [ebp+24h]
    L_0043190d:
        lea esi,[ebp+24h]
    L_00431910:
        mov dword ptr [esi+4],eax
    L_00431913:
        mov eax,10h
    L_00431918:
        mov ecx,474E30h
    L_0043191d:
        call asm_InputMaskActive_0040ace0
    L_00431922:
        test ax,ax
    L_00431925:
        je short L_00431930
    L_00431927:
        push 0FFFFFFFFh
    L_00431929:
        mov eax,esi
    L_0043192b:
        call asm_MenuCursor_Advance_0044bea0
    L_00431930:
        mov eax,20h
    L_00431935:
        mov ecx,474E30h
    L_0043193a:
        call asm_InputMaskActive_0040ace0
    L_0043193f:
        test ax,ax
    L_00431942:
        je short L_0043194d
    L_00431944:
        push 1
    L_00431946:
        mov eax,esi
    L_00431948:
        call asm_MenuCursor_Advance_0044bea0
    L_0043194d:
        mov ecx,dword ptr [esi+4]
    L_00431950:
        cmp ecx,dword ptr [esi]
    L_00431952:
        je short L_00431965
    L_00431954:
        push 0
    L_00431956:
        mov edi,0Ch
    L_0043195b:
        mov ecx,492590h
    L_00431960:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00431965:
        mov eax,dword ptr [data_00474e36]
    L_0043196a:
        test al,0Ah
    L_0043196c:
        je short L_00431990
    L_0043196e:
        mov eax,esi
    L_00431970:
        call asm_Score_InputHistoryStep_0044be70
    L_00431975:
        mov dword ptr [ebp+2Ch],19h
    L_0043197c:
        mov dword ptr [ebp+0F8h],0
    L_00431986:
        mov ecx,2
    L_0043198b:
        jmp asm_target_0043181a
    L_00431990:
        test eax,1001h
    L_00431995:
        je asm_target_00431b5a
    L_0043199b:
        mov edx,dword ptr [esi]
    L_0043199d:
        mov ecx,3
    L_004319a2:
        mov eax,ebp
    L_004319a4:
        mov dword ptr [ebp+59E0h],edx
    L_004319aa:
        call asm_GameState_SetTimerTarget_0042c620
    L_004319af:
        jmp asm_target_00431b5a
    L_004319b4:
        mov eax,dword ptr [ebp+2B4h]
    L_004319ba:
        mov edi,2
    L_004319bf:
        cmp eax,edi
    L_004319c1:
        jne short L_004319ec
    L_004319c3:
        push 0
    L_004319c5:
        push 0
    L_004319c7:
        push 0
    L_004319c9:
        push 20h
    L_004319cb:
        push 5
    L_004319cd:
        mov ebx,2Bh
    L_004319d2:
        call asm_AsciiManager_CreateRetail_0043c8b0
    L_004319d7:
        mov esi,dword ptr [data_004776e0]
    L_004319dd:
        push 43C40000h
    L_004319e2:
        push 43F00000h
    L_004319e7:
        call asm_FUN_0040c540_0040c540
    L_004319ec:
        cmp dword ptr [ebp+2B4h],20h
    L_004319f3:
        jl asm_target_00431b5a
    L_004319f9:
        mov ecx,3
    L_004319fe:
        mov eax,ebp
    L_00431a00:
        call asm_GameState_DisableTimerWithOwner_0042c5c0
    L_00431a05:
        mov eax,dword ptr [ebp+59E0h]
    L_00431a0b:
        inc eax
    L_00431a0c:
        lea ecx,[eax+eax*2]
    L_00431a0f:
        shl ecx,4
    L_00431a12:
        add ecx,474788h
    L_00431a18:
        push 40C00000h
    L_00431a1d:
        mov dword ptr [data_00477848],ecx
    L_00431a23:
        mov dword ptr [data_00474c7c],eax
    L_00431a28:
        mov dword ptr [data_00474c80],eax
    L_00431a2d:
        call asm_Sound_PlayRandomVoiceRetail_00420c30
    L_00431a32:
        mov dword ptr [data_00491fb8],0Ch
    L_00431a3c:
        mov edx,dword ptr [ebp+59DCh]
    L_00431a42:
        mov eax,dword ptr [ebp+edx*4+59E4h]
    L_00431a49:
        add eax,1D4h
    L_00431a4e:
        mov edx,477710h
    L_00431a53:
        mov cl,byte ptr [eax]
    L_00431a55:
        inc eax
    L_00431a56:
        mov byte ptr [edx],cl
    L_00431a58:
        inc edx
    L_00431a59:
        test cl,cl
    L_00431a5b:
        jne short L_00431a53
    L_00431a5d:
        mov eax,dword ptr [ebp+59DCh]
    L_00431a63:
        mov ecx,dword ptr [ebp+eax*4+59E4h]
    L_00431a6a:
        mov eax,dword ptr [ecx+18h]
    L_00431a6d:
        mov edx,dword ptr [eax+50h]
    L_00431a70:
        mov dword ptr [data_00474c68],edx
    L_00431a76:
        mov ecx,dword ptr [eax+54h]
    L_00431a79:
        mov dword ptr [data_00474c6c],ecx
    L_00431a7f:
        mov edx,dword ptr [eax+58h]
    L_00431a82:
        mov dword ptr [data_00474c74],edx
    L_00431a88:
        mov eax,dword ptr [ebp+59DCh]
    L_00431a8e:
        mov dword ptr [data_00491c00],edi
    L_00431a94:
        mov dword ptr [data_00491c04],eax
    L_00431a99:
        jmp asm_target_00431b5a
    L_00431a9e:
        cmp dword ptr [ebp+2B4h],6
    L_00431aa5:
        jl asm_target_00431b5a
    L_00431aab:
        lea ebx,[ebp+59E4h]
    L_00431ab1:
        mov edi,32h
    L_00431ab6:
        mov esi,dword ptr [ebx]
    L_00431ab8:
        test esi,esi
    L_00431aba:
        je short L_00431acb
    L_00431abc:
        push esi
    L_00431abd:
        call asm_FUN_004294a0_004294a0
    L_00431ac2:
        push esi
    L_00431ac3:
        call asm_free_004524a1
    L_00431ac8:
        add esp,4
    L_00431acb:
        add ebx,4
    L_00431ace:
        dec edi
    L_00431acf:
        jne short L_00431ab6
    L_00431ad1:
        xor eax,eax
    L_00431ad3:
        mov ecx,32h
    L_00431ad8:
        lea edi,[ebp+59E4h]
    L_00431ade:
        rep stosd
    L_00431ae0:
        mov esi,65h
    L_00431ae5:
        mov edi,ebp
    L_00431ae7:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_00431aec:
        mov esi,8
    L_00431af1:
        mov ecx,5Ah
    L_00431af6:
        mov eax,ebp
    L_00431af8:
        call asm_FUN_0042c770_0042c770
    L_00431afd:
        mov ecx,5Bh
    L_00431b02:
        mov eax,ebp
    L_00431b04:
        call asm_FUN_0042c770_0042c770
    L_00431b09:
        mov esi,5Eh
    L_00431b0e:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_00431b13:
        lea eax,[ebp+5D0h]
    L_00431b19:
        call asm_FUN_00409e50_00409e50
    L_00431b1e:
        mov ecx,2
    L_00431b23:
        mov eax,ebp
    L_00431b25:
        call asm_GameState_DisableTimerWithOwner_0042c5c0
    L_00431b2a:
        dec dword ptr [ebp+0B0h]
    L_00431b30:
        jns short L_00431b3c
    L_00431b32:
        mov dword ptr [ebp+0B0h],0
    L_00431b3c:
        mov eax,dword ptr [ebp+0B0h]
    L_00431b42:
        mov ecx,dword ptr [ebp+eax*4+30h]
    L_00431b46:
        mov dword ptr [ebp+24h],ecx
    L_00431b49:
        mov edx,dword ptr [ebp+eax*4+70h]
    L_00431b4d:
        mov dword ptr [ebp+2Ch],edx
    L_00431b50:
        mov dword ptr [ebp+0F8h],0
    L_00431b5a:
        pop edi
    L_00431b5b:
        pop esi
    L_00431b5c:
        pop ebx
    L_00431b5d:
        mov ecx,dword ptr [esp+188h]
    L_00431b64:
        pop ebp
    L_00431b65:
        xor ecx,esp
    L_00431b67:
        mov eax,1
    L_00431b6c:
        call asm_security_check_cookie_00458ea5
    L_00431b71:
        add esp,188h
    L_00431b77:
        ret 4
    }
}

// 0x00433570..0x004335EC: FUN_00433570
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00433570_00433570() {
    __asm {
    L_00433570:
        sub esp,44h
    L_00433573:
        mov eax,dword ptr [data_00473660]
    L_00433578:
        xor eax,esp
    L_0043357a:
        push ebp
    L_0043357b:
        mov ebp,dword ptr [esp+4Ch]
    L_0043357f:
        mov dword ptr [esp+44h],eax
    L_00433583:
        mov eax,dword ptr [ebp+20h]
    L_00433586:
        cmp eax,4
    L_00433589:
        ja asm_target_00433af9
    L_0043358f:
        push ebx
    L_00433590:
        push esi
    L_00433591:
        push edi
    L_00433592:
        jmp dword ptr [eax*4+433B10h]
    L_00433599:
        mov dword ptr [ebp+2Ch],19h
    L_004335a0:
        mov dword ptr [ebp+0F4h],1
    L_004335aa:
        mov eax,dword ptr [ebp+2Ch]
    L_004335ad:
        test eax,eax
    L_004335af:
        je short L_004335c0
    L_004335b1:
        jg short L_004335b9
    L_004335b3:
        dec eax
    L_004335b4:
        mov dword ptr [ebp+24h],eax
    L_004335b7:
        jmp short L_004335c7
    L_004335b9:
        xor eax,eax
    L_004335bb:
        mov dword ptr [ebp+24h],eax
    L_004335be:
        jmp short L_004335c7
    L_004335c0:
        mov dword ptr [ebp+24h],0
    L_004335c7:
        mov eax,8
    L_004335cc:
        mov dword ptr [data_00477848],474908h
    L_004335d6:
        mov dword ptr [data_00474c7c],eax
    L_004335db:
        mov dword ptr [data_00474c80],eax
    L_004335e0:
        mov esi,1
    L_004335e5:
        lea edi,[ebp+59E4h]
    L_004335eb:
        TH10_REL8(0xeb, 0x004335eb, VA_asm_FUN_00433570_part_004335f0)
    }
}

// 0x004335F0..0x00433B0F: FUN_00433570
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00433570_part_004335f0() {
    __asm {
    L_004335f0:
        push esi
    L_004335f1:
        lea eax,[esp+14h]
    L_004335f5:
        push 46E0C8h
    L_004335fa:
        push eax
    L_004335fb:
        call asm_sprintf_00452ae8
    L_00433600:
        add esp,0Ch
    L_00433603:
        lea ecx,[esp+10h]
    L_00433607:
        push ecx
    L_00433608:
        call asm_StageManager_CreateRetail_004296f0
    L_0043360d:
        mov dword ptr [edi],eax
    L_0043360f:
        inc esi
    L_00433610:
        add edi,4
    L_00433613:
        cmp esi,19h
    L_00433616:
        jle short L_004335f0
    L_00433618:
        push ebp
    L_00433619:
        mov edi,69h
    L_0043361e:
        call asm_Recovery_InstallAnimationSlot_0042c670
    L_00433623:
        mov ecx,1
    L_00433628:
        mov eax,ebp
    L_0043362a:
        call asm_GameState_SetTimerTarget_0042c620
    L_0043362f:
        cmp dword ptr [ebp+2B4h],6
    L_00433636:
        jle asm_target_00433af6
    L_0043363c:
        mov ecx,2
    L_00433641:
        mov eax,ebp
    L_00433643:
        call asm_GameState_SetTimerTarget_0042c620
    L_00433648:
        jmp asm_target_00433af6
    L_0043364d:
        mov edx,dword ptr [ebp+24h]
    L_00433650:
        lea esi,[ebp+24h]
    L_00433653:
        mov dword ptr [esi+4],edx
    L_00433656:
        mov cl,byte ptr [data_00474e36]
    L_0043365c:
        mov al,10h
    L_0043365e:
        test cl,al
    L_00433660:
        jne short L_0043366a
    L_00433662:
        test byte ptr [data_00474e34],al
    L_00433668:
        je short L_00433673
    L_0043366a:
        push 0FFFFFFFFh
    L_0043366c:
        mov eax,esi
    L_0043366e:
        call asm_MenuCursor_Advance_0044bea0
    L_00433673:
        test byte ptr [data_00474e36],20h
    L_0043367a:
        jne short L_00433685
    L_0043367c:
        test byte ptr [data_00474e34],20h
    L_00433683:
        je short L_0043368e
    L_00433685:
        push 1
    L_00433687:
        mov eax,esi
    L_00433689:
        call asm_MenuCursor_Advance_0044bea0
    L_0043368e:
        mov eax,dword ptr [esi+4]
    L_00433691:
        cmp eax,dword ptr [esi]
    L_00433693:
        je short L_004336a6
    L_00433695:
        push 0
    L_00433697:
        mov edi,0Ch
    L_0043369c:
        mov ecx,492590h
    L_004336a1:
        call asm_AnimationManager_QueueResource_0043dc90
    L_004336a6:
        mov eax,dword ptr [data_00474e36]
    L_004336ab:
        test al,0Ah
    L_004336ad:
        je short L_004336d1
    L_004336af:
        mov ecx,4
    L_004336b4:
        mov eax,ebp
    L_004336b6:
        call asm_GameState_SetTimerTarget_0042c620
    L_004336bb:
        push 0
    L_004336bd:
        mov edi,0Bh
    L_004336c2:
        mov ecx,492590h
    L_004336c7:
        call asm_AnimationManager_QueueResource_0043dc90
    L_004336cc:
        jmp asm_target_00433af6
    L_004336d1:
        test eax,1001h
    L_004336d6:
        je asm_target_00433af6
    L_004336dc:
        mov ecx,dword ptr [esi]
    L_004336de:
        lea ebx,[ebp+58F4h]
    L_004336e4:
        mov dword ptr [ebp+59DCh],ecx
    L_004336ea:
        mov eax,dword ptr [ebx+8]
    L_004336ed:
        test eax,eax
    L_004336ef:
        je short L_004336fe
    L_004336f1:
        jg short L_004336f8
    L_004336f3:
        dec eax
    L_004336f4:
        mov dword ptr [ebx],eax
    L_004336f6:
        jmp short L_00433704
    L_004336f8:
        xor eax,eax
    L_004336fa:
        mov dword ptr [ebx],eax
    L_004336fc:
        jmp short L_00433704
    L_004336fe:
        mov dword ptr [ebx],0
    L_00433704:
        mov eax,dword ptr [data_004746d8]
    L_00433709:
        lea edx,[eax+1]
    L_0043370c:
        TH10_NOP_LEA_ESP_DISP8()
    L_00433710:
        mov cl,byte ptr [eax]
    L_00433712:
        inc eax
    L_00433713:
        test cl,cl
    L_00433715:
        jne short L_00433710
    L_00433717:
        mov esi,dword ptr [data_00477838]
    L_0043371d:
        sub eax,edx
    L_0043371f:
        mov dword ptr [ebp+58FCh],eax
    L_00433725:
        mov dword ptr [ebp+59C4h],1
    L_0043372f:
        mov edx,dword ptr [esi+18h]
    L_00433732:
        add esi,18h
    L_00433735:
        add edx,0Ch
    L_00433738:
        push edx
    L_00433739:
        call asm_FID_conflict___time32_00452b71
    L_0043373e:
        mov eax,dword ptr [esi]
    L_00433740:
        mov dword ptr [eax+5Ch],8
    L_00433747:
        mov eax,dword ptr [data_0047783c]
    L_0043374c:
        lea esi,[ebp+58DCh]
    L_00433752:
        add eax,1D878h
    L_00433757:
        mov ecx,esi
    L_00433759:
        add esp,4
    L_0043375c:
        sub ecx,eax
    L_0043375e:
        mov edi,edi
    L_00433760:
        mov dl,byte ptr [eax]
    L_00433762:
        mov byte ptr [eax+ecx],dl
    L_00433765:
        inc eax
    L_00433766:
        test dl,dl
    L_00433768:
        jne short L_00433760
    L_0043376a:
        mov edi,46E354h
    L_0043376f:
        mov ecx,9
    L_00433774:
        xor edx,edx
    L_00433776:
        mov dword ptr [ebp+58E8h],0
    L_00433780:
        repe cmpsb
    L_00433782:
        je short L_0043378d
    L_00433784:
        push 0FFFFFFFFh
    L_00433786:
        mov eax,ebx
    L_00433788:
        call asm_MenuCursor_Advance_0044bea0
    L_0043378d:
        mov eax,8
    L_00433792:
        cmp byte ptr [eax+ebp+58DBh],20h
    L_0043379a:
        jne short L_004337a1
    L_0043379c:
        dec eax
    L_0043379d:
        test eax,eax
    L_0043379f:
        jg short L_00433792
    L_004337a1:
        push 0
    L_004337a3:
        mov edi,0Ah
    L_004337a8:
        mov ecx,492590h
    L_004337ad:
        mov dword ptr [ebp+58E8h],eax
    L_004337b3:
        call asm_AnimationManager_QueueResource_0043dc90
    L_004337b8:
        mov ecx,3
    L_004337bd:
        mov eax,ebp
    L_004337bf:
        call asm_GameState_SetTimerTarget_0042c620
    L_004337c4:
        jmp asm_target_00433af6
    L_004337c9:
        mov eax,dword ptr [ebp+58F4h]
    L_004337cf:
        lea esi,[ebp+58F4h]
    L_004337d5:
        mov dword ptr [esi+4],eax
    L_004337d8:
        mov cl,byte ptr [data_00474e36]
    L_004337de:
        mov al,10h
    L_004337e0:
        test cl,al
    L_004337e2:
        jne short L_004337ec
    L_004337e4:
        test byte ptr [data_00474e34],al
    L_004337ea:
        je short L_004337f5
    L_004337ec:
        push 0FFFFFFF3h
    L_004337ee:
        mov eax,esi
    L_004337f0:
        call asm_MenuCursor_Advance_0044bea0
    L_004337f5:
        test byte ptr [data_00474e36],20h
    L_004337fc:
        jne short L_00433807
    L_004337fe:
        test byte ptr [data_00474e34],20h
    L_00433805:
        je short L_00433810
    L_00433807:
        push 0Dh
    L_00433809:
        mov eax,esi
    L_0043380b:
        call asm_MenuCursor_Advance_0044bea0
    L_00433810:
        mov cl,byte ptr [data_00474e36]
    L_00433816:
        mov al,40h
    L_00433818:
        test cl,al
    L_0043381a:
        jne short L_00433824
    L_0043381c:
        test byte ptr [data_00474e34],al
    L_00433822:
        je short L_0043383f
    L_00433824:
        mov eax,dword ptr [esi]
    L_00433826:
        cdq
    L_00433827:
        mov ecx,0Dh
    L_0043382c:
        idiv ecx
    L_0043382e:
        mov eax,esi
    L_00433830:
        test edx,edx
    L_00433832:
        je short L_00433838
    L_00433834:
        push 0FFFFFFFFh
    L_00433836:
        jmp short L_0043383a
    L_00433838:
        push 0Ch
    L_0043383a:
        call asm_MenuCursor_Advance_0044bea0
    L_0043383f:
        mov cl,byte ptr [data_00474e36]
    L_00433845:
        mov al,80h
    L_00433847:
        test cl,al
    L_00433849:
        jne short L_00433853
    L_0043384b:
        test byte ptr [data_00474e34],al
    L_00433851:
        je short L_0043386f
    L_00433853:
        mov eax,dword ptr [esi]
    L_00433855:
        cdq
    L_00433856:
        mov ecx,0Dh
    L_0043385b:
        idiv ecx
    L_0043385d:
        mov eax,esi
    L_0043385f:
        cmp edx,0Ch
    L_00433862:
        je short L_00433868
    L_00433864:
        push 1
    L_00433866:
        jmp short L_0043386a
    L_00433868:
        push 0FFFFFFF4h
    L_0043386a:
        call asm_MenuCursor_Advance_0044bea0
    L_0043386f:
        mov edx,dword ptr [esi+4]
    L_00433872:
        cmp edx,dword ptr [esi]
    L_00433874:
        je short L_00433887
    L_00433876:
        push 0
    L_00433878:
        mov edi,0Ch
    L_0043387d:
        mov ecx,492590h
    L_00433882:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00433887:
        test dword ptr [data_00474e36],1001h
    L_00433891:
        je asm_target_004339ed
    L_00433897:
        mov edi,dword ptr [data_004746d8]
    L_0043389d:
        mov eax,edi
    L_0043389f:
        lea edx,[eax+1]
    L_004338a2:
        mov cl,byte ptr [eax]
    L_004338a4:
        inc eax
    L_004338a5:
        test cl,cl
    L_004338a7:
        jne short L_004338a2
    L_004338a9:
        mov ecx,dword ptr [esi]
    L_004338ab:
        sub eax,edx
    L_004338ad:
        lea edx,[eax-3]
    L_004338b0:
        cmp ecx,edx
    L_004338b2:
        jge short L_004338da
    L_004338b4:
        mov edx,dword ptr [ebp+58E8h]
    L_004338ba:
        cmp edx,8
    L_004338bd:
        jge short L_004338cb
    L_004338bf:
        mov cl,byte ptr [ecx+edi]
    L_004338c2:
        mov byte ptr [edx+ebp+58DCh],cl
    L_004338c9:
        jmp short L_004338ef
    L_004338cb:
        mov al,byte ptr [ecx+edi]
    L_004338ce:
        mov byte ptr [edx+ebp+58DBh],al
    L_004338d5:
        jmp asm_target_004339dc
    L_004338da:
        jne short L_00433923
    L_004338dc:
        mov ecx,dword ptr [ebp+58E8h]
    L_004338e2:
        cmp ecx,8
    L_004338e5:
        jge short L_00433916
    L_004338e7:
        mov byte ptr [ecx+ebp+58DCh],20h
    L_004338ef:
        mov edx,dword ptr [ebp+58E8h]
    L_004338f5:
        inc edx
    L_004338f6:
        mov ecx,edx
    L_004338f8:
        cmp ecx,8
    L_004338fb:
        mov dword ptr [ebp+58E8h],edx
    L_00433901:
        jl asm_target_004339dc
    L_00433907:
        lea ecx,[eax-1]
    L_0043390a:
        mov edx,esi
    L_0043390c:
        call asm_FUN_0040ad20_0040ad20
    L_00433911:
        jmp asm_target_004339dc
    L_00433916:
        mov byte ptr [ecx+ebp+58DBh],20h
    L_0043391e:
        jmp asm_target_004339dc
    L_00433923:
        lea edx,[eax-2]
    L_00433926:
        cmp ecx,edx
    L_00433928:
        jne short L_0043394c
    L_0043392a:
        mov eax,dword ptr [ebp+58E8h]
    L_00433930:
        test eax,eax
    L_00433932:
        je asm_target_00433af6
    L_00433938:
        dec eax
    L_00433939:
        mov dword ptr [ebp+58E8h],eax
    L_0043393f:
        mov byte ptr [eax+ebp+58DCh],20h
    L_00433947:
        jmp asm_target_004339dc
    L_0043394c:
        dec eax
    L_0043394d:
        cmp ecx,eax
    L_0043394f:
        jne asm_target_004339dc
    L_00433955:
        push 0
    L_00433957:
        mov edi,2Ch
    L_0043395c:
        mov ecx,492590h
    L_00433961:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00433966:
        mov eax,dword ptr [ebp+24h]
    L_00433969:
        inc eax
    L_0043396a:
        push eax
    L_0043396b:
        lea ecx,[esp+14h]
    L_0043396f:
        push 46E0C8h
    L_00433974:
        push ecx
    L_00433975:
        call asm_sprintf_00452ae8
    L_0043397a:
        mov edx,dword ptr [ebp+24h]
    L_0043397d:
        mov esi,dword ptr [ebp+edx*4+59E4h]
    L_00433984:
        add esp,0Ch
    L_00433987:
        call asm_Platform_DeletingDestructorWithRelease_004297b0
    L_0043398c:
        mov ecx,dword ptr [data_00477838]
    L_00433992:
        lea esi,[ebp+58DCh]
    L_00433998:
        push esi
    L_00433999:
        lea edx,[esp+14h]
    L_0043399d:
        call asm_FUN_00429b60_00429b60
    L_004339a2:
        mov edi,dword ptr [ebp+24h]
    L_004339a5:
        lea eax,[esp+10h]
    L_004339a9:
        push eax
    L_004339aa:
        call asm_StageManager_CreateRetail_004296f0
    L_004339af:
        mov edx,dword ptr [data_0047783c]
    L_004339b5:
        add edx,1D878h
    L_004339bb:
        mov dword ptr [ebp+edi*4+59E4h],eax
    L_004339c2:
        mov eax,esi
    L_004339c4:
        sub edx,esi
    L_004339c6:
        mov cl,byte ptr [eax]
    L_004339c8:
        mov byte ptr [eax+edx],cl
    L_004339cb:
        inc eax
    L_004339cc:
        test cl,cl
    L_004339ce:
        jne short L_004339c6
    L_004339d0:
        mov ecx,2
    L_004339d5:
        mov eax,ebp
    L_004339d7:
        call asm_GameState_SetTimerTarget_0042c620
    L_004339dc:
        push 0
    L_004339de:
        mov edi,0Ah
    L_004339e3:
        mov ecx,492590h
    L_004339e8:
        call asm_AnimationManager_QueueResource_0043dc90
    L_004339ed:
        test byte ptr [data_00474e36],0Ah
    L_004339f4:
        je asm_target_00433af6
    L_004339fa:
        mov eax,dword ptr [ebp+58E8h]
    L_00433a00:
        test eax,eax
    L_00433a02:
        je asm_target_0043363c
    L_00433a08:
        push 0
    L_00433a0a:
        mov edi,0Bh
    L_00433a0f:
        mov ecx,492590h
    L_00433a14:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00433a19:
        mov eax,dword ptr [ebp+58E8h]
    L_00433a1f:
        dec eax
    L_00433a20:
        mov dword ptr [ebp+58E8h],eax
    L_00433a26:
        mov byte ptr [eax+ebp+58DCh],20h
    L_00433a2e:
        jmp asm_target_00433af6
    L_00433a33:
        cmp dword ptr [ebp+2B4h],6
    L_00433a3a:
        jl asm_target_00433af6
    L_00433a40:
        mov esi,69h
    L_00433a45:
        mov edi,ebp
    L_00433a47:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_00433a4c:
        mov esi,8
    L_00433a51:
        mov ecx,5Ah
    L_00433a56:
        mov eax,ebp
    L_00433a58:
        call asm_FUN_0042c770_0042c770
    L_00433a5d:
        mov ecx,5Bh
    L_00433a62:
        mov eax,ebp
    L_00433a64:
        call asm_FUN_0042c770_0042c770
    L_00433a69:
        mov esi,5Eh
    L_00433a6e:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_00433a73:
        lea eax,[ebp+5D0h]
    L_00433a79:
        call asm_FUN_00409e50_00409e50
    L_00433a7e:
        mov ecx,2
    L_00433a83:
        mov eax,ebp
    L_00433a85:
        call asm_GameState_DisableTimerWithOwner_0042c5c0
    L_00433a8a:
        lea eax,[ebp+24h]
    L_00433a8d:
        call asm_Score_InputHistoryStep_0044be70
    L_00433a92:
        mov esi,dword ptr [data_00477838]
    L_00433a98:
        test esi,esi
    L_00433a9a:
        je short L_00433aab
    L_00433a9c:
        push esi
    L_00433a9d:
        call asm_FUN_004294a0_004294a0
    L_00433aa2:
        push esi
    L_00433aa3:
        call asm_free_004524a1
    L_00433aa8:
        add esp,4
    L_00433aab:
        push 46F018h
    L_00433ab0:
        push 0
    L_00433ab2:
        call asm_Recovery_ReplaceExtensionWav_00420a90
    L_00433ab7:
        push 0
    L_00433ab9:
        push 0
    L_00433abb:
        call asm_Sound_PlayDummyRetail_00420b10
    L_00433ac0:
        lea ebx,[ebp+59E4h]
    L_00433ac6:
        mov esi,ebx
    L_00433ac8:
        mov edi,19h
    L_00433acd:
        TH10_NOP_LEA_ECX_DISP8()
    L_00433ad0:
        mov ebp,dword ptr [esi]
    L_00433ad2:
        test ebp,ebp
    L_00433ad4:
        je short L_00433ae5
    L_00433ad6:
        push ebp
    L_00433ad7:
        call asm_FUN_004294a0_004294a0
    L_00433adc:
        push ebp
    L_00433add:
        call asm_free_004524a1
    L_00433ae2:
        add esp,4
    L_00433ae5:
        add esi,4
    L_00433ae8:
        dec edi
    L_00433ae9:
        jne short L_00433ad0
    L_00433aeb:
        mov ecx,32h
    L_00433af0:
        xor eax,eax
    L_00433af2:
        mov edi,ebx
    L_00433af4:
        rep stosd
    L_00433af6:
        pop edi
    L_00433af7:
        pop esi
    L_00433af8:
        pop ebx
    L_00433af9:
        mov ecx,dword ptr [esp+44h]
    L_00433afd:
        pop ebp
    L_00433afe:
        xor ecx,esp
    L_00433b00:
        mov eax,1
    L_00433b05:
        call asm_security_check_cookie_00458ea5
    L_00433b0a:
        add esp,44h
    L_00433b0d:
        ret 4
    }
}
