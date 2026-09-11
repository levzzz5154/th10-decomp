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


