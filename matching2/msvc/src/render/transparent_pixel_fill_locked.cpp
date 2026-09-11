#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004465B0..0x004467CC: FUN_004465b0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004465b0_004465b0() {
    __asm {
    L_004465b0:
        sub esp,40h
    L_004465b3:
        mov eax,dword ptr [eax]
    L_004465b5:
        push esi
    L_004465b6:
        lea edx,[esp+4]
    L_004465ba:
        push edx
    L_004465bb:
        xor esi,esi
    L_004465bd:
        push esi
    L_004465be:
        mov dword ptr [esp+0Ch],esi
    L_004465c2:
        mov ecx,dword ptr [eax]
    L_004465c4:
        push eax
    L_004465c5:
        call dword ptr [ecx+48h]
    L_004465c8:
        mov eax,dword ptr [esp+4]
    L_004465cc:
        mov ecx,dword ptr [eax]
    L_004465ce:
        lea edx,[esp+24h]
    L_004465d2:
        push edx
    L_004465d3:
        push eax
    L_004465d4:
        call dword ptr [ecx+30h]
    L_004465d7:
        mov eax,dword ptr [esp+4]
    L_004465db:
        mov ecx,dword ptr [eax]
    L_004465dd:
        push esi
    L_004465de:
        push esi
    L_004465df:
        lea edx,[esp+18h]
    L_004465e3:
        push edx
    L_004465e4:
        push eax
    L_004465e5:
        call dword ptr [ecx+34h]
    L_004465e8:
        mov eax,dword ptr [esp+24h]
    L_004465ec:
        cmp eax,1Ah
    L_004465ef:
        ja asm_target_00446b20
    L_004465f5:
        movzx eax,byte ptr [eax+446B4Ch]
    L_004465fc:
        push ebx
    L_004465fd:
        push ebp
    L_004465fe:
        push edi
    L_004465ff:
        jmp dword ptr [eax*4+446B3Ch]
    L_00446606:
        mov eax,dword ptr [esp+4Ch]
    L_0044660a:
        xor edx,edx
    L_0044660c:
        cmp eax,esi
    L_0044660e:
        mov dword ptr [esp+14h],edx
    L_00446612:
        jbe asm_target_00446b1d
    L_00446618:
        mov ebp,dword ptr [esp+48h]
    L_0044661c:
        TH10_NOP_LEA_ESP_DISP8()
    L_00446620:
        mov edi,dword ptr [esp+1Ch]
    L_00446624:
        mov ebx,dword ptr [esp+20h]
    L_00446628:
        imul edi,edx
    L_0044662b:
        xor eax,eax
    L_0044662d:
        add edi,ebx
    L_0044662f:
        cmp ebp,esi
    L_00446631:
        mov dword ptr [esp+18h],eax
    L_00446635:
        jbe asm_target_00446782
    L_0044663b:
        lea ecx,[edi-2]
    L_0044663e:
        mov edi,edi
    L_00446640:
        mov bl,byte ptr [ecx+5]
    L_00446643:
        test bl,bl
    L_00446645:
        jne asm_target_0044676d
    L_0044664b:
        mov dword ptr [esp+2Ch],esi
    L_0044664f:
        mov dword ptr [esp+28h],esi
    L_00446653:
        xor ebx,ebx
    L_00446655:
        xor esi,esi
    L_00446657:
        test eax,eax
    L_00446659:
        jbe short L_00446679
    L_0044665b:
        cmp byte ptr [ecx+1],0
    L_0044665f:
        je short L_00446679
    L_00446661:
        movzx esi,byte ptr [ecx-1]
    L_00446665:
        movzx ebx,byte ptr [ecx]
    L_00446668:
        mov dword ptr [esp+28h],esi
    L_0044666c:
        movzx esi,byte ptr [ecx-2]
    L_00446670:
        mov dword ptr [esp+2Ch],esi
    L_00446674:
        mov esi,1
    L_00446679:
        dec ebp
    L_0044667a:
        cmp eax,ebp
    L_0044667c:
        jae short L_004466a2
    L_0044667e:
        mov al,byte ptr [ecx+9]
    L_00446681:
        test al,al
    L_00446683:
        je short L_004466a2
    L_00446685:
        movzx eax,byte ptr [ecx+8]
    L_00446689:
        mov ebp,dword ptr [esp+28h]
    L_0044668d:
        add ebx,eax
    L_0044668f:
        movzx eax,byte ptr [ecx+7]
    L_00446693:
        add ebp,eax
    L_00446695:
        movzx eax,byte ptr [ecx+6]
    L_00446699:
        mov dword ptr [esp+28h],ebp
    L_0044669d:
        add dword ptr [esp+2Ch],eax
    L_004466a1:
        inc esi
    L_004466a2:
        test edx,edx
    L_004466a4:
        jbe short L_004466e5
    L_004466a6:
        mov eax,dword ptr [esp+1Ch]
    L_004466aa:
        cdq
    L_004466ab:
        and edx,3
    L_004466ae:
        add eax,edx
    L_004466b0:
        sar eax,2
    L_004466b3:
        shl eax,2
    L_004466b6:
        mov edx,eax
    L_004466b8:
        mov eax,edi
    L_004466ba:
        sub eax,edx
    L_004466bc:
        mov dl,byte ptr [eax+3]
    L_004466bf:
        test dl,dl
    L_004466c1:
        je short L_004466e5
    L_004466c3:
        movzx edx,byte ptr [eax+2]
    L_004466c7:
        mov ebp,dword ptr [esp+28h]
    L_004466cb:
        add ebx,edx
    L_004466cd:
        movzx edx,byte ptr [eax+1]
    L_004466d1:
        movzx eax,byte ptr [eax]
    L_004466d4:
        add ebp,edx
    L_004466d6:
        mov edx,dword ptr [esp+2Ch]
    L_004466da:
        add edx,eax
    L_004466dc:
        mov dword ptr [esp+28h],ebp
    L_004466e0:
        mov dword ptr [esp+2Ch],edx
    L_004466e4:
        inc esi
    L_004466e5:
        mov edx,dword ptr [esp+4Ch]
    L_004466e9:
        mov eax,dword ptr [esp+14h]
    L_004466ed:
        dec edx
    L_004466ee:
        cmp eax,edx
    L_004466f0:
        jae short L_0044672c
    L_004466f2:
        mov eax,dword ptr [esp+1Ch]
    L_004466f6:
        cdq
    L_004466f7:
        and edx,3
    L_004466fa:
        add eax,edx
    L_004466fc:
        sar eax,2
    L_004466ff:
        mov dl,byte ptr [edi+eax*4+3]
    L_00446703:
        test dl,dl
    L_00446705:
        lea eax,[edi+eax*4]
    L_00446708:
        je short L_0044672c
    L_0044670a:
        movzx edx,byte ptr [eax+2]
    L_0044670e:
        mov ebp,dword ptr [esp+28h]
    L_00446712:
        add ebx,edx
    L_00446714:
        movzx edx,byte ptr [eax+1]
    L_00446718:
        movzx eax,byte ptr [eax]
    L_0044671b:
        add ebp,edx
    L_0044671d:
        mov edx,dword ptr [esp+2Ch]
    L_00446721:
        add edx,eax
    L_00446723:
        mov dword ptr [esp+28h],ebp
    L_00446727:
        mov dword ptr [esp+2Ch],edx
    L_0044672b:
        inc esi
    L_0044672c:
        cmp esi,1
    L_0044672f:
        jbe short L_00446751
    L_00446731:
        xor edx,edx
    L_00446733:
        mov eax,ebx
    L_00446735:
        div esi
    L_00446737:
        xor edx,edx
    L_00446739:
        mov ebx,eax
    L_0044673b:
        mov eax,dword ptr [esp+28h]
    L_0044673f:
        div esi
    L_00446741:
        xor edx,edx
    L_00446743:
        mov dword ptr [esp+28h],eax
    L_00446747:
        mov eax,dword ptr [esp+2Ch]
    L_0044674b:
        div esi
    L_0044674d:
        mov dword ptr [esp+2Ch],eax
    L_00446751:
        mov dl,byte ptr [esp+28h]
    L_00446755:
        mov al,byte ptr [esp+2Ch]
    L_00446759:
        mov byte ptr [ecx+3],dl
    L_0044675c:
        mov edx,dword ptr [esp+14h]
    L_00446760:
        mov byte ptr [edi],al
    L_00446762:
        mov eax,dword ptr [esp+18h]
    L_00446766:
        mov byte ptr [ecx+4],bl
    L_00446769:
        mov ebp,dword ptr [esp+48h]
    L_0044676d:
        add edi,4
    L_00446770:
        add ecx,4
    L_00446773:
        inc eax
    L_00446774:
        xor esi,esi
    L_00446776:
        cmp eax,ebp
    L_00446778:
        mov dword ptr [esp+18h],eax
    L_0044677c:
        jb asm_target_00446640
    L_00446782:
        mov eax,dword ptr [esp+4Ch]
    L_00446786:
        inc edx
    L_00446787:
        cmp edx,eax
    L_00446789:
        mov dword ptr [esp+14h],edx
    L_0044678d:
        jb asm_target_00446620
    L_00446793:
        jmp asm_target_00446b1d
    L_00446798:
        mov eax,dword ptr [esp+4Ch]
    L_0044679c:
        xor ecx,ecx
    L_0044679e:
        cmp eax,esi
    L_004467a0:
        mov dword ptr [esp+14h],ecx
    L_004467a4:
        jbe asm_target_00446b1d
    L_004467aa:
        mov edx,dword ptr [esp+48h]
    L_004467ae:
        mov edi,edi
    L_004467b0:
        mov ebx,dword ptr [esp+20h]
    L_004467b4:
        mov ebp,ecx
    L_004467b6:
        imul ebp,dword ptr [esp+1Ch]
    L_004467bb:
        xor eax,eax
    L_004467bd:
        add ebp,ebx
    L_004467bf:
        cmp edx,esi
    L_004467c1:
        mov dword ptr [esp+18h],eax
    L_004467c5:
        jbe asm_target_00446948
    L_004467cb:
        TH10_REL8(0xeb, 0x004467cb, VA_asm_FUN_004465b0_part_004467d0)
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_004467d0:
        test byte ptr [ebp+1],80h
    L_004467d4:
        jne asm_target_00446934
    L_004467da:
        xor ebx,ebx
    L_004467dc:
        xor ecx,ecx
    L_004467de:
        xor edi,edi
    L_004467e0:
        cmp eax,esi
    L_004467e2:
        mov dword ptr [esp+2Ch],esi
    L_004467e6:
        jbe short L_0044680f
    L_004467e8:
        mov ax,word ptr [ebp-2]
    L_004467ec:
        test ah,ah
    L_004467ee:
        jns short L_0044680f
    L_004467f0:
        movzx esi,ax
    L_004467f3:
        mov ecx,esi
    L_004467f5:
        mov ebx,esi
    L_004467f7:
        shr ecx,0Ah
    L_004467fa:
        shr ebx,5
    L_004467fd:
        and ecx,1Fh
    L_00446800:
        and ebx,1Fh
    L_00446803:
        and esi,1Fh
    L_00446806:
        mov dword ptr [esp+2Ch],esi
    L_0044680a:
        mov edi,1
    L_0044680f:
        mov eax,dword ptr [esp+18h]
    L_00446813:
        dec edx
    L_00446814:
        cmp eax,edx
    L_00446816:
        jae short L_00446845
    L_00446818:
        mov ax,word ptr [ebp+2]
    L_0044681c:
        test ah,ah
    L_0044681e:
        jns short L_00446845
    L_00446820:
        movzx esi,ax
    L_00446823:
        mov edx,esi
    L_00446825:
        shr edx,0Ah
    L_00446828:
        and edx,1Fh
    L_0044682b:
        mov eax,esi
    L_0044682d:
        add ecx,edx
    L_0044682f:
        mov edx,dword ptr [esp+2Ch]
    L_00446833:
        shr eax,5
    L_00446836:
        and esi,1Fh
    L_00446839:
        and eax,1Fh
    L_0044683c:
        add edx,esi
    L_0044683e:
        add ebx,eax
    L_00446840:
        mov dword ptr [esp+2Ch],edx
    L_00446844:
        inc edi
    L_00446845:
        mov eax,dword ptr [esp+14h]
    L_00446849:
        xor esi,esi
    L_0044684b:
        cmp eax,esi
    L_0044684d:
        jbe short L_0044688c
    L_0044684f:
        mov eax,dword ptr [esp+1Ch]
    L_00446853:
        cdq
    L_00446854:
        sub eax,edx
    L_00446856:
        sar eax,1
    L_00446858:
        shl eax,1
    L_0044685a:
        mov edx,eax
    L_0044685c:
        mov eax,ebp
    L_0044685e:
        sub eax,edx
    L_00446860:
        mov ax,word ptr [eax]
    L_00446863:
        test ah,ah
    L_00446865:
        jns short L_0044688c
    L_00446867:
        movzx eax,ax
    L_0044686a:
        mov edx,eax
    L_0044686c:
        shr edx,0Ah
    L_0044686f:
        and edx,1Fh
    L_00446872:
        add ecx,edx
    L_00446874:
        mov edx,eax
    L_00446876:
        shr edx,5
    L_00446879:
        and edx,1Fh
    L_0044687c:
        add ebx,edx
    L_0044687e:
        mov edx,dword ptr [esp+2Ch]
    L_00446882:
        and eax,1Fh
    L_00446885:
        add edx,eax
    L_00446887:
        mov dword ptr [esp+2Ch],edx
    L_0044688b:
        inc edi
    L_0044688c:
        mov eax,dword ptr [esp+4Ch]
    L_00446890:
        mov edx,dword ptr [esp+14h]
    L_00446894:
        dec eax
    L_00446895:
        cmp edx,eax
    L_00446897:
        jae short L_004468d2
    L_00446899:
        mov eax,dword ptr [esp+1Ch]
    L_0044689d:
        cdq
    L_0044689e:
        sub eax,edx
    L_004468a0:
        sar eax,1
    L_004468a2:
        lea eax,[ebp+eax*2]
    L_004468a6:
        mov ax,word ptr [eax]
    L_004468a9:
        test ah,ah
    L_004468ab:
        jns short L_004468d2
    L_004468ad:
        movzx eax,ax
    L_004468b0:
        mov edx,eax
    L_004468b2:
        shr edx,0Ah
    L_004468b5:
        and edx,1Fh
    L_004468b8:
        add ecx,edx
    L_004468ba:
        mov edx,eax
    L_004468bc:
        shr edx,5
    L_004468bf:
        and edx,1Fh
    L_004468c2:
        add ebx,edx
    L_004468c4:
        mov edx,dword ptr [esp+2Ch]
    L_004468c8:
        and eax,1Fh
    L_004468cb:
        add edx,eax
    L_004468cd:
        mov dword ptr [esp+2Ch],edx
    L_004468d1:
        inc edi
    L_004468d2:
        cmp edi,1
    L_004468d5:
        jbe short L_004468f3
    L_004468d7:
        xor edx,edx
    L_004468d9:
        mov eax,ecx
    L_004468db:
        div edi
    L_004468dd:
        xor edx,edx
    L_004468df:
        mov ecx,eax
    L_004468e1:
        mov eax,ebx
    L_004468e3:
        div edi
    L_004468e5:
        xor edx,edx
    L_004468e7:
        mov ebx,eax
    L_004468e9:
        mov eax,dword ptr [esp+2Ch]
    L_004468ed:
        div edi
    L_004468ef:
        mov dword ptr [esp+2Ch],eax
    L_004468f3:
        and cl,1Fh
    L_004468f6:
        movzx cx,cl
    L_004468fa:
        and bl,1Fh
    L_004468fd:
        movzx dx,bl
    L_00446901:
        xor eax,eax
    L_00446903:
        mov ax,word ptr [ebp]
    L_00446907:
        shl ecx,5
    L_0044690a:
        or ecx,edx
    L_0044690c:
        shl ecx,5
    L_0044690f:
        and eax,801Fh
    L_00446914:
        or ecx,eax
    L_00446916:
        mov al,byte ptr [esp+2Ch]
    L_0044691a:
        and al,1Fh
    L_0044691c:
        movzx dx,al
    L_00446920:
        mov eax,dword ptr [esp+18h]
    L_00446924:
        and ecx,0FFE0h
    L_0044692a:
        or ecx,edx
    L_0044692c:
        mov word ptr [ebp],cx
    L_00446930:
        mov edx,dword ptr [esp+48h]
    L_00446934:
        add ebp,2
    L_00446937:
        inc eax
    L_00446938:
        cmp eax,edx
    L_0044693a:
        mov dword ptr [esp+18h],eax
    L_0044693e:
        jb asm_FUN_004465b0_part_004467d0
    L_00446944:
        mov ecx,dword ptr [esp+14h]
    L_00446948:
        mov eax,dword ptr [esp+4Ch]
    L_0044694c:
        inc ecx
    L_0044694d:
        cmp ecx,eax
    L_0044694f:
        mov dword ptr [esp+14h],ecx
    L_00446953:
        jb asm_target_004467b0
    L_00446959:
        jmp asm_target_00446b1d
    L_0044695e:
        mov eax,dword ptr [esp+4Ch]
    L_00446962:
        xor ecx,ecx
    L_00446964:
        cmp eax,esi
    L_00446966:
        mov dword ptr [esp+14h],ecx
    L_0044696a:
        jbe asm_target_00446b1d
    L_00446970:
        mov edx,dword ptr [esp+48h]
    L_00446974:
        mov ebx,dword ptr [esp+20h]
    L_00446978:
        mov ebp,ecx
    L_0044697a:
        imul ebp,dword ptr [esp+1Ch]
    L_0044697f:
        xor eax,eax
    L_00446981:
        add ebp,ebx
    L_00446983:
        cmp edx,esi
    L_00446985:
        mov dword ptr [esp+18h],eax
    L_00446989:
        jbe asm_target_00446b0c
    L_0044698f:
        nop
    L_00446990:
        test byte ptr [ebp+1],0F0h
    L_00446994:
        jne asm_target_00446af8
    L_0044699a:
        xor ebx,ebx
    L_0044699c:
        xor ecx,ecx
    L_0044699e:
        xor edi,edi
    L_004469a0:
        cmp eax,esi
    L_004469a2:
        mov dword ptr [esp+2Ch],esi
    L_004469a6:
        jbe short L_004469d0
    L_004469a8:
        mov ax,word ptr [ebp-2]
    L_004469ac:
        test ah,0F0h
    L_004469af:
        je short L_004469d0
    L_004469b1:
        movzx esi,ax
    L_004469b4:
        mov ecx,esi
    L_004469b6:
        mov ebx,esi
    L_004469b8:
        shr ecx,8
    L_004469bb:
        shr ebx,4
    L_004469be:
        and ecx,0Fh
    L_004469c1:
        and ebx,0Fh
    L_004469c4:
        and esi,0Fh
    L_004469c7:
        mov dword ptr [esp+2Ch],esi
    L_004469cb:
        mov edi,1
    L_004469d0:
        mov eax,dword ptr [esp+18h]
    L_004469d4:
        dec edx
    L_004469d5:
        cmp eax,edx
    L_004469d7:
        jae short L_00446a07
    L_004469d9:
        mov ax,word ptr [ebp+2]
    L_004469dd:
        test ah,0F0h
    L_004469e0:
        je short L_00446a07
    L_004469e2:
        movzx esi,ax
    L_004469e5:
        mov edx,esi
    L_004469e7:
        shr edx,4
    L_004469ea:
        and edx,0Fh
    L_004469ed:
        mov eax,esi
    L_004469ef:
        add ebx,edx
    L_004469f1:
        mov edx,dword ptr [esp+2Ch]
    L_004469f5:
        shr eax,8
    L_004469f8:
        and esi,0Fh
    L_004469fb:
        and eax,0Fh
    L_004469fe:
        add edx,esi
    L_00446a00:
        add ecx,eax
    L_00446a02:
        mov dword ptr [esp+2Ch],edx
    L_00446a06:
        inc edi
    L_00446a07:
        mov eax,dword ptr [esp+14h]
    L_00446a0b:
        xor esi,esi
    L_00446a0d:
        cmp eax,esi
    L_00446a0f:
        jbe short L_00446a4f
    L_00446a11:
        mov eax,dword ptr [esp+1Ch]
    L_00446a15:
        cdq
    L_00446a16:
        sub eax,edx
    L_00446a18:
        sar eax,1
    L_00446a1a:
        shl eax,1
    L_00446a1c:
        mov edx,eax
    L_00446a1e:
        mov eax,ebp
    L_00446a20:
        sub eax,edx
    L_00446a22:
        mov ax,word ptr [eax]
    L_00446a25:
        test ah,0F0h
    L_00446a28:
        je short L_00446a4f
    L_00446a2a:
        movzx eax,ax
    L_00446a2d:
        mov edx,eax
    L_00446a2f:
        shr edx,8
    L_00446a32:
        and edx,0Fh
    L_00446a35:
        add ecx,edx
    L_00446a37:
        mov edx,eax
    L_00446a39:
        shr edx,4
    L_00446a3c:
        and edx,0Fh
    L_00446a3f:
        add ebx,edx
    L_00446a41:
        mov edx,dword ptr [esp+2Ch]
    L_00446a45:
        and eax,0Fh
    L_00446a48:
        add edx,eax
    L_00446a4a:
        mov dword ptr [esp+2Ch],edx
    L_00446a4e:
        inc edi
    L_00446a4f:
        mov eax,dword ptr [esp+4Ch]
    L_00446a53:
        mov edx,dword ptr [esp+14h]
    L_00446a57:
        dec eax
    L_00446a58:
        cmp edx,eax
    L_00446a5a:
        jae short L_00446a96
    L_00446a5c:
        mov eax,dword ptr [esp+1Ch]
    L_00446a60:
        cdq
    L_00446a61:
        sub eax,edx
    L_00446a63:
        sar eax,1
    L_00446a65:
        lea eax,[ebp+eax*2]
    L_00446a69:
        mov ax,word ptr [eax]
    L_00446a6c:
        test ah,0F0h
    L_00446a6f:
        je short L_00446a96
    L_00446a71:
        movzx eax,ax
    L_00446a74:
        mov edx,eax
    L_00446a76:
        shr edx,8
    L_00446a79:
        and edx,0Fh
    L_00446a7c:
        add ecx,edx
    L_00446a7e:
        mov edx,eax
    L_00446a80:
        shr edx,4
    L_00446a83:
        and edx,0Fh
    L_00446a86:
        add ebx,edx
    L_00446a88:
        mov edx,dword ptr [esp+2Ch]
    L_00446a8c:
        and eax,0Fh
    L_00446a8f:
        add edx,eax
    L_00446a91:
        mov dword ptr [esp+2Ch],edx
    L_00446a95:
        inc edi
    L_00446a96:
        cmp edi,1
    L_00446a99:
        jbe short L_00446ab7
    L_00446a9b:
        xor edx,edx
    L_00446a9d:
        mov eax,ecx
    L_00446a9f:
        div edi
    L_00446aa1:
        xor edx,edx
    L_00446aa3:
        mov ecx,eax
    L_00446aa5:
        mov eax,ebx
    L_00446aa7:
        div edi
    L_00446aa9:
        xor edx,edx
    L_00446aab:
        mov ebx,eax
    L_00446aad:
        mov eax,dword ptr [esp+2Ch]
    L_00446ab1:
        div edi
    L_00446ab3:
        mov dword ptr [esp+2Ch],eax
    L_00446ab7:
        and cl,0Fh
    L_00446aba:
        movzx cx,cl
    L_00446abe:
        and bl,0Fh
    L_00446ac1:
        movzx dx,bl
    L_00446ac5:
        xor eax,eax
    L_00446ac7:
        mov ax,word ptr [ebp]
    L_00446acb:
        shl ecx,4
    L_00446ace:
        or ecx,edx
    L_00446ad0:
        shl ecx,4
    L_00446ad3:
        and eax,0F00Fh
    L_00446ad8:
        or ecx,eax
    L_00446ada:
        mov al,byte ptr [esp+2Ch]
    L_00446ade:
        and al,0Fh
    L_00446ae0:
        movzx dx,al
    L_00446ae4:
        mov eax,dword ptr [esp+18h]
    L_00446ae8:
        and ecx,0FFF0h
    L_00446aee:
        or ecx,edx
    L_00446af0:
        mov word ptr [ebp],cx
    L_00446af4:
        mov edx,dword ptr [esp+48h]
    L_00446af8:
        add ebp,2
    L_00446afb:
        inc eax
    L_00446afc:
        cmp eax,edx
    L_00446afe:
        mov dword ptr [esp+18h],eax
    L_00446b02:
        jb asm_target_00446990
    L_00446b08:
        mov ecx,dword ptr [esp+14h]
    L_00446b0c:
        mov eax,dword ptr [esp+4Ch]
    L_00446b10:
        inc ecx
    L_00446b11:
        cmp ecx,eax
    L_00446b13:
        mov dword ptr [esp+14h],ecx
    L_00446b17:
        jb asm_target_00446974
    L_00446b1d:
        pop edi
    L_00446b1e:
        pop ebp
    L_00446b1f:
        pop ebx
    L_00446b20:
        mov eax,dword ptr [esp+4]
    L_00446b24:
        mov ecx,dword ptr [eax]
    L_00446b26:
        push eax
    L_00446b27:
        call dword ptr [ecx+38h]
    L_00446b2a:
        mov eax,dword ptr [esp+4]
    L_00446b2e:
        mov edx,dword ptr [eax]
    L_00446b30:
        push eax
    L_00446b31:
        call dword ptr [edx+8]
    L_00446b34:
        pop esi
    L_00446b35:
        add esp,40h
    L_00446b38:
        ret
    }
}
