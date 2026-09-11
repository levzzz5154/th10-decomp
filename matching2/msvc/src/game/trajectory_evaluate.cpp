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


