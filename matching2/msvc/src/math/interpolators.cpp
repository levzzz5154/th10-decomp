#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00441600..0x00441933: FUN_00441600
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00441600_00441600() {
    __asm {
    L_00441600:
        sub esp,48h
    L_00441603:
        push ebx
    L_00441604:
        push ebp
    L_00441605:
        mov ebp,dword ptr [esp+54h]
    L_00441609:
        mov ebx,eax
    L_0044160b:
        mov eax,dword ptr [ebx+44h]
    L_0044160e:
        push esi
    L_0044160f:
        xor esi,esi
    L_00441611:
        cmp eax,esi
    L_00441613:
        mov dword ptr [esp+58h],eax
    L_00441617:
        jle asm_target_004416eb
    L_0044161d:
        mov edx,dword ptr [ebx+34h]
    L_00441620:
        mov ecx,dword ptr [ebx+3Ch]
    L_00441623:
        mov dword ptr [ebx+30h],edx
    L_00441626:
        fld dword ptr [ecx]
    L_00441628:
        fcomp dword ptr [data_00470b68]
    L_0044162e:
        fnstsw ax
    L_00441630:
        test ah,41h
    L_00441633:
        jne short L_00441656
    L_00441635:
        fld dword ptr [ecx]
    L_00441637:
        fcomp dword ptr [data_00470b64]
    L_0044163d:
        fnstsw ax
    L_0044163f:
        test ah,5
    L_00441642:
        jp short L_00441656
    L_00441644:
        fld dword ptr [ebx+38h]
    L_00441647:
        inc edx
    L_00441648:
        fadd dword ptr [data_00470afc]
    L_0044164e:
        mov dword ptr [ebx+34h],edx
    L_00441651:
        fstp dword ptr [ebx+38h]
    L_00441654:
        jmp short L_00441666
    L_00441656:
        fld dword ptr [ecx]
    L_00441658:
        fadd dword ptr [ebx+38h]
    L_0044165b:
        fst dword ptr [ebx+38h]
    L_0044165e:
        call asm_FUN_00463b2c_00463b2c
    L_00441663:
        mov dword ptr [ebx+34h],eax
    L_00441666:
        mov ecx,dword ptr [ebx+44h]
    L_00441669:
        cmp dword ptr [ebx+34h],ecx
    L_0044166c:
        mov dword ptr [esp+58h],ecx
    L_00441670:
        jl short L_004416eb
    L_00441672:
        mov eax,dword ptr [ebx+40h]
    L_00441675:
        test al,1
    L_00441677:
        mov dword ptr [esp+58h],ecx
    L_0044167b:
        jne short L_00441697
    L_0044167d:
        or eax,1
    L_00441680:
        mov dword ptr [ebx+34h],esi
    L_00441683:
        mov dword ptr [ebx+30h],0FFF0BDC1h
    L_0044168a:
        mov dword ptr [ebx+38h],esi
    L_0044168d:
        mov dword ptr [ebx+3Ch],476F78h
    L_00441694:
        mov dword ptr [ebx+40h],eax
    L_00441697:
        fild dword ptr [esp+58h]
    L_0044169b:
        mov dword ptr [ebx+34h],ecx
    L_0044169e:
        dec ecx
    L_0044169f:
        mov dword ptr [ebx+30h],ecx
    L_004416a2:
        fstp dword ptr [ebx+38h]
    L_004416a5:
        mov eax,dword ptr [ebx+48h]
    L_004416a8:
        cmp eax,7
    L_004416ab:
        mov dword ptr [ebx+44h],esi
    L_004416ae:
        je short L_004416ce
    L_004416b0:
        add ebx,0Ch
    L_004416b3:
        mov ecx,dword ptr [ebx]
    L_004416b5:
        mov eax,ebp
    L_004416b7:
        mov dword ptr [eax],ecx
    L_004416b9:
        mov edx,dword ptr [ebx+4]
    L_004416bc:
        pop esi
    L_004416bd:
        mov dword ptr [eax+4],edx
    L_004416c0:
        mov ecx,dword ptr [ebx+8]
    L_004416c3:
        pop ebp
    L_004416c4:
        mov dword ptr [eax+8],ecx
    L_004416c7:
        pop ebx
    L_004416c8:
        add esp,48h
    L_004416cb:
        ret 4
    L_004416ce:
        mov eax,dword ptr [ebx]
    L_004416d0:
        mov edx,ebp
    L_004416d2:
        mov dword ptr [edx],eax
    L_004416d4:
        mov ecx,dword ptr [ebx+4]
    L_004416d7:
        mov dword ptr [edx+4],ecx
    L_004416da:
        mov eax,dword ptr [ebx+8]
    L_004416dd:
        pop esi
    L_004416de:
        mov dword ptr [edx+8],eax
    L_004416e1:
        mov eax,ebp
    L_004416e3:
        pop ebp
    L_004416e4:
        pop ebx
    L_004416e5:
        add esp,48h
    L_004416e8:
        ret 4
    L_004416eb:
        mov eax,dword ptr [ebx+48h]
    L_004416ee:
        cmp eax,7
    L_004416f1:
        jne short L_00441729
    L_004416f3:
        mov eax,ebx
    L_004416f5:
        mov ecx,dword ptr [eax]
    L_004416f7:
        mov edx,dword ptr [eax+4]
    L_004416fa:
        mov esi,dword ptr [eax+8]
    L_004416fd:
        mov eax,dword ptr [ebx+0Ch]
    L_00441700:
        add eax,ecx
    L_00441702:
        mov ecx,dword ptr [ebx+10h]
    L_00441705:
        add ecx,edx
    L_00441707:
        mov edx,dword ptr [ebx+14h]
    L_0044170a:
        mov dword ptr [ebx],eax
    L_0044170c:
        add edx,esi
    L_0044170e:
        mov dword ptr [ebx+4],ecx
    L_00441711:
        mov dword ptr [ebx+8],edx
    L_00441714:
        mov esi,ebp
    L_00441716:
        mov dword ptr [esi],eax
    L_00441718:
        mov dword ptr [esi+4],ecx
    L_0044171b:
        mov dword ptr [esi+8],edx
    L_0044171e:
        pop esi
    L_0044171f:
        mov eax,ebp
    L_00441721:
        pop ebp
    L_00441722:
        pop ebx
    L_00441723:
        add esp,48h
    L_00441726:
        ret 4
    L_00441729:
        cmp eax,11h
    L_0044172c:
        push edi
    L_0044172d:
        jne short L_00441791
    L_0044172f:
        lea eax,[ebx+24h]
    L_00441732:
        mov ecx,ebx
    L_00441734:
        mov edx,dword ptr [ecx]
    L_00441736:
        mov esi,dword ptr [ecx+4]
    L_00441739:
        mov edi,dword ptr [ecx+8]
    L_0044173c:
        mov ecx,dword ptr [eax]
    L_0044173e:
        add ecx,edx
    L_00441740:
        mov edx,dword ptr [eax+4]
    L_00441743:
        add edx,esi
    L_00441745:
        mov esi,dword ptr [eax+8]
    L_00441748:
        add esi,edi
    L_0044174a:
        mov edi,ebx
    L_0044174c:
        mov dword ptr [edi],ecx
    L_0044174e:
        mov dword ptr [edi+4],edx
    L_00441751:
        mov dword ptr [edi+8],esi
    L_00441754:
        mov edi,dword ptr [eax]
    L_00441756:
        add edi,dword ptr [ebx+0Ch]
    L_00441759:
        mov dword ptr [esp+28h],edi
    L_0044175d:
        mov edi,dword ptr [ebx+10h]
    L_00441760:
        add edi,dword ptr [eax+4]
    L_00441763:
        mov ebx,dword ptr [ebx+14h]
    L_00441766:
        add ebx,dword ptr [eax+8]
    L_00441769:
        mov dword ptr [esp+30h],ebx
    L_0044176d:
        mov ebx,dword ptr [esp+28h]
    L_00441771:
        mov dword ptr [eax],ebx
    L_00441773:
        mov dword ptr [eax+4],edi
    L_00441776:
        mov edi,dword ptr [esp+30h]
    L_0044177a:
        mov dword ptr [eax+8],edi
    L_0044177d:
        mov eax,ebp
    L_0044177f:
        mov dword ptr [eax],ecx
    L_00441781:
        pop edi
    L_00441782:
        mov dword ptr [eax+4],edx
    L_00441785:
        mov dword ptr [eax+8],esi
    L_00441788:
        pop esi
    L_00441789:
        pop ebp
    L_0044178a:
        pop ebx
    L_0044178b:
        add esp,48h
    L_0044178e:
        ret 4
    L_00441791:
        cmp eax,8
    L_00441794:
        fild dword ptr [esp+5Ch]
    L_00441798:
        push ecx
    L_00441799:
        jne asm_target_004418b4
    L_0044179f:
        fdivr dword ptr [ebx+38h]
    L_004417a2:
        lea edi,[ebx+0Ch]
    L_004417a5:
        lea esi,[esp+38h]
    L_004417a9:
        fst dword ptr [esp+60h]
    L_004417ad:
        fadd st(0),st
    L_004417af:
        fstp dword ptr [esp+18h]
    L_004417b3:
        fld dword ptr [data_00470bd4]
    L_004417b9:
        fsub dword ptr [esp+18h]
    L_004417bd:
        fmul dword ptr [esp+60h]
    L_004417c1:
        fmul dword ptr [esp+60h]
    L_004417c5:
        fstp dword ptr [esp]
    L_004417c8:
        call asm_RandomVector_StoreRoundedScalar_00441e50
    L_004417cd:
        fld dword ptr [esp+5Ch]
    L_004417d1:
        push ecx
    L_004417d2:
        fsub dword ptr [data_00470afc]
    L_004417d8:
        lea esi,[esp+44h]
    L_004417dc:
        mov edi,ebx
    L_004417de:
        mov dword ptr [esp+1Ch],eax
    L_004417e2:
        fstp dword ptr [esp+14h]
    L_004417e6:
        fld dword ptr [esp+18h]
    L_004417ea:
        fadd dword ptr [data_00470afc]
    L_004417f0:
        fmul dword ptr [esp+14h]
    L_004417f4:
        fmul dword ptr [esp+14h]
    L_004417f8:
        fstp dword ptr [esp]
    L_004417fb:
        call asm_RandomVector_StoreRoundedScalar_00441e50
    L_00441800:
        mov edx,dword ptr [eax]
    L_00441802:
        fld dword ptr [data_00470afc]
    L_00441808:
        mov ecx,dword ptr [esp+18h]
    L_0044180c:
        fsub dword ptr [esp+5Ch]
    L_00441810:
        add edx,dword ptr [ecx]
    L_00441812:
        mov dword ptr [esp+1Ch],edx
    L_00441816:
        fld st(0)
    L_00441818:
        mov edx,dword ptr [ecx+4]
    L_0044181b:
        fmul st,st(1)
    L_0044181d:
        add edx,dword ptr [eax+4]
    L_00441820:
        fmul dword ptr [esp+5Ch]
    L_00441824:
        mov dword ptr [esp+20h],edx
    L_00441828:
        mov ecx,dword ptr [ecx+8]
    L_0044182b:
        add ecx,dword ptr [eax+8]
    L_0044182e:
        push ecx
    L_0044182f:
        fstp dword ptr [esp]
    L_00441832:
        lea edi,[ebx+18h]
    L_00441835:
        lea esi,[esp+50h]
    L_00441839:
        mov dword ptr [esp+28h],ecx
    L_0044183d:
        fstp st(0)
    L_0044183f:
        call asm_RandomVector_StoreRoundedScalar_00441e50
    L_00441844:
        fld dword ptr [esp+10h]
    L_00441848:
        mov ecx,dword ptr [eax]
    L_0044184a:
        fmul dword ptr [esp+5Ch]
    L_0044184e:
        mov esi,dword ptr [esp+1Ch]
    L_00441852:
        mov edx,dword ptr [esp+20h]
    L_00441856:
        fmul dword ptr [esp+5Ch]
    L_0044185a:
        add ecx,esi
    L_0044185c:
        mov dword ptr [esp+28h],ecx
    L_00441860:
        mov ecx,dword ptr [eax+4]
    L_00441863:
        mov eax,dword ptr [eax+8]
    L_00441866:
        add ecx,edx
    L_00441868:
        mov dword ptr [esp+2Ch],ecx
    L_0044186c:
        add eax,dword ptr [esp+24h]
    L_00441870:
        push ecx
    L_00441871:
        lea edi,[ebx+24h]
    L_00441874:
        fstp dword ptr [esp]
    L_00441877:
        lea esi,[esp+20h]
    L_0044187b:
        mov dword ptr [esp+34h],eax
    L_0044187f:
        call asm_RandomVector_StoreRoundedScalar_00441e50
    L_00441884:
        mov ecx,dword ptr [eax]
    L_00441886:
        mov edx,dword ptr [eax+4]
    L_00441889:
        mov ebx,dword ptr [esp+28h]
    L_0044188d:
        mov edi,dword ptr [esp+2Ch]
    L_00441891:
        mov esi,dword ptr [esp+30h]
    L_00441895:
        mov eax,dword ptr [eax+8]
    L_00441898:
        add ecx,ebx
    L_0044189a:
        add edx,edi
    L_0044189c:
        add eax,esi
    L_0044189e:
        mov esi,ebp
    L_004418a0:
        mov dword ptr [esi],ecx
    L_004418a2:
        mov dword ptr [esi+4],edx
    L_004418a5:
        pop edi
    L_004418a6:
        mov dword ptr [esi+8],eax
    L_004418a9:
        pop esi
    L_004418aa:
        mov eax,ebp
    L_004418ac:
        pop ebp
    L_004418ad:
        pop ebx
    L_004418ae:
        add esp,48h
    L_004418b1:
        ret 4
    L_004418b4:
        mov ecx,dword ptr [ebx+38h]
    L_004418b7:
        fstp dword ptr [esp]
    L_004418ba:
        push ecx
    L_004418bb:
        call asm_FUN_0044c350_0044c350
    L_004418c0:
        mov esi,dword ptr [ebx]
    L_004418c2:
        mov edx,dword ptr [ebx+0Ch]
    L_004418c5:
        mov edi,dword ptr [ebx+4]
    L_004418c8:
        mov eax,dword ptr [ebx+10h]
    L_004418cb:
        mov ecx,dword ptr [ebx+14h]
    L_004418ce:
        sub edx,esi
    L_004418d0:
        mov dword ptr [esp+28h],edx
    L_004418d4:
        fild dword ptr [esp+28h]
    L_004418d8:
        sub eax,edi
    L_004418da:
        mov dword ptr [esp+2Ch],eax
    L_004418de:
        mov eax,dword ptr [ebx+8]
    L_004418e1:
        fmul st,st(1)
    L_004418e3:
        sub ecx,eax
    L_004418e5:
        mov dword ptr [esp+5Ch],eax
    L_004418e9:
        mov dword ptr [esp+30h],ecx
    L_004418ed:
        call asm_FUN_00463b2c_00463b2c
    L_004418f2:
        fild dword ptr [esp+2Ch]
    L_004418f6:
        mov ebx,eax
    L_004418f8:
        fmul st,st(1)
    L_004418fa:
        call asm_FUN_00463b2c_00463b2c
    L_004418ff:
        fild dword ptr [esp+30h]
    L_00441903:
        mov dword ptr [esp+20h],eax
    L_00441907:
        fmul st,st(1)
    L_00441909:
        call asm_FUN_00463b2c_00463b2c
    L_0044190e:
        fstp st(0)
    L_00441910:
        mov edx,dword ptr [esp+20h]
    L_00441914:
        mov ecx,dword ptr [esp+5Ch]
    L_00441918:
        add edi,edx
    L_0044191a:
        add esi,ebx
    L_0044191c:
        mov edx,ebp
    L_0044191e:
        mov dword ptr [edx],esi
    L_00441920:
        mov dword ptr [edx+4],edi
    L_00441923:
        pop edi
    L_00441924:
        add eax,ecx
    L_00441926:
        pop esi
    L_00441927:
        mov dword ptr [edx+8],eax
    L_0044192a:
        mov eax,ebp
    L_0044192c:
        pop ebp
    L_0044192d:
        pop ebx
    L_0044192e:
        add esp,48h
    L_00441931:
        ret 4
    }
}

// 0x00441950..0x00441AC1: FUN_00441950
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00441950_00441950() {
    __asm {
    L_00441950:
        sub esp,8
    L_00441953:
        mov eax,dword ptr [esi+24h]
    L_00441956:
        test eax,eax
    L_00441958:
        mov dword ptr [esp],eax
    L_0044195b:
        jle asm_target_00441a04
    L_00441961:
        mov edx,dword ptr [esi+14h]
    L_00441964:
        mov ecx,dword ptr [esi+1Ch]
    L_00441967:
        mov dword ptr [esi+10h],edx
    L_0044196a:
        fld dword ptr [ecx]
    L_0044196c:
        fcomp dword ptr [data_00470b68]
    L_00441972:
        fnstsw ax
    L_00441974:
        test ah,41h
    L_00441977:
        jne short L_0044199a
    L_00441979:
        fld dword ptr [ecx]
    L_0044197b:
        fcomp dword ptr [data_00470b64]
    L_00441981:
        fnstsw ax
    L_00441983:
        test ah,5
    L_00441986:
        jp short L_0044199a
    L_00441988:
        fld dword ptr [esi+18h]
    L_0044198b:
        inc edx
    L_0044198c:
        fadd dword ptr [data_00470afc]
    L_00441992:
        mov dword ptr [esi+14h],edx
    L_00441995:
        fstp dword ptr [esi+18h]
    L_00441998:
        jmp short L_004419aa
    L_0044199a:
        fld dword ptr [ecx]
    L_0044199c:
        fadd dword ptr [esi+18h]
    L_0044199f:
        fst dword ptr [esi+18h]
    L_004419a2:
        call asm_FUN_00463b2c_00463b2c
    L_004419a7:
        mov dword ptr [esi+14h],eax
    L_004419aa:
        mov ecx,dword ptr [esi+24h]
    L_004419ad:
        cmp dword ptr [esi+14h],ecx
    L_004419b0:
        mov dword ptr [esp],ecx
    L_004419b3:
        jl short L_00441a04
    L_004419b5:
        mov eax,dword ptr [esi+20h]
    L_004419b8:
        test al,1
    L_004419ba:
        mov dword ptr [esp],ecx
    L_004419bd:
        jne short L_004419e1
    L_004419bf:
        or eax,1
    L_004419c2:
        mov dword ptr [esi+14h],0
    L_004419c9:
        mov dword ptr [esi+10h],0FFF0BDC1h
    L_004419d0:
        mov dword ptr [esi+18h],0
    L_004419d7:
        mov dword ptr [esi+1Ch],476F78h
    L_004419de:
        mov dword ptr [esi+20h],eax
    L_004419e1:
        fild dword ptr [esp]
    L_004419e4:
        mov dword ptr [esi+14h],ecx
    L_004419e7:
        dec ecx
    L_004419e8:
        mov dword ptr [esi+10h],ecx
    L_004419eb:
        fstp dword ptr [esi+18h]
    L_004419ee:
        mov eax,dword ptr [esi+28h]
    L_004419f1:
        cmp eax,7
    L_004419f4:
        mov dword ptr [esi+24h],0
    L_004419fb:
        je short L_00441a15
    L_004419fd:
        mov eax,dword ptr [esi+4]
    L_00441a00:
        add esp,8
    L_00441a03:
        ret
    L_00441a04:
        mov eax,dword ptr [esi+28h]
    L_00441a07:
        cmp eax,7
    L_00441a0a:
        jne short L_00441a1b
    L_00441a0c:
        mov ecx,dword ptr [esi]
    L_00441a0e:
        mov eax,dword ptr [esi+4]
    L_00441a11:
        add ecx,eax
    L_00441a13:
        mov dword ptr [esi],ecx
    L_00441a15:
        mov eax,dword ptr [esi]
    L_00441a17:
        add esp,8
    L_00441a1a:
        ret
    L_00441a1b:
        cmp eax,11h
    L_00441a1e:
        jne short L_00441a33
    L_00441a20:
        mov eax,dword ptr [esi+0Ch]
    L_00441a23:
        add dword ptr [esi],eax
    L_00441a25:
        mov ecx,dword ptr [esi+4]
    L_00441a28:
        add ecx,eax
    L_00441a2a:
        mov eax,dword ptr [esi]
    L_00441a2c:
        mov dword ptr [esi+0Ch],ecx
    L_00441a2f:
        add esp,8
    L_00441a32:
        ret
    L_00441a33:
        cmp eax,8
    L_00441a36:
        fild dword ptr [esp]
    L_00441a39:
        jne short L_00441a98
    L_00441a3b:
        fdivr dword ptr [esi+18h]
    L_00441a3e:
        fld st(0)
    L_00441a40:
        fadd st,st(1)
    L_00441a42:
        fld st(1)
    L_00441a44:
        fsub dword ptr [data_00470afc]
    L_00441a4a:
        fld dword ptr [data_00470afc]
    L_00441a50:
        fsub st,st(3)
    L_00441a52:
        fld dword ptr [data_00470bd4]
    L_00441a58:
        fsub st,st(3)
    L_00441a5a:
        fmul st,st(4)
    L_00441a5c:
        fmul st,st(4)
    L_00441a5e:
        fimul dword ptr [esi+4]
    L_00441a61:
        fld st(2)
    L_00441a63:
        fmul st,st(5)
    L_00441a65:
        fmul st,st(5)
    L_00441a67:
        fimul dword ptr [esi+0Ch]
    L_00441a6a:
        faddp st(1),st
    L_00441a6c:
        fld st(1)
    L_00441a6e:
        fmul st,st(2)
    L_00441a70:
        fmul st,st(5)
    L_00441a72:
        fimul dword ptr [esi+8]
    L_00441a75:
        faddp st(1),st
    L_00441a77:
        fxch st(3)
    L_00441a79:
        fadd dword ptr [data_00470afc]
    L_00441a7f:
        fmul st,st(2)
    L_00441a81:
        fmul st,st(2)
    L_00441a83:
        fimul dword ptr [esi]
    L_00441a85:
        faddp st(3),st
    L_00441a87:
        fxch st(2)
    L_00441a89:
        call asm_FUN_00463b2c_00463b2c
    L_00441a8e:
        fstp st(1)
    L_00441a90:
        fstp st(0)
    L_00441a92:
        fstp st(0)
    L_00441a94:
        add esp,8
    L_00441a97:
        ret
    L_00441a98:
        mov ecx,dword ptr [esi]
    L_00441a9a:
        mov edx,dword ptr [esi+18h]
    L_00441a9d:
        push ecx
    L_00441a9e:
        fstp dword ptr [esp]
    L_00441aa1:
        push edx
    L_00441aa2:
        mov dword ptr [esp+0Ch],ecx
    L_00441aa6:
        call asm_FUN_0044c350_0044c350
    L_00441aab:
        mov eax,dword ptr [esi+4]
    L_00441aae:
        sub eax,ecx
    L_00441ab0:
        mov dword ptr [esp],eax
    L_00441ab3:
        fimul dword ptr [esp]
    L_00441ab6:
        fiadd dword ptr [esp+4]
    L_00441aba:
        add esp,8
    L_00441abd:
        jmp asm_FUN_00463b2c_00463b2c
    }
}

// 0x00441AD0..0x00441D5B: FUN_00441ad0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00441ad0_00441ad0() {
    __asm {
    L_00441ad0:
        sub esp,20h
    L_00441ad3:
        mov eax,dword ptr [esi+34h]
    L_00441ad6:
        test eax,eax
    L_00441ad8:
        mov dword ptr [esp],eax
    L_00441adb:
        jle asm_target_00441ba0
    L_00441ae1:
        mov edx,dword ptr [esi+24h]
    L_00441ae4:
        mov ecx,dword ptr [esi+2Ch]
    L_00441ae7:
        mov dword ptr [esi+20h],edx
    L_00441aea:
        fld dword ptr [ecx]
    L_00441aec:
        fcomp dword ptr [data_00470b68]
    L_00441af2:
        fnstsw ax
    L_00441af4:
        test ah,41h
    L_00441af7:
        jne short L_00441b1a
    L_00441af9:
        fld dword ptr [ecx]
    L_00441afb:
        fcomp dword ptr [data_00470b64]
    L_00441b01:
        fnstsw ax
    L_00441b03:
        test ah,5
    L_00441b06:
        jp short L_00441b1a
    L_00441b08:
        fld dword ptr [esi+28h]
    L_00441b0b:
        inc edx
    L_00441b0c:
        fadd dword ptr [data_00470afc]
    L_00441b12:
        mov dword ptr [esi+24h],edx
    L_00441b15:
        fstp dword ptr [esi+28h]
    L_00441b18:
        jmp short L_00441b2a
    L_00441b1a:
        fld dword ptr [ecx]
    L_00441b1c:
        fadd dword ptr [esi+28h]
    L_00441b1f:
        fst dword ptr [esi+28h]
    L_00441b22:
        call asm_FUN_00463b2c_00463b2c
    L_00441b27:
        mov dword ptr [esi+24h],eax
    L_00441b2a:
        mov ecx,dword ptr [esi+34h]
    L_00441b2d:
        cmp dword ptr [esi+24h],ecx
    L_00441b30:
        mov dword ptr [esp],ecx
    L_00441b33:
        jl short L_00441ba0
    L_00441b35:
        mov eax,dword ptr [esi+30h]
    L_00441b38:
        test al,1
    L_00441b3a:
        mov dword ptr [esp+8],ecx
    L_00441b3e:
        jne short L_00441b62
    L_00441b40:
        or eax,1
    L_00441b43:
        mov dword ptr [esi+24h],0
    L_00441b4a:
        mov dword ptr [esi+20h],0FFF0BDC1h
    L_00441b51:
        mov dword ptr [esi+28h],0
    L_00441b58:
        mov dword ptr [esi+2Ch],476F78h
    L_00441b5f:
        mov dword ptr [esi+30h],eax
    L_00441b62:
        fild dword ptr [esp+8]
    L_00441b66:
        mov dword ptr [esi+24h],ecx
    L_00441b69:
        dec ecx
    L_00441b6a:
        mov dword ptr [esi+20h],ecx
    L_00441b6d:
        fstp dword ptr [esi+28h]
    L_00441b70:
        mov eax,dword ptr [esi+38h]
    L_00441b73:
        cmp eax,7
    L_00441b76:
        mov dword ptr [esi+34h],0
    L_00441b7d:
        je short L_00441b90
    L_00441b7f:
        mov eax,dword ptr [esi+8]
    L_00441b82:
        mov dword ptr [edi],eax
    L_00441b84:
        mov ecx,dword ptr [esi+0Ch]
    L_00441b87:
        mov dword ptr [edi+4],ecx
    L_00441b8a:
        mov eax,edi
    L_00441b8c:
        add esp,20h
    L_00441b8f:
        ret
    L_00441b90:
        mov edx,dword ptr [esi]
    L_00441b92:
        mov dword ptr [edi],edx
    L_00441b94:
        mov eax,dword ptr [esi+4]
    L_00441b97:
        mov dword ptr [edi+4],eax
    L_00441b9a:
        mov eax,edi
    L_00441b9c:
        add esp,20h
    L_00441b9f:
        ret
    L_00441ba0:
        mov eax,dword ptr [esi+38h]
    L_00441ba3:
        cmp eax,7
    L_00441ba6:
        jne short L_00441be1
    L_00441ba8:
        mov ecx,dword ptr [esi]
    L_00441baa:
        mov edx,dword ptr [esi+4]
    L_00441bad:
        mov dword ptr [esp+8],ecx
    L_00441bb1:
        fld dword ptr [esp+8]
    L_00441bb5:
        fadd dword ptr [esi+8]
    L_00441bb8:
        mov dword ptr [esp+0Ch],edx
    L_00441bbc:
        fstp dword ptr [esp]
    L_00441bbf:
        mov eax,dword ptr [esp]
    L_00441bc2:
        fld dword ptr [esp+0Ch]
    L_00441bc6:
        fadd dword ptr [esi+0Ch]
    L_00441bc9:
        mov dword ptr [esi],eax
    L_00441bcb:
        fstp dword ptr [esp+4]
    L_00441bcf:
        mov ecx,dword ptr [esp+4]
    L_00441bd3:
        mov dword ptr [esi+4],ecx
    L_00441bd6:
        mov dword ptr [edi],eax
    L_00441bd8:
        mov dword ptr [edi+4],ecx
    L_00441bdb:
        mov eax,edi
    L_00441bdd:
        add esp,20h
    L_00441be0:
        ret
    L_00441be1:
        cmp eax,11h
    L_00441be4:
        jne short L_00441c41
    L_00441be6:
        mov eax,dword ptr [esi]
    L_00441be8:
        mov ecx,dword ptr [esi+4]
    L_00441beb:
        mov dword ptr [esp+8],eax
    L_00441bef:
        fld dword ptr [esp+8]
    L_00441bf3:
        fadd dword ptr [esi+18h]
    L_00441bf6:
        mov dword ptr [esp+0Ch],ecx
    L_00441bfa:
        fstp dword ptr [esp]
    L_00441bfd:
        mov eax,dword ptr [esp]
    L_00441c00:
        fld dword ptr [esp+0Ch]
    L_00441c04:
        fadd dword ptr [esi+1Ch]
    L_00441c07:
        mov dword ptr [esi],eax
    L_00441c09:
        fstp dword ptr [esp+4]
    L_00441c0d:
        mov ecx,dword ptr [esp+4]
    L_00441c11:
        mov dword ptr [esi+4],ecx
    L_00441c14:
        fld dword ptr [esi+18h]
    L_00441c17:
        fadd dword ptr [esi+8]
    L_00441c1a:
        fstp dword ptr [esp+8]
    L_00441c1e:
        mov edx,dword ptr [esp+8]
    L_00441c22:
        fld dword ptr [esi+0Ch]
    L_00441c25:
        fadd dword ptr [esi+1Ch]
    L_00441c28:
        mov dword ptr [esi+18h],edx
    L_00441c2b:
        fstp dword ptr [esp+0Ch]
    L_00441c2f:
        mov edx,dword ptr [esp+0Ch]
    L_00441c33:
        mov dword ptr [esi+1Ch],edx
    L_00441c36:
        mov dword ptr [edi],eax
    L_00441c38:
        mov dword ptr [edi+4],ecx
    L_00441c3b:
        mov eax,edi
    L_00441c3d:
        add esp,20h
    L_00441c40:
        ret
    L_00441c41:
        cmp eax,8
    L_00441c44:
        fild dword ptr [esp]
    L_00441c47:
        jne asm_target_00441d0e
    L_00441c4d:
        fdivr dword ptr [esi+28h]
    L_00441c50:
        fld st(0)
    L_00441c52:
        fadd st,st(1)
    L_00441c54:
        fld st(1)
    L_00441c56:
        fsub dword ptr [data_00470afc]
    L_00441c5c:
        fstp dword ptr [esp]
    L_00441c5f:
        fld dword ptr [data_00470afc]
    L_00441c65:
        fadd st,st(1)
    L_00441c67:
        fmul dword ptr [esp]
    L_00441c6a:
        fmul dword ptr [esp]
    L_00441c6d:
        fstp dword ptr [esp+8]
    L_00441c71:
        fsubr dword ptr [data_00470bd4]
    L_00441c77:
        fmul st,st(1)
    L_00441c79:
        fmul st,st(1)
    L_00441c7b:
        fld dword ptr [data_00470afc]
    L_00441c81:
        fsub st,st(2)
    L_00441c83:
        fld st(0)
    L_00441c85:
        fmulp st(1),st
    L_00441c87:
        fmul st,st(2)
    L_00441c89:
        fld dword ptr [esp]
    L_00441c8c:
        fmul st,st(3)
    L_00441c8e:
        fmul st,st(3)
    L_00441c90:
        fld st(0)
    L_00441c92:
        fmul dword ptr [esi+18h]
    L_00441c95:
        fstp dword ptr [esp+10h]
    L_00441c99:
        fmul dword ptr [esi+1Ch]
    L_00441c9c:
        fstp dword ptr [esp+14h]
    L_00441ca0:
        fld st(0)
    L_00441ca2:
        fmul dword ptr [esi+10h]
    L_00441ca5:
        fstp dword ptr [esp]
    L_00441ca8:
        fmul dword ptr [esi+14h]
    L_00441cab:
        fstp dword ptr [esp+4]
    L_00441caf:
        fld st(0)
    L_00441cb1:
        fmul dword ptr [esi+8]
    L_00441cb4:
        fstp dword ptr [esp+18h]
    L_00441cb8:
        fmul dword ptr [esi+0Ch]
    L_00441cbb:
        fstp st(1)
    L_00441cbd:
        fld dword ptr [esp+8]
    L_00441cc1:
        fmul dword ptr [esi]
    L_00441cc3:
        fld dword ptr [esp+8]
    L_00441cc7:
        fmul dword ptr [esi+4]
    L_00441cca:
        fstp dword ptr [esp+0Ch]
    L_00441cce:
        fadd dword ptr [esp+18h]
    L_00441cd2:
        fld dword ptr [esp+0Ch]
    L_00441cd6:
        fadd st,st(2)
    L_00441cd8:
        fstp dword ptr [esp+1Ch]
    L_00441cdc:
        fadd dword ptr [esp]
    L_00441cdf:
        fstp st(1)
    L_00441ce1:
        fld dword ptr [esp+1Ch]
    L_00441ce5:
        fadd dword ptr [esp+4]
    L_00441ce9:
        fxch
    L_00441ceb:
        fadd dword ptr [esp+10h]
    L_00441cef:
        fstp dword ptr [esp+8]
    L_00441cf3:
        mov eax,dword ptr [esp+8]
    L_00441cf7:
        mov dword ptr [edi],eax
    L_00441cf9:
        fadd dword ptr [esp+14h]
    L_00441cfd:
        mov eax,edi
    L_00441cff:
        fstp dword ptr [esp+0Ch]
    L_00441d03:
        mov ecx,dword ptr [esp+0Ch]
    L_00441d07:
        mov dword ptr [edi+4],ecx
    L_00441d0a:
        add esp,20h
    L_00441d0d:
        ret
    L_00441d0e:
        mov edx,dword ptr [esi+28h]
    L_00441d11:
        push ecx
    L_00441d12:
        fstp dword ptr [esp]
    L_00441d15:
        push edx
    L_00441d16:
        call asm_FUN_0044c350_0044c350
    L_00441d1b:
        fld dword ptr [esi+8]
    L_00441d1e:
        fsub dword ptr [esi]
    L_00441d20:
        fld dword ptr [esi+0Ch]
    L_00441d23:
        fsub dword ptr [esi+4]
    L_00441d26:
        fstp dword ptr [esp+1Ch]
    L_00441d2a:
        fmul st,st(1)
    L_00441d2c:
        fld dword ptr [esp+1Ch]
    L_00441d30:
        fmul st,st(2)
    L_00441d32:
        fstp dword ptr [esp+1Ch]
    L_00441d36:
        fadd dword ptr [esi]
    L_00441d38:
        fstp dword ptr [esp+10h]
    L_00441d3c:
        mov eax,dword ptr [esp+10h]
    L_00441d40:
        fstp st(0)
    L_00441d42:
        fld dword ptr [esp+1Ch]
    L_00441d46:
        fadd dword ptr [esi+4]
    L_00441d49:
        mov dword ptr [edi],eax
    L_00441d4b:
        mov eax,edi
    L_00441d4d:
        fstp dword ptr [esp+14h]
    L_00441d51:
        mov ecx,dword ptr [esp+14h]
    L_00441d55:
        mov dword ptr [edi+4],ecx
    L_00441d58:
        add esp,20h
    L_00441d5b:
        ret
    }
}
