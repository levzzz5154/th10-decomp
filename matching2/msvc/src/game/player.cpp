#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00404530..0x004045A6: FUN_00404530
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00404530_00404530() {
    __asm {
    L_00404530:
        push ebx
    L_00404531:
        push 0
    L_00404533:
        push 0
    L_00404535:
        push 0
    L_00404537:
        push 1Eh
    L_00404539:
        push 2
    L_0040453b:
        mov ebx,0Fh
    L_00404540:
        call asm_AsciiManager_CreateRetail_0043c8b0
    L_00404545:
        mov eax,dword ptr [esi+2A2Ch]
    L_0040454b:
        test al,1
    L_0040454d:
        pop ebx
    L_0040454e:
        jne short L_00404581
    L_00404550:
        or eax,1
    L_00404553:
        mov dword ptr [esi+2A20h],0
    L_0040455d:
        mov dword ptr [esi+2A1Ch],0FFF0BDC1h
    L_00404567:
        mov dword ptr [esi+2A24h],0
    L_00404571:
        mov dword ptr [esi+2A28h],476F78h
    L_0040457b:
        mov dword ptr [esi+2A2Ch],eax
    L_00404581:
        mov dword ptr [esi+2A20h],1Eh
    L_0040458b:
        mov dword ptr [esi+2A24h],41F00000h
    L_00404595:
        mov dword ptr [esi+2A1Ch],1Dh
    L_0040459f:
        or dword ptr [esi+2A18h],2
    L_004045a6:
        ret
    }
}
// 0x00405500..0x00405550: Player_ClearExpiredFlagsRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Player_ClearExpiredFlagsRetail_00405500() {
    __asm {
    L_00405500:
        cmp dword ptr [eax+3738h],3Ch
    L_00405507:
        jl short L_00405550
    L_00405509:
        mov edx,dword ptr [eax+378Ch]
    L_0040550f:
        mov dword ptr [eax+3790h],0
    L_00405519:
        mov ecx,0FFFFFFFDh
    L_0040551e:
        and edx,ecx
    L_00405520:
        mov dword ptr [eax+378Ch],edx
    L_00405526:
        and dword ptr [eax+0AD4h],ecx
    L_0040552c:
        and dword ptr [eax+0E80h],ecx
    L_00405532:
        and dword ptr [eax+15D8h],ecx
    L_00405538:
        and dword ptr [eax+1984h],ecx
    L_0040553e:
        and dword ptr [eax+1D30h],ecx
    L_00405544:
        and dword ptr [eax+20DCh],ecx
    L_0040554a:
        and dword ptr [eax+2488h],ecx
    L_00405550:
        ret
    }
}

// 0x004055C0..0x00405613: ?Recovery_InstallPairSetFlags@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_InstallPairSetFlags_004055c0() {
    __asm {
    L_004055c0:
        push esi
    L_004055c1:
        push edi
    L_004055c2:
        push 405840h
    L_004055c7:
        call asm_SchedulerCallback_Create_00449ed0
    L_004055cc:
        mov esi,eax
    L_004055ce:
        or dword ptr [esi+4],2
    L_004055d2:
        mov eax,dword ptr [data_00491be4]
    L_004055d7:
        push eax
    L_004055d8:
        mov edi,11h
    L_004055dd:
        mov dword ptr [esi+20h],ebx
    L_004055e0:
        call asm_Scheduler_RegisterPrimary_00449ae0
    L_004055e5:
        push 405850h
    L_004055ea:
        mov dword ptr [ebx+8],esi
    L_004055ed:
        call asm_SchedulerCallback_Create_00449ed0
    L_004055f2:
        mov esi,eax
    L_004055f4:
        or dword ptr [esi+4],2
    L_004055f8:
        mov ecx,dword ptr [data_00491be4]
    L_004055fe:
        push ecx
    L_004055ff:
        mov edi,22h
    L_00405604:
        mov dword ptr [esi+20h],ebx
    L_00405607:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_0040560c:
        pop edi
    L_0040560d:
        mov dword ptr [ebx+0Ch],esi
    L_00405610:
        xor eax,eax
    L_00405612:
        pop esi
    L_00405613:
        ret
    }
}

// 0x00405620..0x004056A8: Recovery_ReleaseRawPairAndReset
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_ReleaseRawPairAndReset_00405620() {
    __asm {
    L_00405620:
        mov eax,dword ptr [esp+4]
    L_00405624:
        push ebx
    L_00405625:
        mov ebx,dword ptr [data_004660b0]
    L_0040562b:
        push ebp
    L_0040562c:
        mov ebp,dword ptr [data_004660b4]
    L_00405632:
        push esi
    L_00405633:
        mov esi,dword ptr [eax+8]
    L_00405636:
        test esi,esi
    L_00405638:
        push edi
    L_00405639:
        mov edi,dword ptr [data_00491be4]
    L_0040563f:
        je short L_00405664
    L_00405641:
        push 492274h
    L_00405646:
        call ebx
    L_00405648:
        inc byte ptr [data_0049231c]
    L_0040564e:
        mov ecx,esi
    L_00405650:
        mov edx,edi
    L_00405652:
        call asm_Scheduler_Remove_00449f60
    L_00405657:
        push 492274h
    L_0040565c:
        call ebp
    L_0040565e:
        dec byte ptr [data_0049231c]
    L_00405664:
        mov ecx,dword ptr [esp+14h]
    L_00405668:
        mov esi,dword ptr [ecx+0Ch]
    L_0040566b:
        test esi,esi
    L_0040566d:
        mov edi,dword ptr [data_00491be4]
    L_00405673:
        je short L_00405698
    L_00405675:
        push 492274h
    L_0040567a:
        call ebx
    L_0040567c:
        inc byte ptr [data_0049231c]
    L_00405682:
        mov ecx,esi
    L_00405684:
        mov edx,edi
    L_00405686:
        call asm_Scheduler_Remove_00449f60
    L_0040568b:
        push 492274h
    L_00405690:
        call ebp
    L_00405692:
        dec byte ptr [data_0049231c]
    L_00405698:
        pop edi
    L_00405699:
        pop esi
    L_0040569a:
        pop ebp
    L_0040569b:
        mov dword ptr [data_004776ec],0
    L_004056a5:
        pop ebx
    L_004056a6:
        ret 4
    }
}

// 0x00405750..0x0040582E: UpdatePlayer
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_UpdatePlayer_00405750() {
    __asm {
    L_00405750:
        mov eax,dword ptr [edi+28h]
    L_00405753:
        sub esp,0Ch
    L_00405756:
        push esi
    L_00405757:
        xor esi,esi
    L_00405759:
        cmp eax,esi
    L_0040575b:
        je asm_target_00405825
    L_00405761:
        dec eax
    L_00405762:
        push ebx
    L_00405763:
        push ebp
    L_00405764:
        jne asm_target_0040581b
    L_0040576a:
        mov eax,dword ptr [edi+2Ch]
    L_0040576d:
        mov ebp,dword ptr [data_00491c10]
    L_00405773:
        push eax
    L_00405774:
        mov edx,ebp
    L_00405776:
        call asm_AnimationManager_Find_004491c0
    L_0040577b:
        mov ebx,eax
    L_0040577d:
        cmp ebx,esi
    L_0040577f:
        jne short L_00405793
    L_00405781:
        pop ebp
    L_00405782:
        mov dword ptr [edi+2Ch],esi
    L_00405785:
        pop ebx
    L_00405786:
        mov dword ptr [edi+28h],esi
    L_00405789:
        mov eax,1
    L_0040578e:
        pop esi
    L_0040578f:
        add esp,0Ch
    L_00405792:
        ret
    L_00405793:
        mov eax,dword ptr [data_004776f4]
    L_00405798:
        test byte ptr [eax+378Ch],1
    L_0040579f:
        je short L_004057c1
    L_004057a1:
        mov eax,dword ptr [eax+3788h]
    L_004057a7:
        cmp eax,5Dh
    L_004057aa:
        jl short L_004057b1
    L_004057ac:
        cmp eax,60h
    L_004057af:
        jle short L_004057b6
    L_004057b1:
        cmp eax,6Dh
    L_004057b4:
        jne short L_004057c1
    L_004057b6:
        fld dword ptr [edi+34h]
    L_004057b9:
        fsub dword ptr [data_00470b0c]
    L_004057bf:
        jmp short L_004057db
    L_004057c1:
        mov eax,dword ptr [data_00474c68]
    L_004057c6:
        fld dword ptr [edi+34h]
    L_004057c9:
        cmp eax,esi
    L_004057cb:
        jne short L_004057d5
    L_004057cd:
        fsub dword ptr [data_00470afc]
    L_004057d3:
        jmp short L_004057db
    L_004057d5:
        fsub dword ptr [data_00470d34]
    L_004057db:
        mov edx,dword ptr [edi+2Ch]
    L_004057de:
        fstp dword ptr [edi+34h]
    L_004057e1:
        fld dword ptr [edi+30h]
    L_004057e4:
        mov ecx,dword ptr [edi+38h]
    L_004057e7:
        fadd dword ptr [data_00470b4c]
    L_004057ed:
        push edx
    L_004057ee:
        lea esi,[esp+10h]
    L_004057f2:
        mov edx,ebp
    L_004057f4:
        fstp dword ptr [esp+10h]
    L_004057f8:
        mov dword ptr [esp+18h],ecx
    L_004057fc:
        fld dword ptr [edi+34h]
    L_004057ff:
        fadd dword ptr [data_00470b48]
    L_00405805:
        fstp dword ptr [esp+14h]
    L_00405809:
        call asm_AnimationManager_SetPosition_004492f0
    L_0040580e:
        mov eax,dword ptr [ebx+40h]
    L_00405811:
        mov esi,edi
    L_00405813:
        mov dword ptr [edi+3Ch],eax
    L_00405816:
        call asm_Player_Draw_00405ac0
    L_0040581b:
        lea esi,[edi+14h]
    L_0040581e:
        call asm_FrameTimer_Tick_00404ed0
    L_00405823:
        pop ebp
    L_00405824:
        pop ebx
    L_00405825:
        mov eax,1
    L_0040582a:
        pop esi
    L_0040582b:
        add esp,0Ch
    L_0040582e:
        ret
    }
}

// 0x00405860..0x004059EC: InitializePlayer
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_InitializePlayer_00405860() {
    __asm {
    L_00405860:
        push ebp
    L_00405861:
        mov ebp,dword ptr [esp+8]
    L_00405865:
        mov eax,dword ptr [ebp+28h]
    L_00405868:
        xor ecx,ecx
    L_0040586a:
        cmp eax,ecx
    L_0040586c:
        je short L_00405875
    L_0040586e:
        or eax,0FFFFFFFFh
    L_00405871:
        pop ebp
    L_00405872:
        ret 4
    L_00405875:
        mov edx,1
    L_0040587a:
        mov dword ptr [ebp+28h],edx
    L_0040587d:
        mov eax,dword ptr [ebp+24h]
    L_00405880:
        test al,dl
    L_00405882:
        jne short L_0040589d
    L_00405884:
        or eax,edx
    L_00405886:
        mov dword ptr [ebp+18h],ecx
    L_00405889:
        mov dword ptr [ebp+14h],0FFF0BDC1h
    L_00405890:
        mov dword ptr [ebp+1Ch],ecx
    L_00405893:
        mov dword ptr [ebp+20h],476F78h
    L_0040589a:
        mov dword ptr [ebp+24h],eax
    L_0040589d:
        mov eax,dword ptr [data_00477834]
    L_004058a2:
        mov dword ptr [ebp+18h],ecx
    L_004058a5:
        mov dword ptr [ebp+1Ch],ecx
    L_004058a8:
        mov dword ptr [ebp+14h],0FFFFFFFFh
    L_004058af:
        push esi
    L_004058b0:
        add eax,3C0h
    L_004058b5:
        mov dword ptr [ebp+3Ch],42000000h
    L_004058bc:
        mov dword ptr [ebp+40h],40800000h
    L_004058c3:
        mov esi,dword ptr [eax]
    L_004058c5:
        push edi
    L_004058c6:
        lea edi,[ebp+30h]
    L_004058c9:
        mov ecx,edi
    L_004058cb:
        mov dword ptr [ecx],esi
    L_004058cd:
        mov esi,dword ptr [eax+4]
    L_004058d0:
        mov dword ptr [ecx+4],esi
    L_004058d3:
        mov eax,dword ptr [eax+8]
    L_004058d6:
        mov dword ptr [ecx+8],eax
    L_004058d9:
        mov eax,dword ptr [data_004776f4]
    L_004058de:
        test byte ptr [eax+378Ch],dl
    L_004058e4:
        je short L_004058f6
    L_004058e6:
        mov ecx,dword ptr [eax+3788h]
    L_004058ec:
        cmp ecx,5Dh
    L_004058ef:
        jl short L_004058f6
    L_004058f1:
        cmp ecx,60h
    L_004058f4:
        jle short L_00405912
    L_004058f6:
        cmp dword ptr [eax+3788h],6Dh
    L_004058fd:
        je short L_00405912
    L_004058ff:
        mov eax,dword ptr [data_00474c68]
    L_00405904:
        neg eax
    L_00405906:
        sbb eax,eax
    L_00405908:
        and eax,7
    L_0040590b:
        add eax,190h
    L_00405910:
        jmp short L_00405917
    L_00405912:
        mov eax,1B9h
    L_00405917:
        mov edx,dword ptr [data_004776f0]
    L_0040591d:
        push ebx
    L_0040591e:
        push eax
    L_0040591f:
        mov eax,dword ptr [edx+3E0B50h]
    L_00405925:
        lea ecx,[esp+18h]
    L_00405929:
        push ecx
    L_0040592a:
        push eax
    L_0040592b:
        call asm_PlayerAnimation_Create_00448db0
    L_00405930:
        mov edx,dword ptr [edi]
    L_00405932:
        mov ecx,dword ptr [eax]
    L_00405934:
        push edx
    L_00405935:
        mov ebx,26h
    L_0040593a:
        mov esi,492590h
    L_0040593f:
        mov dword ptr [ebp+2Ch],ecx
    L_00405942:
        call asm_FUN_0043dd10_0043dd10
    L_00405947:
        movsx eax,word ptr [data_00474c48]
    L_0040594e:
        cdq
    L_0040594f:
        mov ecx,14h
    L_00405954:
        idiv ecx
    L_00405956:
        mov esi,dword ptr [data_0047770c]
    L_0040595c:
        imul edx,64h
    L_0040595f:
        mov ecx,eax
    L_00405961:
        mov eax,66666667h
    L_00405966:
        imul edx
    L_00405968:
        sar edx,3
    L_0040596b:
        mov eax,edx
    L_0040596d:
        shr eax,1Fh
    L_00405970:
        add eax,edx
    L_00405972:
        push eax
    L_00405973:
        mov edx,ecx
    L_00405975:
        call asm_FUN_004054b0_004054b0
    L_0040597a:
        mov esi,dword ptr [data_004776f4]
    L_00405980:
        mov eax,esi
    L_00405982:
        call asm_Player_ClearExpiredFlagsRetail_00405500
    L_00405987:
        mov eax,dword ptr [data_00474c98]
    L_0040598c:
        sub eax,80h
    L_00405991:
        cmp eax,400h
    L_00405996:
        mov dword ptr [data_00474c98],eax
    L_0040599b:
        pop ebx
    L_0040599c:
        jle short L_004059aa
    L_0040599e:
        mov dword ptr [data_00474c98],400h
    L_004059a8:
        jmp short L_004059bb
    L_004059aa:
        cmp eax,0FFFFFC00h
    L_004059af:
        jge short L_004059bb
    L_004059b1:
        mov dword ptr [data_00474c98],0FFFFFC00h
    L_004059bb:
        mov cl,byte ptr [esi+378Ch]
    L_004059c1:
        mov eax,1
    L_004059c6:
        test cl,al
    L_004059c8:
        je short L_004059de
    L_004059ca:
        cmp dword ptr [esi+3738h],3Ch
    L_004059d1:
        jl short L_004059de
    L_004059d3:
        pop edi
    L_004059d4:
        mov dword ptr [ebp+44h],eax
    L_004059d7:
        pop esi
    L_004059d8:
        xor eax,eax
    L_004059da:
        pop ebp
    L_004059db:
        ret 4
    L_004059de:
        pop edi
    L_004059df:
        pop esi
    L_004059e0:
        mov dword ptr [ebp+44h],0
    L_004059e7:
        xor eax,eax
    L_004059e9:
        pop ebp
    L_004059ea:
        ret 4
    }
}

// 0x004059F0..0x00405AB9: Player_HitTestRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Player_HitTestRetail_004059f0() {
    __asm {
    L_004059f0:
        mov edx,dword ptr [ecx+28h]
    L_004059f3:
        test edx,edx
    L_004059f5:
        jne short L_004059fa
    L_004059f7:
        xor eax,eax
    L_004059f9:
        ret
    L_004059fa:
        fld dword ptr [eax+4]
    L_004059fd:
        xor edx,edx
    L_004059ff:
        fsub dword ptr [ecx+34h]
    L_00405a02:
        fld dword ptr [eax]
    L_00405a04:
        fsub dword ptr [ecx+30h]
    L_00405a07:
        fld dword ptr [ecx+3Ch]
    L_00405a0a:
        fld st(1)
    L_00405a0c:
        fmul st,st(2)
    L_00405a0e:
        fld st(3)
    L_00405a10:
        fmul st,st(4)
    L_00405a12:
        faddp st(1),st
    L_00405a14:
        fld st(1)
    L_00405a16:
        fmul st,st(2)
    L_00405a18:
        fcompp
    L_00405a1a:
        fstp st(0)
    L_00405a1c:
        fnstsw ax
    L_00405a1e:
        fstp st(0)
    L_00405a20:
        test ah,41h
    L_00405a23:
        fstp st(0)
    L_00405a25:
        jne short L_00405a68
    L_00405a27:
        mov eax,dword ptr [ecx+44h]
    L_00405a2a:
        test eax,eax
    L_00405a2c:
        mov eax,dword ptr [data_004776f4]
    L_00405a31:
        mov cl,byte ptr [eax+378Ch]
    L_00405a37:
        jne short L_00405a46
    L_00405a39:
        test cl,1
    L_00405a3c:
        je short L_00405a53
    L_00405a3e:
        mov edx,3
    L_00405a43:
        mov eax,edx
    L_00405a45:
        ret
    L_00405a46:
        test cl,1
    L_00405a49:
        je short L_00405a53
    L_00405a4b:
        mov edx,26h
    L_00405a50:
        mov eax,edx
    L_00405a52:
        ret
    L_00405a53:
        mov eax,dword ptr [data_00477704]
    L_00405a58:
        mov edx,dword ptr [eax+10h]
    L_00405a5b:
        neg edx
    L_00405a5d:
        sbb edx,edx
    L_00405a5f:
        and edx,21h
    L_00405a62:
        add edx,5
    L_00405a65:
        mov eax,edx
    L_00405a67:
        ret
    L_00405a68:
        mov eax,dword ptr [data_004776f4]
    L_00405a6d:
        test byte ptr [eax+378Ch],1
    L_00405a74:
        je short L_00405a8f
    L_00405a76:
        cmp dword ptr [ecx+44h],1
    L_00405a7a:
        jne short L_00405ab7
    L_00405a7c:
        mov edx,dword ptr [data_00474c68]
    L_00405a82:
        neg edx
    L_00405a84:
        sbb edx,edx
    L_00405a86:
        and edx,0FFFFFFFDh
    L_00405a89:
        add edx,1Ah
    L_00405a8c:
        mov eax,edx
    L_00405a8e:
        ret
    L_00405a8f:
        mov eax,dword ptr [data_00477704]
    L_00405a94:
        push esi
    L_00405a95:
        mov esi,dword ptr [eax+10h]
    L_00405a98:
        test esi,esi
    L_00405a9a:
        pop esi
    L_00405a9b:
        je short L_00405ab7
    L_00405a9d:
        mov eax,dword ptr [ecx+44h]
    L_00405aa0:
        test eax,eax
    L_00405aa2:
        jne short L_00405ab7
    L_00405aa4:
        mov eax,dword ptr [data_00474c68]
    L_00405aa9:
        xor edx,edx
    L_00405aab:
        test eax,eax
    L_00405aad:
        sete dl
    L_00405ab0:
        lea edx,[edx*4+10h]
    L_00405ab7:
        mov eax,edx
    L_00405ab9:
        ret
    }
}

// 0x00405AC0..0x00405B3B: Player_Draw
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Player_Draw_00405ac0() {
    __asm {
    L_00405ac0:
        mov eax,dword ptr [esi+28h]
    L_00405ac3:
        test eax,eax
    L_00405ac5:
        je short L_00405b39
    L_00405ac7:
        mov ecx,dword ptr [data_004776f4]
    L_00405acd:
        mov eax,dword ptr [ecx+378Ch]
    L_00405ad3:
        test al,1
    L_00405ad5:
        push ebx
    L_00405ad6:
        je short L_00405ae8
    L_00405ad8:
        mov edx,dword ptr [ecx+3788h]
    L_00405ade:
        cmp edx,5Dh
    L_00405ae1:
        jl short L_00405ae8
    L_00405ae3:
        cmp edx,60h
    L_00405ae6:
        jle short L_00405af1
    L_00405ae8:
        cmp dword ptr [ecx+3788h],6Dh
    L_00405aef:
        jne short L_00405aff
    L_00405af1:
        not eax
    L_00405af3:
        push 0
    L_00405af5:
        and eax,1
    L_00405af8:
        push eax
    L_00405af9:
        mov eax,dword ptr [esi+3Ch]
    L_00405afc:
        push eax
    L_00405afd:
        jmp short L_00405b0b
    L_00405aff:
        mov ecx,dword ptr [esi+3Ch]
    L_00405b02:
        not eax
    L_00405b04:
        push 1
    L_00405b06:
        and eax,1
    L_00405b09:
        push eax
    L_00405b0a:
        push ecx
    L_00405b0b:
        mov eax,dword ptr [data_004776f0]
    L_00405b10:
        lea ebx,[esi+30h]
    L_00405b13:
        call asm_FUN_00408100_00408100
    L_00405b18:
        mov edx,dword ptr [data_004776f4]
    L_00405b1e:
        mov eax,dword ptr [edx+378Ch]
    L_00405b24:
        mov ecx,dword ptr [esi+3Ch]
    L_00405b27:
        not eax
    L_00405b29:
        and eax,1
    L_00405b2c:
        push eax
    L_00405b2d:
        mov eax,dword ptr [data_0047781c]
    L_00405b32:
        push ecx
    L_00405b33:
        call asm_ScoreRecords_CopyVectorAndEvaluate_0041c800
    L_00405b38:
        pop ebx
    L_00405b39:
        xor eax,eax
    L_00405b3b:
        ret
    }
}
