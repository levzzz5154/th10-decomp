#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040A450..0x0040A932: FUN_0040a450
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040a450_0040a450() {
    __asm {
    L_0040a450:
        sub esp,184h
    L_0040a456:
        mov eax,dword ptr [data_00473660]
    L_0040a45b:
        xor eax,esp
    L_0040a45d:
        push ebx
    L_0040a45e:
        push ebp
    L_0040a45f:
        mov ebp,dword ptr [esp+190h]
    L_0040a466:
        mov dword ptr [esp+188h],eax
    L_0040a46d:
        mov eax,dword ptr [ebp+30h]
    L_0040a470:
        sub eax,0
    L_0040a473:
        push esi
    L_0040a474:
        push edi
    L_0040a475:
        je asm_target_0040a7ae
    L_0040a47b:
        dec eax
    L_0040a47c:
        je asm_target_0040a55b
    L_0040a482:
        sub eax,3
    L_0040a485:
        jne asm_target_0040a913
    L_0040a48b:
        mov cx,word ptr [data_00474e30]
    L_0040a492:
        mov ax,word ptr [data_00474e5c]
    L_0040a498:
        mov word ptr [data_00474e5c],cx
    L_0040a49f:
        mov ecx,474E30h
    L_0040a4a4:
        mov word ptr [data_00474e5e],ax
    L_0040a4aa:
        call asm_UpdateInputState_0040ac20
    L_0040a4af:
        mov dx,word ptr [data_00474e36]
    L_0040a4b6:
        mov al,dl
    L_0040a4b8:
        test al,8
    L_0040a4ba:
        mov word ptr [data_00474e62],dx
    L_0040a4c1:
        je asm_target_0040a913
    L_0040a4c7:
        mov esi,dword ptr [data_00477834]
    L_0040a4cd:
        mov eax,dword ptr [esi+8]
    L_0040a4d0:
        test eax,eax
    L_0040a4d2:
        mov edi,0FFFFFFFDh
    L_0040a4d7:
        je short L_0040a4dc
    L_0040a4d9:
        and dword ptr [eax+4],edi
    L_0040a4dc:
        mov eax,dword ptr [esi+0Ch]
    L_0040a4df:
        test eax,eax
    L_0040a4e1:
        je short L_0040a4e6
    L_0040a4e3:
        and dword ptr [eax+4],edi
    L_0040a4e6:
        call asm_FUN_00424d90_00424d90
    L_0040a4eb:
        mov esi,dword ptr [data_004776f0]
    L_0040a4f1:
        mov eax,dword ptr [esi+8]
    L_0040a4f4:
        test eax,eax
    L_0040a4f6:
        je short L_0040a4fb
    L_0040a4f8:
        and dword ptr [eax+4],edi
    L_0040a4fb:
        mov eax,dword ptr [esi+0Ch]
    L_0040a4fe:
        test eax,eax
    L_0040a500:
        je short L_0040a505
    L_0040a502:
        and dword ptr [eax+4],edi
    L_0040a505:
        call asm_BulletPool_ResetRetail_00405ed0
    L_0040a50a:
        mov eax,dword ptr [data_00477704]
    L_0040a50f:
        mov ecx,dword ptr [eax+8]
    L_0040a512:
        test ecx,ecx
    L_0040a514:
        je short L_0040a519
    L_0040a516:
        and dword ptr [ecx+4],edi
    L_0040a519:
        mov ecx,dword ptr [eax+0Ch]
    L_0040a51c:
        test ecx,ecx
    L_0040a51e:
        je short L_0040a523
    L_0040a520:
        and dword ptr [ecx+4],edi
    L_0040a523:
        push eax
    L_0040a524:
        call asm_FUN_00409f90_00409f90
    L_0040a529:
        mov edx,dword ptr [data_00477818]
    L_0040a52f:
        mov eax,dword ptr [edx+8]
    L_0040a532:
        test eax,eax
    L_0040a534:
        je short L_0040a539
    L_0040a536:
        and dword ptr [eax+4],edi
    L_0040a539:
        mov eax,dword ptr [edx+0Ch]
    L_0040a53c:
        test eax,eax
    L_0040a53e:
        je short L_0040a543
    L_0040a540:
        and dword ptr [eax+4],edi
    L_0040a543:
        mov ecx,873A8h
    L_0040a548:
        xor eax,eax
    L_0040a54a:
        lea edi,[edx+14h]
    L_0040a54d:
        rep stosd
    L_0040a54f:
        mov dword ptr [ebp+30h],1
    L_0040a556:
        jmp asm_target_0040a913
    L_0040a55b:
        mov eax,dword ptr [ebp+3Ch]
    L_0040a55e:
        lea esi,[ebp+3Ch]
    L_0040a561:
        mov dword ptr [esi+4],eax
    L_0040a564:
        mov cl,byte ptr [data_00474e36]
    L_0040a56a:
        mov al,20h
    L_0040a56c:
        test cl,al
    L_0040a56e:
        jne short L_0040a578
    L_0040a570:
        test byte ptr [data_00474e34],al
    L_0040a576:
        je short L_0040a581
    L_0040a578:
        push 1
    L_0040a57a:
        mov eax,esi
    L_0040a57c:
        call asm_MenuCursor_Advance_0044bea0
    L_0040a581:
        test byte ptr [data_00474e36],10h
    L_0040a588:
        jne short L_0040a593
    L_0040a58a:
        test byte ptr [data_00474e34],10h
    L_0040a591:
        je short L_0040a59c
    L_0040a593:
        push 0FFFFFFFFh
    L_0040a595:
        mov eax,esi
    L_0040a597:
        call asm_MenuCursor_Advance_0044bea0
    L_0040a59c:
        mov esi,dword ptr [esi]
    L_0040a59e:
        sub esi,0
    L_0040a5a1:
        je asm_target_0040a6df
    L_0040a5a7:
        dec esi
    L_0040a5a8:
        je short L_0040a5d2
    L_0040a5aa:
        dec esi
    L_0040a5ab:
        jne asm_target_0040a913
    L_0040a5b1:
        test dword ptr [data_00474e36],1001h
    L_0040a5bb:
        je asm_target_0040a913
    L_0040a5c1:
        push 3
    L_0040a5c3:
        mov eax,491C28h
    L_0040a5c8:
        call asm_SetInputMode_0040ac90
    L_0040a5cd:
        jmp asm_target_0040a913
    L_0040a5d2:
        mov eax,dword ptr [data_00477704]
    L_0040a5d7:
        test eax,eax
    L_0040a5d9:
        je asm_target_0040a913
    L_0040a5df:
        mov ecx,dword ptr [ebp+1ECh]
    L_0040a5e5:
        lea ebx,[ebp+1ECh]
    L_0040a5eb:
        mov dword ptr [ebx+4],ecx
    L_0040a5ee:
        mov eax,80h
    L_0040a5f3:
        mov ecx,474E30h
    L_0040a5f8:
        call asm_InputMaskActive_0040ace0
    L_0040a5fd:
        test ax,ax
    L_0040a600:
        je short L_0040a60b
    L_0040a602:
        push 1
    L_0040a604:
        mov eax,ebx
    L_0040a606:
        call asm_MenuCursor_Advance_0044bea0
    L_0040a60b:
        mov eax,40h
    L_0040a610:
        mov ecx,474E30h
    L_0040a615:
        call asm_InputMaskActive_0040ace0
    L_0040a61a:
        test ax,ax
    L_0040a61d:
        je short L_0040a628
    L_0040a61f:
        push 0FFFFFFFFh
    L_0040a621:
        mov eax,ebx
    L_0040a623:
        call asm_MenuCursor_Advance_0044bea0
    L_0040a628:
        test dword ptr [data_00474e38],1001h
    L_0040a632:
        je asm_target_0040a913
    L_0040a638:
        mov eax,dword ptr [data_00477834]
    L_0040a63d:
        call asm_FUN_0040a010_0040a010
    L_0040a642:
        mov esi,dword ptr [data_00477834]
    L_0040a648:
        call asm_FUN_00424d90_00424d90
    L_0040a64d:
        mov esi,dword ptr [data_004776f0]
    L_0040a653:
        mov eax,esi
    L_0040a655:
        call asm_Retire_ScoreRuntimeCallbacks_00409e20
    L_0040a65a:
        call asm_BulletPool_ResetRetail_00405ed0
    L_0040a65f:
        mov esi,dword ptr [data_00477704]
    L_0040a665:
        mov eax,esi
    L_0040a667:
        call asm_FUN_0040d510_0040d510
    L_0040a66c:
        push esi
    L_0040a66d:
        call asm_FUN_00409f90_00409f90
    L_0040a672:
        mov edi,dword ptr [data_0047770c]
    L_0040a678:
        call asm_FUN_00413bc0_00413bc0
    L_0040a67d:
        mov esi,dword ptr [data_00477818]
    L_0040a683:
        mov eax,esi
    L_0040a685:
        call asm_Retire_ScoreRuntimeCallbacks_00409e20
    L_0040a68a:
        xor eax,eax
    L_0040a68c:
        mov ecx,873A8h
    L_0040a691:
        lea edi,[esi+14h]
    L_0040a694:
        rep stosd
    L_0040a696:
        mov ecx,10h
    L_0040a69b:
        lea edi,[esp+10h]
    L_0040a69f:
        rep stosd
    L_0040a6a1:
        mov ecx,dword ptr [ebx]
    L_0040a6a3:
        mov dword ptr [esp+10h],eax
    L_0040a6a7:
        mov dword ptr [esp+14h],eax
    L_0040a6ab:
        mov dword ptr [esp+18h],eax
    L_0040a6af:
        mov eax,dword ptr [data_00477704]
    L_0040a6b4:
        mov edx,dword ptr [eax+54h]
    L_0040a6b7:
        mov edx,dword ptr [edx+8Ch]
    L_0040a6bd:
        mov ecx,dword ptr [edx+ecx*8]
    L_0040a6c0:
        push ecx
    L_0040a6c1:
        push eax
    L_0040a6c2:
        lea eax,[esp+18h]
    L_0040a6c6:
        mov dword ptr [esp+2Ch],2710h
    L_0040a6ce:
        call asm_FUN_0040cfb0_0040cfb0
    L_0040a6d3:
        mov dword ptr [ebp+30h],4
    L_0040a6da:
        jmp asm_target_0040a913
    L_0040a6df:
        mov edx,dword ptr [ebp+114h]
    L_0040a6e5:
        lea esi,[ebp+114h]
    L_0040a6eb:
        mov dword ptr [esi+4],edx
    L_0040a6ee:
        mov cl,byte ptr [data_00474e36]
    L_0040a6f4:
        mov al,80h
    L_0040a6f6:
        test cl,al
    L_0040a6f8:
        jne short L_0040a702
    L_0040a6fa:
        test byte ptr [data_00474e34],al
    L_0040a700:
        je short L_0040a70b
    L_0040a702:
        push 1
    L_0040a704:
        mov eax,esi
    L_0040a706:
        call asm_MenuCursor_Advance_0044bea0
    L_0040a70b:
        mov cl,byte ptr [data_00474e36]
    L_0040a711:
        mov al,40h
    L_0040a713:
        test cl,al
    L_0040a715:
        jne short L_0040a71f
    L_0040a717:
        test byte ptr [data_00474e34],al
    L_0040a71d:
        je short L_0040a728
    L_0040a71f:
        push 0FFFFFFFFh
    L_0040a721:
        mov eax,esi
    L_0040a723:
        call asm_MenuCursor_Advance_0044bea0
    L_0040a728:
        test dword ptr [data_00474e36],1001h
    L_0040a732:
        je asm_target_0040a913
    L_0040a738:
        mov esi,dword ptr [data_0047770c]
    L_0040a73e:
        call asm_FUN_004148e0_004148e0
    L_0040a743:
        mov esi,dword ptr [data_00477834]
    L_0040a749:
        call asm_FUN_00425090_00425090
    L_0040a74e:
        mov esi,dword ptr [data_004776f0]
    L_0040a754:
        call asm_FUN_00406140_00406140
    L_0040a759:
        mov esi,dword ptr [data_004776ec]
    L_0040a75f:
        call asm_FUN_00405730_00405730
    L_0040a764:
        mov esi,dword ptr [data_00477818]
    L_0040a76a:
        call asm_FUN_0041afb0_0041afb0
    L_0040a76f:
        mov esi,dword ptr [data_00477840]
    L_0040a775:
        call asm_FUN_0042b6d0_0042b6d0
    L_0040a77a:
        mov esi,dword ptr [data_00477704]
    L_0040a780:
        call asm_FUN_0040d730_0040d730
    L_0040a785:
        mov ecx,dword ptr [ebp+684h]
    L_0040a78b:
        and ecx,0FFFFFFFDh
    L_0040a78e:
        push ebp
    L_0040a78f:
        lea eax,[ebp+10h]
    L_0040a792:
        mov edi,40A340h
    L_0040a797:
        mov dword ptr [ebp+684h],ecx
    L_0040a79d:
        call asm_FUN_0044c1c0_0044c1c0
    L_0040a7a2:
        mov dword ptr [ebp+30h],2
    L_0040a7a9:
        jmp asm_target_0040a913
    L_0040a7ae:
        mov esi,ebp
    L_0040a7b0:
        call asm_FUN_00409eb0_00409eb0
    L_0040a7b5:
        mov ebx,dword ptr [data_004660a0]
    L_0040a7bb:
        lea eax,[esp+50h]
    L_0040a7bf:
        push eax
    L_0040a7c0:
        push 46CEA8h
    L_0040a7c5:
        xor edi,edi
    L_0040a7c7:
        call ebx
    L_0040a7c9:
        mov esi,eax
    L_0040a7cb:
        cmp esi,0FFFFFFFFh
    L_0040a7ce:
        je short L_0040a7e1
    L_0040a7d0:
        lea ecx,[esp+50h]
    L_0040a7d4:
        push ecx
    L_0040a7d5:
        push esi
    L_0040a7d6:
        inc edi
    L_0040a7d7:
        call dword ptr [data_004660a4]
    L_0040a7dd:
        test eax,eax
    L_0040a7df:
        jne short L_0040a7d0
    L_0040a7e1:
        push esi
    L_0040a7e2:
        call dword ptr [data_004660a8]
    L_0040a7e8:
        xor esi,esi
    L_0040a7ea:
        cmp edi,esi
    L_0040a7ec:
        mov dword ptr [ebp+38h],edi
    L_0040a7ef:
        je short L_0040a86b
    L_0040a7f1:
        lea edx,[edi*4]
    L_0040a7f8:
        push edx
    L_0040a7f9:
        call asm_malloc_00452706
    L_0040a7fe:
        add esp,4
    L_0040a801:
        mov dword ptr [ebp+34h],eax
    L_0040a804:
        lea eax,[esp+50h]
    L_0040a808:
        push eax
    L_0040a809:
        push 46CEA8h
    L_0040a80e:
        call ebx
    L_0040a810:
        test edi,edi
    L_0040a812:
        mov ebx,eax
    L_0040a814:
        jle short L_0040a862
    L_0040a816:
        lea eax,[esp+7Ch]
    L_0040a81a:
        lea edx,[eax+1]
    L_0040a81d:
        TH10_NOP_LEA_ECX_DISP8()
    L_0040a820:
        mov cl,byte ptr [eax]
    L_0040a822:
        inc eax
    L_0040a823:
        test cl,cl
    L_0040a825:
        jne short L_0040a820
    L_0040a827:
        sub eax,edx
    L_0040a829:
        inc eax
    L_0040a82a:
        push eax
    L_0040a82b:
        call asm_malloc_00452706
    L_0040a830:
        mov ecx,dword ptr [ebp+34h]
    L_0040a833:
        mov dword ptr [ecx+esi*4],eax
    L_0040a836:
        mov edx,dword ptr [ebp+34h]
    L_0040a839:
        mov edx,dword ptr [edx+esi*4]
    L_0040a83c:
        add esp,4
    L_0040a83f:
        lea ecx,[esp+7Ch]
    L_0040a843:
        mov al,byte ptr [ecx]
    L_0040a845:
        inc ecx
    L_0040a846:
        mov byte ptr [edx],al
    L_0040a848:
        inc edx
    L_0040a849:
        test al,al
    L_0040a84b:
        jne short L_0040a843
    L_0040a84d:
        lea eax,[esp+50h]
    L_0040a851:
        push eax
    L_0040a852:
        push ebx
    L_0040a853:
        call dword ptr [data_004660a4]
    L_0040a859:
        test eax,eax
    L_0040a85b:
        je short L_0040a862
    L_0040a85d:
        inc esi
    L_0040a85e:
        cmp esi,edi
    L_0040a860:
        jl short L_0040a816
    L_0040a862:
        push ebx
    L_0040a863:
        call dword ptr [data_004660a8]
    L_0040a869:
        xor esi,esi
    L_0040a86b:
        mov ecx,1
    L_0040a870:
        mov dword ptr [ebp+44h],3
    L_0040a877:
        mov dword ptr [ebp+10Ch],ecx
    L_0040a87d:
        mov eax,dword ptr [ebp+44h]
    L_0040a880:
        cmp eax,esi
    L_0040a882:
        je short L_0040a893
    L_0040a884:
        jg short L_0040a88c
    L_0040a886:
        dec eax
    L_0040a887:
        mov dword ptr [ebp+3Ch],eax
    L_0040a88a:
        jmp short L_0040a896
    L_0040a88c:
        xor eax,eax
    L_0040a88e:
        mov dword ptr [ebp+3Ch],eax
    L_0040a891:
        jmp short L_0040a896
    L_0040a893:
        mov dword ptr [ebp+3Ch],esi
    L_0040a896:
        mov eax,edi
    L_0040a898:
        cmp eax,esi
    L_0040a89a:
        mov dword ptr [ebp+11Ch],edi
    L_0040a8a0:
        mov dword ptr [ebp+1E4h],ecx
    L_0040a8a6:
        je short L_0040a8bd
    L_0040a8a8:
        jg short L_0040a8b3
    L_0040a8aa:
        dec eax
    L_0040a8ab:
        mov dword ptr [ebp+114h],eax
    L_0040a8b1:
        jmp short L_0040a8c3
    L_0040a8b3:
        xor eax,eax
    L_0040a8b5:
        mov dword ptr [ebp+114h],eax
    L_0040a8bb:
        jmp short L_0040a8c3
    L_0040a8bd:
        mov dword ptr [ebp+114h],esi
    L_0040a8c3:
        mov eax,ecx
    L_0040a8c5:
        cmp eax,esi
    L_0040a8c7:
        mov dword ptr [ebp+1F4h],ecx
    L_0040a8cd:
        mov dword ptr [ebp+2BCh],ecx
    L_0040a8d3:
        je short L_0040a8ea
    L_0040a8d5:
        jg short L_0040a8e0
    L_0040a8d7:
        dec eax
    L_0040a8d8:
        mov dword ptr [ebp+1ECh],eax
    L_0040a8de:
        jmp short L_0040a8f0
    L_0040a8e0:
        xor eax,eax
    L_0040a8e2:
        mov dword ptr [ebp+1ECh],eax
    L_0040a8e8:
        jmp short L_0040a8f0
    L_0040a8ea:
        mov dword ptr [ebp+1ECh],esi
    L_0040a8f0:
        mov dword ptr [ebp+30h],ecx
    L_0040a8f3:
        mov dword ptr [ebp+674h],esi
    L_0040a8f9:
        mov dword ptr [ebp+678h],42000000h
    L_0040a903:
        mov dword ptr [ebp+67Ch],esi
    L_0040a909:
        mov dword ptr [ebp+680h],3E8h
    L_0040a913:
        mov ecx,dword ptr [esp+190h]
    L_0040a91a:
        pop edi
    L_0040a91b:
        pop esi
    L_0040a91c:
        pop ebp
    L_0040a91d:
        pop ebx
    L_0040a91e:
        xor ecx,esp
    L_0040a920:
        mov eax,1
    L_0040a925:
        call asm_security_check_cookie_00458ea5
    L_0040a92a:
        add esp,184h
    L_0040a930:
        ret 4
    }
}
