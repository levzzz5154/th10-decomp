#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00404610..0x00404986: FUN_00404610
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00404610_00404610() {
    __asm {
    L_00404610:
        sub esp,44h
    L_00404613:
        push ebx
    L_00404614:
        push esi
    L_00404615:
        mov esi,eax
    L_00404617:
        mov eax,dword ptr [esi+44h]
    L_0040461a:
        xor ebx,ebx
    L_0040461c:
        cmp eax,ebx
    L_0040461e:
        mov dword ptr [esp+0Ch],eax
    L_00404622:
        jle asm_target_004046f0
    L_00404628:
        mov edx,dword ptr [esi+34h]
    L_0040462b:
        mov ecx,dword ptr [esi+3Ch]
    L_0040462e:
        mov dword ptr [esi+30h],edx
    L_00404631:
        fld dword ptr [ecx]
    L_00404633:
        fcomp dword ptr [data_00470b68]
    L_00404639:
        fnstsw ax
    L_0040463b:
        test ah,41h
    L_0040463e:
        jne short L_00404661
    L_00404640:
        fld dword ptr [ecx]
    L_00404642:
        fcomp dword ptr [data_00470b64]
    L_00404648:
        fnstsw ax
    L_0040464a:
        test ah,5
    L_0040464d:
        jp short L_00404661
    L_0040464f:
        fld dword ptr [esi+38h]
    L_00404652:
        inc edx
    L_00404653:
        fadd dword ptr [data_00470afc]
    L_00404659:
        mov dword ptr [esi+34h],edx
    L_0040465c:
        fstp dword ptr [esi+38h]
    L_0040465f:
        jmp short L_00404671
    L_00404661:
        fld dword ptr [ecx]
    L_00404663:
        fadd dword ptr [esi+38h]
    L_00404666:
        fst dword ptr [esi+38h]
    L_00404669:
        call asm_FUN_00463b2c_00463b2c
    L_0040466e:
        mov dword ptr [esi+34h],eax
    L_00404671:
        mov ecx,dword ptr [esi+44h]
    L_00404674:
        cmp dword ptr [esi+34h],ecx
    L_00404677:
        mov dword ptr [esp+0Ch],ecx
    L_0040467b:
        jl short L_004046f0
    L_0040467d:
        mov eax,dword ptr [esi+40h]
    L_00404680:
        test al,1
    L_00404682:
        mov dword ptr [esp+0Ch],ecx
    L_00404686:
        jne short L_004046a2
    L_00404688:
        or eax,1
    L_0040468b:
        mov dword ptr [esi+34h],ebx
    L_0040468e:
        mov dword ptr [esi+30h],0FFF0BDC1h
    L_00404695:
        mov dword ptr [esi+38h],ebx
    L_00404698:
        mov dword ptr [esi+3Ch],476F78h
    L_0040469f:
        mov dword ptr [esi+40h],eax
    L_004046a2:
        fild dword ptr [esp+0Ch]
    L_004046a6:
        mov dword ptr [esi+34h],ecx
    L_004046a9:
        dec ecx
    L_004046aa:
        mov dword ptr [esi+30h],ecx
    L_004046ad:
        fstp dword ptr [esi+38h]
    L_004046b0:
        mov eax,dword ptr [esi+48h]
    L_004046b3:
        cmp eax,7
    L_004046b6:
        mov dword ptr [esi+44h],ebx
    L_004046b9:
        je short L_004046d6
    L_004046bb:
        add esi,0Ch
    L_004046be:
        mov ecx,dword ptr [esi]
    L_004046c0:
        mov eax,edi
    L_004046c2:
        mov dword ptr [eax],ecx
    L_004046c4:
        mov edx,dword ptr [esi+4]
    L_004046c7:
        mov dword ptr [eax+4],edx
    L_004046ca:
        mov ecx,dword ptr [esi+8]
    L_004046cd:
        pop esi
    L_004046ce:
        mov dword ptr [eax+8],ecx
    L_004046d1:
        pop ebx
    L_004046d2:
        add esp,44h
    L_004046d5:
        ret
    L_004046d6:
        mov eax,dword ptr [esi]
    L_004046d8:
        mov edx,edi
    L_004046da:
        mov dword ptr [edx],eax
    L_004046dc:
        mov ecx,dword ptr [esi+4]
    L_004046df:
        mov dword ptr [edx+4],ecx
    L_004046e2:
        mov eax,dword ptr [esi+8]
    L_004046e5:
        pop esi
    L_004046e6:
        mov dword ptr [edx+8],eax
    L_004046e9:
        mov eax,edi
    L_004046eb:
        pop ebx
    L_004046ec:
        add esp,44h
    L_004046ef:
        ret
    L_004046f0:
        mov eax,dword ptr [esi+48h]
    L_004046f3:
        cmp eax,7
    L_004046f6:
        jne short L_00404755
    L_004046f8:
        mov ecx,esi
    L_004046fa:
        mov edx,dword ptr [ecx]
    L_004046fc:
        mov eax,dword ptr [ecx+4]
    L_004046ff:
        mov ecx,dword ptr [ecx+8]
    L_00404702:
        mov dword ptr [esp+10h],edx
    L_00404706:
        fld dword ptr [esp+10h]
    L_0040470a:
        fadd dword ptr [esi+0Ch]
    L_0040470d:
        mov dword ptr [esp+14h],eax
    L_00404711:
        mov dword ptr [esp+18h],ecx
    L_00404715:
        fstp dword ptr [esp+1Ch]
    L_00404719:
        mov eax,dword ptr [esp+1Ch]
    L_0040471d:
        fld dword ptr [esp+14h]
    L_00404721:
        fadd dword ptr [esi+10h]
    L_00404724:
        fstp dword ptr [esp+20h]
    L_00404728:
        mov ecx,dword ptr [esp+20h]
    L_0040472c:
        fld dword ptr [esp+18h]
    L_00404730:
        fadd dword ptr [esi+14h]
    L_00404733:
        mov dword ptr [esi],eax
    L_00404735:
        mov dword ptr [esi+4],ecx
    L_00404738:
        fstp dword ptr [esp+24h]
    L_0040473c:
        mov edx,dword ptr [esp+24h]
    L_00404740:
        mov dword ptr [esi+8],edx
    L_00404743:
        mov esi,edi
    L_00404745:
        mov dword ptr [esi],eax
    L_00404747:
        mov dword ptr [esi+4],ecx
    L_0040474a:
        mov dword ptr [esi+8],edx
    L_0040474d:
        pop esi
    L_0040474e:
        mov eax,edi
    L_00404750:
        pop ebx
    L_00404751:
        add esp,44h
    L_00404754:
        ret
    L_00404755:
        cmp eax,11h
    L_00404758:
        jne asm_target_004047f2
    L_0040475e:
        mov edx,esi
    L_00404760:
        mov eax,dword ptr [edx]
    L_00404762:
        mov ecx,dword ptr [edx+4]
    L_00404765:
        mov edx,dword ptr [edx+8]
    L_00404768:
        mov dword ptr [esp+1Ch],eax
    L_0040476c:
        fld dword ptr [esp+1Ch]
    L_00404770:
        fadd dword ptr [esi+24h]
    L_00404773:
        lea eax,[esi+24h]
    L_00404776:
        mov dword ptr [esp+20h],ecx
    L_0040477a:
        push ebp
    L_0040477b:
        fstp dword ptr [esp+14h]
    L_0040477f:
        mov ecx,dword ptr [esp+14h]
    L_00404783:
        fld dword ptr [esp+24h]
    L_00404787:
        mov dword ptr [esp+28h],edx
    L_0040478b:
        fadd dword ptr [eax+4]
    L_0040478e:
        mov ebp,esi
    L_00404790:
        fstp dword ptr [esp+18h]
    L_00404794:
        mov edx,dword ptr [esp+18h]
    L_00404798:
        fld dword ptr [esp+28h]
    L_0040479c:
        fadd dword ptr [eax+8]
    L_0040479f:
        mov dword ptr [ebp],ecx
    L_004047a2:
        mov dword ptr [ebp+4],edx
    L_004047a5:
        fstp dword ptr [esp+1Ch]
    L_004047a9:
        mov ebx,dword ptr [esp+1Ch]
    L_004047ad:
        mov dword ptr [ebp+8],ebx
    L_004047b0:
        fld dword ptr [eax]
    L_004047b2:
        fadd dword ptr [esi+0Ch]
    L_004047b5:
        pop ebp
    L_004047b6:
        fstp dword ptr [esp+1Ch]
    L_004047ba:
        fld dword ptr [esi+10h]
    L_004047bd:
        fadd dword ptr [eax+4]
    L_004047c0:
        fstp dword ptr [esp+20h]
    L_004047c4:
        fld dword ptr [esi+14h]
    L_004047c7:
        mov esi,dword ptr [esp+1Ch]
    L_004047cb:
        fadd dword ptr [eax+8]
    L_004047ce:
        mov dword ptr [eax],esi
    L_004047d0:
        mov esi,dword ptr [esp+20h]
    L_004047d4:
        mov dword ptr [eax+4],esi
    L_004047d7:
        fstp dword ptr [esp+24h]
    L_004047db:
        mov esi,dword ptr [esp+24h]
    L_004047df:
        mov dword ptr [eax+8],esi
    L_004047e2:
        mov eax,edi
    L_004047e4:
        mov dword ptr [eax],ecx
    L_004047e6:
        mov dword ptr [eax+4],edx
    L_004047e9:
        pop esi
    L_004047ea:
        mov dword ptr [eax+8],ebx
    L_004047ed:
        pop ebx
    L_004047ee:
        add esp,44h
    L_004047f1:
        ret
    L_004047f2:
        cmp eax,8
    L_004047f5:
        fild dword ptr [esp+0Ch]
    L_004047f9:
        jne asm_target_00404915
    L_004047ff:
        fdivr dword ptr [esi+38h]
    L_00404802:
        mov ecx,edi
    L_00404804:
        fld st(0)
    L_00404806:
        fadd st,st(1)
    L_00404808:
        fld st(1)
    L_0040480a:
        fsub dword ptr [data_00470afc]
    L_00404810:
        fstp dword ptr [esp+8]
    L_00404814:
        fld dword ptr [data_00470afc]
    L_0040481a:
        fadd st,st(1)
    L_0040481c:
        fmul dword ptr [esp+8]
    L_00404820:
        fmul dword ptr [esp+8]
    L_00404824:
        fstp dword ptr [esp+0Ch]
    L_00404828:
        fsubr dword ptr [data_00470bd4]
    L_0040482e:
        fmul st,st(1)
    L_00404830:
        fmul st,st(1)
    L_00404832:
        fld dword ptr [data_00470afc]
    L_00404838:
        fsub st,st(2)
    L_0040483a:
        fld st(0)
    L_0040483c:
        fmulp st(1),st
    L_0040483e:
        fmul st,st(2)
    L_00404840:
        fld dword ptr [esp+8]
    L_00404844:
        fmul st,st(3)
    L_00404846:
        fmul st,st(3)
    L_00404848:
        fld st(0)
    L_0040484a:
        fmul dword ptr [esi+24h]
    L_0040484d:
        fstp dword ptr [esp+10h]
    L_00404851:
        fld st(0)
    L_00404853:
        fmul dword ptr [esi+28h]
    L_00404856:
        fstp dword ptr [esp+14h]
    L_0040485a:
        fmul dword ptr [esi+2Ch]
    L_0040485d:
        fstp dword ptr [esp+18h]
    L_00404861:
        fld st(0)
    L_00404863:
        fmul dword ptr [esi+18h]
    L_00404866:
        fstp dword ptr [esp+1Ch]
    L_0040486a:
        fld st(0)
    L_0040486c:
        fmul dword ptr [esi+1Ch]
    L_0040486f:
        fstp dword ptr [esp+20h]
    L_00404873:
        fmul dword ptr [esi+20h]
    L_00404876:
        fstp dword ptr [esp+24h]
    L_0040487a:
        fld st(0)
    L_0040487c:
        fmul dword ptr [esi+0Ch]
    L_0040487f:
        fstp dword ptr [esp+28h]
    L_00404883:
        fld st(0)
    L_00404885:
        fmul dword ptr [esi+10h]
    L_00404888:
        fstp dword ptr [esp+2Ch]
    L_0040488c:
        fmul dword ptr [esi+14h]
    L_0040488f:
        fstp st(1)
    L_00404891:
        fld dword ptr [esp+0Ch]
    L_00404895:
        fmul dword ptr [esi]
    L_00404897:
        fld dword ptr [esp+0Ch]
    L_0040489b:
        fmul dword ptr [esi+4]
    L_0040489e:
        fld dword ptr [esp+0Ch]
    L_004048a2:
        fmul dword ptr [esi+8]
    L_004048a5:
        fstp dword ptr [esp+48h]
    L_004048a9:
        fxch
    L_004048ab:
        fadd dword ptr [esp+28h]
    L_004048af:
        fstp dword ptr [esp+34h]
    L_004048b3:
        fadd dword ptr [esp+2Ch]
    L_004048b7:
        fld dword ptr [esp+48h]
    L_004048bb:
        fadd st,st(2)
    L_004048bd:
        fstp dword ptr [esp+3Ch]
    L_004048c1:
        fld dword ptr [esp+34h]
    L_004048c5:
        fadd dword ptr [esp+1Ch]
    L_004048c9:
        fstp dword ptr [esp+40h]
    L_004048cd:
        fadd dword ptr [esp+20h]
    L_004048d1:
        fstp st(1)
    L_004048d3:
        fld dword ptr [esp+3Ch]
    L_004048d7:
        fadd dword ptr [esp+24h]
    L_004048db:
        fld dword ptr [esp+40h]
    L_004048df:
        fadd dword ptr [esp+10h]
    L_004048e3:
        fstp dword ptr [esp+1Ch]
    L_004048e7:
        mov edx,dword ptr [esp+1Ch]
    L_004048eb:
        fxch
    L_004048ed:
        mov dword ptr [ecx],edx
    L_004048ef:
        fadd dword ptr [esp+14h]
    L_004048f3:
        fstp dword ptr [esp+20h]
    L_004048f7:
        mov eax,dword ptr [esp+20h]
    L_004048fb:
        fadd dword ptr [esp+18h]
    L_004048ff:
        fstp dword ptr [esp+24h]
    L_00404903:
        mov edx,dword ptr [esp+24h]
    L_00404907:
        mov dword ptr [ecx+4],eax
    L_0040490a:
        pop esi
    L_0040490b:
        mov dword ptr [ecx+8],edx
    L_0040490e:
        mov eax,edi
    L_00404910:
        pop ebx
    L_00404911:
        add esp,44h
    L_00404914:
        ret
    L_00404915:
        push ecx
    L_00404916:
        mov ecx,dword ptr [esi+38h]
    L_00404919:
        fstp dword ptr [esp]
    L_0040491c:
        push ecx
    L_0040491d:
        call asm_FUN_0044c350_0044c350
    L_00404922:
        fld dword ptr [esi+0Ch]
    L_00404925:
        fsub dword ptr [esi]
    L_00404927:
        mov edx,edi
    L_00404929:
        fld dword ptr [esi+10h]
    L_0040492c:
        fsub dword ptr [esi+4]
    L_0040492f:
        fld dword ptr [esi+14h]
    L_00404932:
        fsub dword ptr [esi+8]
    L_00404935:
        fstp dword ptr [esp+48h]
    L_00404939:
        fxch
    L_0040493b:
        fmul st,st(2)
    L_0040493d:
        fstp dword ptr [esp+34h]
    L_00404941:
        fmul st,st(1)
    L_00404943:
        fld dword ptr [esp+48h]
    L_00404947:
        fmul st,st(2)
    L_00404949:
        fstp dword ptr [esp+3Ch]
    L_0040494d:
        fld dword ptr [esp+34h]
    L_00404951:
        fadd dword ptr [esi]
    L_00404953:
        fstp dword ptr [esp+1Ch]
    L_00404957:
        mov eax,dword ptr [esp+1Ch]
    L_0040495b:
        fadd dword ptr [esi+4]
    L_0040495e:
        fstp dword ptr [esp+20h]
    L_00404962:
        mov ecx,dword ptr [esp+20h]
    L_00404966:
        fstp st(0)
    L_00404968:
        fld dword ptr [esp+3Ch]
    L_0040496c:
        fadd dword ptr [esi+8]
    L_0040496f:
        mov dword ptr [edx],eax
    L_00404971:
        mov dword ptr [edx+4],ecx
    L_00404974:
        pop esi
    L_00404975:
        fstp dword ptr [esp+20h]
    L_00404979:
        mov eax,dword ptr [esp+20h]
    L_0040497d:
        mov dword ptr [edx+8],eax
    L_00404980:
        mov eax,edi
    L_00404982:
        pop ebx
    L_00404983:
        add esp,44h
    L_00404986:
        ret
    }
}

// 0x00412AC0..0x00412D4B: FUN_00412ac0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00412ac0_00412ac0() {
    __asm {
    L_00412ac0:
        sub esp,20h
    L_00412ac3:
        mov eax,dword ptr [esi+34h]
    L_00412ac6:
        test eax,eax
    L_00412ac8:
        mov dword ptr [esp],eax
    L_00412acb:
        jle asm_target_00412b90
    L_00412ad1:
        mov edx,dword ptr [esi+24h]
    L_00412ad4:
        mov ecx,dword ptr [esi+2Ch]
    L_00412ad7:
        mov dword ptr [esi+20h],edx
    L_00412ada:
        fld dword ptr [ecx]
    L_00412adc:
        fcomp dword ptr [data_00470b68]
    L_00412ae2:
        fnstsw ax
    L_00412ae4:
        test ah,41h
    L_00412ae7:
        jne short L_00412b0a
    L_00412ae9:
        fld dword ptr [ecx]
    L_00412aeb:
        fcomp dword ptr [data_00470b64]
    L_00412af1:
        fnstsw ax
    L_00412af3:
        test ah,5
    L_00412af6:
        jp short L_00412b0a
    L_00412af8:
        fld dword ptr [esi+28h]
    L_00412afb:
        inc edx
    L_00412afc:
        fadd dword ptr [data_00470afc]
    L_00412b02:
        mov dword ptr [esi+24h],edx
    L_00412b05:
        fstp dword ptr [esi+28h]
    L_00412b08:
        jmp short L_00412b1a
    L_00412b0a:
        fld dword ptr [ecx]
    L_00412b0c:
        fadd dword ptr [esi+28h]
    L_00412b0f:
        fst dword ptr [esi+28h]
    L_00412b12:
        call asm_FUN_00463b2c_00463b2c
    L_00412b17:
        mov dword ptr [esi+24h],eax
    L_00412b1a:
        mov ecx,dword ptr [esi+34h]
    L_00412b1d:
        cmp dword ptr [esi+24h],ecx
    L_00412b20:
        mov dword ptr [esp],ecx
    L_00412b23:
        jl short L_00412b90
    L_00412b25:
        mov eax,dword ptr [esi+30h]
    L_00412b28:
        test al,1
    L_00412b2a:
        mov dword ptr [esp+8],ecx
    L_00412b2e:
        jne short L_00412b52
    L_00412b30:
        or eax,1
    L_00412b33:
        mov dword ptr [esi+24h],0
    L_00412b3a:
        mov dword ptr [esi+20h],0FFF0BDC1h
    L_00412b41:
        mov dword ptr [esi+28h],0
    L_00412b48:
        mov dword ptr [esi+2Ch],476F78h
    L_00412b4f:
        mov dword ptr [esi+30h],eax
    L_00412b52:
        fild dword ptr [esp+8]
    L_00412b56:
        mov dword ptr [esi+24h],ecx
    L_00412b59:
        dec ecx
    L_00412b5a:
        mov dword ptr [esi+20h],ecx
    L_00412b5d:
        fstp dword ptr [esi+28h]
    L_00412b60:
        mov eax,dword ptr [esi+38h]
    L_00412b63:
        cmp eax,7
    L_00412b66:
        mov dword ptr [esi+34h],0
    L_00412b6d:
        je short L_00412b80
    L_00412b6f:
        mov eax,dword ptr [esi+8]
    L_00412b72:
        mov dword ptr [edi],eax
    L_00412b74:
        mov ecx,dword ptr [esi+0Ch]
    L_00412b77:
        mov dword ptr [edi+4],ecx
    L_00412b7a:
        mov eax,edi
    L_00412b7c:
        add esp,20h
    L_00412b7f:
        ret
    L_00412b80:
        mov edx,dword ptr [esi]
    L_00412b82:
        mov dword ptr [edi],edx
    L_00412b84:
        mov eax,dword ptr [esi+4]
    L_00412b87:
        mov dword ptr [edi+4],eax
    L_00412b8a:
        mov eax,edi
    L_00412b8c:
        add esp,20h
    L_00412b8f:
        ret
    L_00412b90:
        mov eax,dword ptr [esi+38h]
    L_00412b93:
        cmp eax,7
    L_00412b96:
        jne short L_00412bd1
    L_00412b98:
        mov ecx,dword ptr [esi]
    L_00412b9a:
        mov edx,dword ptr [esi+4]
    L_00412b9d:
        mov dword ptr [esp+8],ecx
    L_00412ba1:
        fld dword ptr [esp+8]
    L_00412ba5:
        fadd dword ptr [esi+8]
    L_00412ba8:
        mov dword ptr [esp+0Ch],edx
    L_00412bac:
        fstp dword ptr [esp]
    L_00412baf:
        mov eax,dword ptr [esp]
    L_00412bb2:
        fld dword ptr [esp+0Ch]
    L_00412bb6:
        fadd dword ptr [esi+0Ch]
    L_00412bb9:
        mov dword ptr [esi],eax
    L_00412bbb:
        fstp dword ptr [esp+4]
    L_00412bbf:
        mov ecx,dword ptr [esp+4]
    L_00412bc3:
        mov dword ptr [esi+4],ecx
    L_00412bc6:
        mov dword ptr [edi],eax
    L_00412bc8:
        mov dword ptr [edi+4],ecx
    L_00412bcb:
        mov eax,edi
    L_00412bcd:
        add esp,20h
    L_00412bd0:
        ret
    L_00412bd1:
        cmp eax,11h
    L_00412bd4:
        jne short L_00412c31
    L_00412bd6:
        mov eax,dword ptr [esi]
    L_00412bd8:
        mov ecx,dword ptr [esi+4]
    L_00412bdb:
        mov dword ptr [esp+8],eax
    L_00412bdf:
        fld dword ptr [esp+8]
    L_00412be3:
        fadd dword ptr [esi+18h]
    L_00412be6:
        mov dword ptr [esp+0Ch],ecx
    L_00412bea:
        fstp dword ptr [esp]
    L_00412bed:
        mov eax,dword ptr [esp]
    L_00412bf0:
        fld dword ptr [esp+0Ch]
    L_00412bf4:
        fadd dword ptr [esi+1Ch]
    L_00412bf7:
        mov dword ptr [esi],eax
    L_00412bf9:
        fstp dword ptr [esp+4]
    L_00412bfd:
        mov ecx,dword ptr [esp+4]
    L_00412c01:
        mov dword ptr [esi+4],ecx
    L_00412c04:
        fld dword ptr [esi+18h]
    L_00412c07:
        fadd dword ptr [esi+8]
    L_00412c0a:
        fstp dword ptr [esp+8]
    L_00412c0e:
        mov edx,dword ptr [esp+8]
    L_00412c12:
        fld dword ptr [esi+0Ch]
    L_00412c15:
        fadd dword ptr [esi+1Ch]
    L_00412c18:
        mov dword ptr [esi+18h],edx
    L_00412c1b:
        fstp dword ptr [esp+0Ch]
    L_00412c1f:
        mov edx,dword ptr [esp+0Ch]
    L_00412c23:
        mov dword ptr [esi+1Ch],edx
    L_00412c26:
        mov dword ptr [edi],eax
    L_00412c28:
        mov dword ptr [edi+4],ecx
    L_00412c2b:
        mov eax,edi
    L_00412c2d:
        add esp,20h
    L_00412c30:
        ret
    L_00412c31:
        cmp eax,8
    L_00412c34:
        fild dword ptr [esp]
    L_00412c37:
        jne asm_target_00412cfe
    L_00412c3d:
        fdivr dword ptr [esi+28h]
    L_00412c40:
        fld st(0)
    L_00412c42:
        fadd st,st(1)
    L_00412c44:
        fld st(1)
    L_00412c46:
        fsub dword ptr [data_00470afc]
    L_00412c4c:
        fstp dword ptr [esp]
    L_00412c4f:
        fld dword ptr [data_00470afc]
    L_00412c55:
        fadd st,st(1)
    L_00412c57:
        fmul dword ptr [esp]
    L_00412c5a:
        fmul dword ptr [esp]
    L_00412c5d:
        fstp dword ptr [esp+8]
    L_00412c61:
        fsubr dword ptr [data_00470bd4]
    L_00412c67:
        fmul st,st(1)
    L_00412c69:
        fmul st,st(1)
    L_00412c6b:
        fld dword ptr [data_00470afc]
    L_00412c71:
        fsub st,st(2)
    L_00412c73:
        fld st(0)
    L_00412c75:
        fmulp st(1),st
    L_00412c77:
        fmul st,st(2)
    L_00412c79:
        fld dword ptr [esp]
    L_00412c7c:
        fmul st,st(3)
    L_00412c7e:
        fmul st,st(3)
    L_00412c80:
        fld st(0)
    L_00412c82:
        fmul dword ptr [esi+18h]
    L_00412c85:
        fstp dword ptr [esp+10h]
    L_00412c89:
        fmul dword ptr [esi+1Ch]
    L_00412c8c:
        fstp dword ptr [esp+14h]
    L_00412c90:
        fld st(0)
    L_00412c92:
        fmul dword ptr [esi+10h]
    L_00412c95:
        fstp dword ptr [esp]
    L_00412c98:
        fmul dword ptr [esi+14h]
    L_00412c9b:
        fstp dword ptr [esp+4]
    L_00412c9f:
        fld st(0)
    L_00412ca1:
        fmul dword ptr [esi+8]
    L_00412ca4:
        fstp dword ptr [esp+18h]
    L_00412ca8:
        fmul dword ptr [esi+0Ch]
    L_00412cab:
        fstp st(1)
    L_00412cad:
        fld dword ptr [esp+8]
    L_00412cb1:
        fmul dword ptr [esi]
    L_00412cb3:
        fld dword ptr [esp+8]
    L_00412cb7:
        fmul dword ptr [esi+4]
    L_00412cba:
        fstp dword ptr [esp+0Ch]
    L_00412cbe:
        fadd dword ptr [esp+18h]
    L_00412cc2:
        fld dword ptr [esp+0Ch]
    L_00412cc6:
        fadd st,st(2)
    L_00412cc8:
        fstp dword ptr [esp+1Ch]
    L_00412ccc:
        fadd dword ptr [esp]
    L_00412ccf:
        fstp st(1)
    L_00412cd1:
        fld dword ptr [esp+1Ch]
    L_00412cd5:
        fadd dword ptr [esp+4]
    L_00412cd9:
        fxch
    L_00412cdb:
        fadd dword ptr [esp+10h]
    L_00412cdf:
        fstp dword ptr [esp+8]
    L_00412ce3:
        mov eax,dword ptr [esp+8]
    L_00412ce7:
        mov dword ptr [edi],eax
    L_00412ce9:
        fadd dword ptr [esp+14h]
    L_00412ced:
        mov eax,edi
    L_00412cef:
        fstp dword ptr [esp+0Ch]
    L_00412cf3:
        mov ecx,dword ptr [esp+0Ch]
    L_00412cf7:
        mov dword ptr [edi+4],ecx
    L_00412cfa:
        add esp,20h
    L_00412cfd:
        ret
    L_00412cfe:
        mov edx,dword ptr [esi+28h]
    L_00412d01:
        push ecx
    L_00412d02:
        fstp dword ptr [esp]
    L_00412d05:
        push edx
    L_00412d06:
        call asm_FUN_0044c350_0044c350
    L_00412d0b:
        fld dword ptr [esi+8]
    L_00412d0e:
        fsub dword ptr [esi]
    L_00412d10:
        fld dword ptr [esi+0Ch]
    L_00412d13:
        fsub dword ptr [esi+4]
    L_00412d16:
        fstp dword ptr [esp+1Ch]
    L_00412d1a:
        fmul st,st(1)
    L_00412d1c:
        fld dword ptr [esp+1Ch]
    L_00412d20:
        fmul st,st(2)
    L_00412d22:
        fstp dword ptr [esp+1Ch]
    L_00412d26:
        fadd dword ptr [esi]
    L_00412d28:
        fstp dword ptr [esp+10h]
    L_00412d2c:
        mov eax,dword ptr [esp+10h]
    L_00412d30:
        fstp st(0)
    L_00412d32:
        fld dword ptr [esp+1Ch]
    L_00412d36:
        fadd dword ptr [esi+4]
    L_00412d39:
        mov dword ptr [edi],eax
    L_00412d3b:
        mov eax,edi
    L_00412d3d:
        fstp dword ptr [esp+14h]
    L_00412d41:
        mov ecx,dword ptr [esp+14h]
    L_00412d45:
        mov dword ptr [edi+4],ecx
    L_00412d48:
        add esp,20h
    L_00412d4b:
        ret
    }
}

// 0x0044C350..0x0044C54C: FUN_0044c350
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0044c350_0044c350() {
    __asm {
    L_0044c350:
        fld dword ptr [esp+4]
    L_0044c354:
        dec eax
    L_0044c355:
        cmp eax,0Fh
    L_0044c358:
        fdiv dword ptr [esp+8]
    L_0044c35c:
        ja asm_target_0044c54a
    L_0044c362:
        jmp dword ptr [eax*4+44C550h]
    L_0044c369:
        fld st(0)
    L_0044c36b:
        fmulp st(1),st
    L_0044c36d:
        ret 8
    L_0044c370:
        fsubr dword ptr [data_00470afc]
    L_0044c376:
        fld st(0)
    L_0044c378:
        fmulp st(1),st
    L_0044c37a:
        fsubr dword ptr [data_00470afc]
    L_0044c380:
        ret 8
    L_0044c383:
        fld st(0)
    L_0044c385:
        fmul st,st(1)
    L_0044c387:
        fmulp st(1),st
    L_0044c389:
        ret 8
    L_0044c38c:
        fsubr dword ptr [data_00470afc]
    L_0044c392:
        fld st(0)
    L_0044c394:
        fld st(0)
    L_0044c396:
        fmul st,st(1)
    L_0044c398:
        fmulp st(2),st
    L_0044c39a:
        fxch
    L_0044c39c:
        fsubr dword ptr [data_00470afc]
    L_0044c3a2:
        fstp st(1)
    L_0044c3a4:
        ret 8
    L_0044c3a7:
        fld st(0)
    L_0044c3a9:
        fmul st,st(1)
    L_0044c3ab:
        fmul st,st(1)
    L_0044c3ad:
        fmulp st(1),st
    L_0044c3af:
        ret 8
    L_0044c3b2:
        fsubr dword ptr [data_00470afc]
    L_0044c3b8:
        fld st(0)
    L_0044c3ba:
        fld st(0)
    L_0044c3bc:
        fmul st,st(1)
    L_0044c3be:
        fmul st,st(2)
    L_0044c3c0:
        fmulp st(2),st
    L_0044c3c2:
        fxch
    L_0044c3c4:
        fsubr dword ptr [data_00470afc]
    L_0044c3ca:
        fstp st(1)
    L_0044c3cc:
        ret 8
    L_0044c3cf:
        fadd st(0),st
    L_0044c3d1:
        fcom dword ptr [data_00470afc]
    L_0044c3d7:
        fnstsw ax
    L_0044c3d9:
        test ah,5
    L_0044c3dc:
        jp short L_0044c3eb
    L_0044c3de:
        fld st(0)
    L_0044c3e0:
        fmulp st(1),st
    L_0044c3e2:
        fmul dword ptr [data_00470b0c]
    L_0044c3e8:
        ret 8
    L_0044c3eb:
        fsubr dword ptr [data_00470b08]
    L_0044c3f1:
        fld st(0)
    L_0044c3f3:
        fmulp st(1),st
    L_0044c3f5:
        fsubr dword ptr [data_00470b08]
    L_0044c3fb:
        fmul dword ptr [data_00470b0c]
    L_0044c401:
        ret 8
    L_0044c404:
        fadd st(0),st
    L_0044c406:
        fcom dword ptr [data_00470afc]
    L_0044c40c:
        fnstsw ax
    L_0044c40e:
        test ah,5
    L_0044c411:
        jp short L_0044c42c
    L_0044c413:
        fsubr dword ptr [data_00470afc]
    L_0044c419:
        fld st(0)
    L_0044c41b:
        fmulp st(1),st
    L_0044c41d:
        fmul dword ptr [data_00470b0c]
    L_0044c423:
        fsubr dword ptr [data_00470b0c]
    L_0044c429:
        ret 8
    L_0044c42c:
        fsub dword ptr [data_00470afc]
    L_0044c432:
        fld st(0)
    L_0044c434:
        fmulp st(1),st
    L_0044c436:
        fmul dword ptr [data_00470b0c]
    L_0044c43c:
        fadd dword ptr [data_00470b0c]
    L_0044c442:
        ret 8
    L_0044c445:
        fadd st(0),st
    L_0044c447:
        fcom dword ptr [data_00470afc]
    L_0044c44d:
        fnstsw ax
    L_0044c44f:
        test ah,5
    L_0044c452:
        jp short L_0044c463
    L_0044c454:
        fld st(0)
    L_0044c456:
        fmul st,st(1)
    L_0044c458:
        fmulp st(1),st
    L_0044c45a:
        fmul dword ptr [data_00470b0c]
    L_0044c460:
        ret 8
    L_0044c463:
        fsubr dword ptr [data_00470b08]
    L_0044c469:
        fld st(0)
    L_0044c46b:
        fld st(0)
    L_0044c46d:
        fmul st,st(1)
    L_0044c46f:
        jmp short L_0044c4cd
    L_0044c471:
        fadd st(0),st
    L_0044c473:
        fcom dword ptr [data_00470afc]
    L_0044c479:
        fnstsw ax
    L_0044c47b:
        test ah,5
    L_0044c47e:
        jp short L_0044c48e
    L_0044c480:
        fsubr dword ptr [data_00470afc]
    L_0044c486:
        fld st(0)
    L_0044c488:
        fld st(0)
    L_0044c48a:
        fmul st,st(1)
    L_0044c48c:
        jmp short L_0044c4ff
    L_0044c48e:
        fsub dword ptr [data_00470afc]
    L_0044c494:
        fld st(0)
    L_0044c496:
        fld st(0)
    L_0044c498:
        fmul st,st(1)
    L_0044c49a:
        jmp asm_target_0044c522
    L_0044c49f:
        fadd st(0),st
    L_0044c4a1:
        fcom dword ptr [data_00470afc]
    L_0044c4a7:
        fnstsw ax
    L_0044c4a9:
        test ah,5
    L_0044c4ac:
        jp short L_0044c4bf
    L_0044c4ae:
        fld st(0)
    L_0044c4b0:
        fmul st,st(1)
    L_0044c4b2:
        fmul st,st(1)
    L_0044c4b4:
        fmulp st(1),st
    L_0044c4b6:
        fmul dword ptr [data_00470b0c]
    L_0044c4bc:
        ret 8
    L_0044c4bf:
        fsubr dword ptr [data_00470b08]
    L_0044c4c5:
        fld st(0)
    L_0044c4c7:
        fld st(0)
    L_0044c4c9:
        fmul st,st(1)
    L_0044c4cb:
        fmul st,st(2)
    L_0044c4cd:
        fmulp st(2),st
    L_0044c4cf:
        fxch
    L_0044c4d1:
        fsubr dword ptr [data_00470b08]
    L_0044c4d7:
        fmul dword ptr [data_00470b0c]
    L_0044c4dd:
        fstp st(1)
    L_0044c4df:
        ret 8
    L_0044c4e2:
        fadd st(0),st
    L_0044c4e4:
        fcom dword ptr [data_00470afc]
    L_0044c4ea:
        fnstsw ax
    L_0044c4ec:
        test ah,5
    L_0044c4ef:
        jp short L_0044c514
    L_0044c4f1:
        fsubr dword ptr [data_00470afc]
    L_0044c4f7:
        fld st(0)
    L_0044c4f9:
        fld st(0)
    L_0044c4fb:
        fmul st,st(1)
    L_0044c4fd:
        fmul st,st(2)
    L_0044c4ff:
        fmulp st(2),st
    L_0044c501:
        fxch
    L_0044c503:
        fmul dword ptr [data_00470b0c]
    L_0044c509:
        fsubr dword ptr [data_00470b0c]
    L_0044c50f:
        fstp st(1)
    L_0044c511:
        ret 8
    L_0044c514:
        fsub dword ptr [data_00470afc]
    L_0044c51a:
        fld st(0)
    L_0044c51c:
        fld st(0)
    L_0044c51e:
        fmul st,st(1)
    L_0044c520:
        fmul st,st(2)
    L_0044c522:
        fmulp st(2),st
    L_0044c524:
        fxch
    L_0044c526:
        fmul dword ptr [data_00470b0c]
    L_0044c52c:
        fadd dword ptr [data_00470b0c]
    L_0044c532:
        fstp st(1)
    L_0044c534:
        ret 8
    L_0044c537:
        fstp st(0)
    L_0044c539:
        fld dword ptr [data_00470b04]
    L_0044c53f:
        ret 8
    L_0044c542:
        fstp st(0)
    L_0044c544:
        fld dword ptr [data_00470afc]
    L_0044c54a:
        ret 8
    }
}
