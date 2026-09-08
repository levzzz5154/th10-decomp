#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00419650..0x0041988A: FUN_00419650
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00419650_00419650() {
    __asm {
    L_00419650:
        mov eax,dword ptr [ebx+0D8h]
    L_00419656:
        mov ecx,dword ptr [data_00474c84]
    L_0041965c:
        sub esp,10h
    L_0041965f:
        cmp eax,ecx
    L_00419661:
        je short L_0041966a
    L_00419663:
        mov dword ptr [ebx+14h],0
    L_0041966a:
        mov eax,dword ptr [data_00474c7c]
    L_0041966f:
        push ebp
    L_00419670:
        push esi
    L_00419671:
        push edi
    L_00419672:
        push 1
    L_00419674:
        lea ecx,[eax+eax*2]
    L_00419677:
        mov eax,dword ptr [ebx+ecx*4+1Ch]
    L_0041967b:
        push ebx
    L_0041967c:
        call asm_FUN_00419120_00419120
    L_00419681:
        mov eax,dword ptr [data_00477834]
    L_00419686:
        fld dword ptr [eax+3C0h]
    L_0041968c:
        lea edi,[ebx+17Ch]
    L_00419692:
        fadd dword ptr [data_00470b4c]
    L_00419698:
        lea ebp,[ebx+108h]
    L_0041969e:
        fld dword ptr [eax+3C4h]
    L_004196a4:
        mov dword ptr [esp+18h],0Ah
    L_004196ac:
        fadd dword ptr [data_00470b48]
    L_004196b2:
        mov ecx,dword ptr [edi-0A0h]
    L_004196b8:
        test ecx,ecx
    L_004196ba:
        jne short L_004196c0
    L_004196bc:
        xor esi,esi
    L_004196be:
        jmp short L_004196fe
    L_004196c0:
        mov edx,dword ptr [data_00491c10]
    L_004196c6:
        mov eax,dword ptr [edx+72DAD4h]
    L_004196cc:
        test eax,eax
    L_004196ce:
        je short L_004196dd
    L_004196d0:
        mov esi,dword ptr [eax]
    L_004196d2:
        cmp dword ptr [esi],ecx
    L_004196d4:
        je short L_004196f8
    L_004196d6:
        mov eax,dword ptr [eax+4]
    L_004196d9:
        test eax,eax
    L_004196db:
        jne short L_004196d0
    L_004196dd:
        mov eax,dword ptr [edx+72DADCh]
    L_004196e3:
        test eax,eax
    L_004196e5:
        je short L_004196bc
    L_004196e7:
        mov edx,dword ptr [eax]
    L_004196e9:
        cmp dword ptr [edx],ecx
    L_004196eb:
        je short L_004196f8
    L_004196ed:
        mov eax,dword ptr [eax+4]
    L_004196f0:
        test eax,eax
    L_004196f2:
        jne short L_004196e7
    L_004196f4:
        xor esi,esi
    L_004196f6:
        jmp short L_004196fe
    L_004196f8:
        mov esi,dword ptr [eax]
    L_004196fa:
        test esi,esi
    L_004196fc:
        jne short L_00419710
    L_004196fe:
        test esi,esi
    L_00419700:
        mov dword ptr [edi-0A0h],0
    L_0041970a:
        je asm_target_00419858
    L_00419710:
        mov eax,dword ptr [esi+12Ch]
    L_00419716:
        test eax,eax
    L_00419718:
        jne asm_target_00419858
    L_0041971e:
        fld st(1)
    L_00419720:
        fsub dword ptr [ebp-4]
    L_00419723:
        fabs
    L_00419725:
        fld st(1)
    L_00419727:
        fsub dword ptr [ebp]
    L_0041972a:
        fabs
    L_0041972c:
        fstp dword ptr [esp+0Ch]
    L_00419730:
        fld dword ptr [edi]
    L_00419732:
        fmul dword ptr [data_00470b0c]
    L_00419738:
        fstp dword ptr [esp+10h]
    L_0041973c:
        fcom dword ptr [esp+10h]
    L_00419740:
        fnstsw ax
    L_00419742:
        test ah,5
    L_00419745:
        jp short L_00419774
    L_00419747:
        fld dword ptr [esi+50h]
    L_0041974a:
        fmul dword ptr [esi+40h]
    L_0041974d:
        fmul dword ptr [data_00470b0c]
    L_00419753:
        fcomp dword ptr [esp+0Ch]
    L_00419757:
        fnstsw ax
    L_00419759:
        test ah,41h
    L_0041975c:
        jne short L_00419774
    L_0041975e:
        mov al,byte ptr [esi+310h]
    L_00419764:
        fstp st(0)
    L_00419766:
        shr al,2
    L_00419769:
        mov byte ptr [esi+2FFh],al
    L_0041976f:
        jmp asm_target_00419858
    L_00419774:
        fld dword ptr [esp+10h]
    L_00419778:
        fadd dword ptr [data_00470bcc]
    L_0041977e:
        fstp dword ptr [esp+14h]
    L_00419782:
        fcom dword ptr [esp+14h]
    L_00419786:
        fnstsw ax
    L_00419788:
        test ah,5
    L_0041978b:
        jp short L_004197e3
    L_0041978d:
        fld dword ptr [esi+50h]
    L_00419790:
        fmul dword ptr [esi+40h]
    L_00419793:
        fmul dword ptr [data_00470b0c]
    L_00419799:
        fcomp dword ptr [esp+0Ch]
    L_0041979d:
        fnstsw ax
    L_0041979f:
        test ah,41h
    L_004197a2:
        jne short L_004197e3
    L_004197a4:
        mov eax,dword ptr [esi+310h]
    L_004197aa:
        mov dword ptr [esp+10h],eax
    L_004197ae:
        fild dword ptr [esp+10h]
    L_004197b2:
        lea eax,[eax+eax*2]
    L_004197b5:
        fld dword ptr [esp+14h]
    L_004197b9:
        cdq
    L_004197ba:
        and edx,3
    L_004197bd:
        fsub st,st(2)
    L_004197bf:
        add eax,edx
    L_004197c1:
        sar eax,2
    L_004197c4:
        mov dword ptr [esp+14h],eax
    L_004197c8:
        fimul dword ptr [esp+14h]
    L_004197cc:
        fmul dword ptr [data_00470d20]
    L_004197d2:
        fsubp st(1),st
    L_004197d4:
        call asm_FUN_00463b2c_00463b2c
    L_004197d9:
        fstp st(0)
    L_004197db:
        mov byte ptr [esi+2FFh],al
    L_004197e1:
        jmp short L_00419858
    L_004197e3:
        fcomp dword ptr [esp+10h]
    L_004197e7:
        fnstsw ax
    L_004197e9:
        test ah,5
    L_004197ec:
        jp short L_0041984c
    L_004197ee:
        fld dword ptr [esi+50h]
    L_004197f1:
        fmul dword ptr [esi+40h]
    L_004197f4:
        fmul dword ptr [data_00470b0c]
    L_004197fa:
        fadd dword ptr [data_00470bcc]
    L_00419800:
        fld dword ptr [esp+0Ch]
    L_00419804:
        fcomp
    L_00419806:
        fnstsw ax
    L_00419808:
        test ah,5
    L_0041980b:
        jp short L_0041984a
    L_0041980d:
        mov eax,dword ptr [esi+310h]
    L_00419813:
        mov dword ptr [esp+10h],eax
    L_00419817:
        fild dword ptr [esp+10h]
    L_0041981b:
        lea eax,[eax+eax*2]
    L_0041981e:
        cdq
    L_0041981f:
        fxch
    L_00419821:
        fsub dword ptr [esp+0Ch]
    L_00419825:
        and edx,3
    L_00419828:
        add eax,edx
    L_0041982a:
        sar eax,2
    L_0041982d:
        mov dword ptr [esp+14h],eax
    L_00419831:
        fimul dword ptr [esp+14h]
    L_00419835:
        fmul dword ptr [data_00470d20]
    L_0041983b:
        fsubp st(1),st
    L_0041983d:
        call asm_FUN_00463b2c_00463b2c
    L_00419842:
        mov byte ptr [esi+2FFh],al
    L_00419848:
        jmp short L_00419858
    L_0041984a:
        fstp st(0)
    L_0041984c:
        mov cl,byte ptr [esi+310h]
    L_00419852:
        mov byte ptr [esi+2FFh],cl
    L_00419858:
        mov eax,dword ptr [esp+18h]
    L_0041985c:
        add edi,4
    L_0041985f:
        add ebp,0Ch
    L_00419862:
        dec eax
    L_00419863:
        mov dword ptr [esp+18h],eax
    L_00419867:
        jne asm_target_004196b2
    L_0041986d:
        mov ecx,dword ptr [ebx+10h]
    L_00419870:
        fstp st(0)
    L_00419872:
        mov eax,dword ptr [ebx+14h]
    L_00419875:
        fstp st(0)
    L_00419877:
        inc ecx
    L_00419878:
        pop edi
    L_00419879:
        inc eax
    L_0041987a:
        pop esi
    L_0041987b:
        mov dword ptr [ebx+14h],eax
    L_0041987e:
        mov dword ptr [ebx+10h],ecx
    L_00419881:
        mov eax,1
    L_00419886:
        pop ebp
    L_00419887:
        add esp,10h
    L_0041988a:
        ret
    }
}
