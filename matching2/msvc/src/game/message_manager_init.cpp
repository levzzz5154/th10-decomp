#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040B560..0x0040B7A7: FUN_0040b560
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040b560_0040b560() {
    __asm {
    L_0040b560:
        mov eax,dword ptr fs:[0]
    L_0040b566:
        push 0FFFFFFFFh
    L_0040b568:
        push 4657BBh
    L_0040b56d:
        push eax
    L_0040b56e:
        mov dword ptr fs:[0],esp
    L_0040b575:
        sub esp,0Ch
    L_0040b578:
        push ebx
    L_0040b579:
        push ebp
    L_0040b57a:
        mov ebp,dword ptr [esp+24h]
    L_0040b57e:
        push esi
    L_0040b57f:
        push 24h
    L_0040b581:
        call asm_operator_new_00452493
    L_0040b586:
        xor ebx,ebx
    L_0040b588:
        add esp,4
    L_0040b58b:
        cmp eax,ebx
    L_0040b58d:
        je short L_0040b5b0
    L_0040b58f:
        mov ecx,dword ptr [eax+4]
    L_0040b592:
        mov dword ptr [eax+8],ebx
    L_0040b595:
        mov dword ptr [eax+0Ch],ebx
    L_0040b598:
        mov dword ptr [eax+10h],ebx
    L_0040b59b:
        mov dword ptr [eax],ebx
    L_0040b59d:
        and ecx,0FFFFFFFEh
    L_0040b5a0:
        mov dword ptr [eax+4],ecx
    L_0040b5a3:
        mov dword ptr [eax+14h],eax
    L_0040b5a6:
        mov dword ptr [eax+18h],ebx
    L_0040b5a9:
        mov dword ptr [eax+1Ch],ebx
    L_0040b5ac:
        mov esi,eax
    L_0040b5ae:
        jmp short L_0040b5b2
    L_0040b5b0:
        xor esi,esi
    L_0040b5b2:
        mov eax,dword ptr [esi+4]
    L_0040b5b5:
        or eax,3
    L_0040b5b8:
        push edi
    L_0040b5b9:
        mov dword ptr [esi+4],eax
    L_0040b5bc:
        mov eax,dword ptr [data_00491be4]
    L_0040b5c1:
        push eax
    L_0040b5c2:
        mov edi,1Ch
    L_0040b5c7:
        mov dword ptr [esi+8],40BA70h
    L_0040b5ce:
        mov dword ptr [esi+0Ch],ebx
    L_0040b5d1:
        mov dword ptr [esi+10h],ebx
    L_0040b5d4:
        mov dword ptr [esi+20h],ebp
    L_0040b5d7:
        call asm_Scheduler_RegisterPrimary_00449ae0
    L_0040b5dc:
        push 24h
    L_0040b5de:
        mov dword ptr [ebp+8],esi
    L_0040b5e1:
        call asm_operator_new_00452493
    L_0040b5e6:
        add esp,4
    L_0040b5e9:
        cmp eax,ebx
    L_0040b5eb:
        je short L_0040b60e
    L_0040b5ed:
        mov ecx,dword ptr [eax+4]
    L_0040b5f0:
        mov dword ptr [eax+8],ebx
    L_0040b5f3:
        mov dword ptr [eax+0Ch],ebx
    L_0040b5f6:
        mov dword ptr [eax+10h],ebx
    L_0040b5f9:
        mov dword ptr [eax],ebx
    L_0040b5fb:
        and ecx,0FFFFFFFEh
    L_0040b5fe:
        mov dword ptr [eax+4],ecx
    L_0040b601:
        mov dword ptr [eax+14h],eax
    L_0040b604:
        mov dword ptr [eax+18h],ebx
    L_0040b607:
        mov dword ptr [eax+1Ch],ebx
    L_0040b60a:
        mov esi,eax
    L_0040b60c:
        jmp short L_0040b610
    L_0040b60e:
        xor esi,esi
    L_0040b610:
        mov edi,dword ptr [esi+4]
    L_0040b613:
        mov ecx,dword ptr [data_00491be4]
    L_0040b619:
        or edi,3
    L_0040b61c:
        mov dword ptr [esi+4],edi
    L_0040b61f:
        push ecx
    L_0040b620:
        mov edi,6
    L_0040b625:
        mov dword ptr [esi+8],40BA80h
    L_0040b62c:
        mov dword ptr [esi+0Ch],ebx
    L_0040b62f:
        mov dword ptr [esi+10h],ebx
    L_0040b632:
        mov dword ptr [esi+20h],ebp
    L_0040b635:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_0040b63a:
        mov eax,dword ptr [data_004776e0]
    L_0040b63f:
        mov dword ptr [ebp+0Ch],esi
    L_0040b642:
        mov ecx,dword ptr [eax+89A4h]
    L_0040b648:
        cmp ecx,ebx
    L_0040b64a:
        lea esi,[eax+89A4h]
    L_0040b650:
        mov dword ptr [esp+10h],43F00000h
    L_0040b658:
        mov dword ptr [esp+14h],43C40000h
    L_0040b660:
        mov dword ptr [esp+18h],0
    L_0040b668:
        jne short L_0040b684
    L_0040b66a:
        mov eax,dword ptr [eax+8994h]
    L_0040b670:
        push edi
    L_0040b671:
        lea edx,[esp+30h]
    L_0040b675:
        push edx
    L_0040b676:
        push eax
    L_0040b677:
        lea edi,[esp+1Ch]
    L_0040b67b:
        call asm_AnimationManager_CreatePositionedPrimary_00448d50
    L_0040b680:
        mov eax,dword ptr [eax]
    L_0040b682:
        mov dword ptr [esi],eax
    L_0040b684:
        mov eax,dword ptr [data_00474c68]
    L_0040b689:
        mov ecx,dword ptr [data_00474c6c]
    L_0040b68f:
        lea edx,[ecx+eax*2]
    L_0040b692:
        add eax,edx
    L_0040b694:
        mov dword ptr [ebp+1Ch],eax
    L_0040b697:
        cmp dword ptr [data_00474c90],ebx
    L_0040b69d:
        mov ecx,1
    L_0040b6a2:
        jne short L_0040b6b2
    L_0040b6a4:
        cmp dword ptr [data_00474c74],ecx
    L_0040b6aa:
        jl short L_0040b6b2
    L_0040b6ac:
        add eax,6
    L_0040b6af:
        mov dword ptr [ebp+1Ch],eax
    L_0040b6b2:
        mov edx,dword ptr [ebp+1Ch]
    L_0040b6b5:
        mov eax,dword ptr [data_0047783c]
    L_0040b6ba:
        cmp byte ptr [edx+eax+1D882h],bl
    L_0040b6c1:
        jne short L_0040b6c6
    L_0040b6c3:
        or dword ptr [ebp+20h],ecx
    L_0040b6c6:
        cmp byte ptr [eax+1D88Eh],bl
    L_0040b6cc:
        jne short L_0040b6d2
    L_0040b6ce:
        or dword ptr [ebp+20h],2
    L_0040b6d2:
        mov edx,dword ptr [ebp+1Ch]
    L_0040b6d5:
        mov byte ptr [edx+eax+1D882h],cl
    L_0040b6dc:
        cmp dword ptr [ebp+1Ch],6
    L_0040b6e0:
        jl short L_0040b6e8
    L_0040b6e2:
        mov byte ptr [eax+1D88Eh],cl
    L_0040b6e8:
        mov eax,dword ptr [ebp+1Ch]
    L_0040b6eb:
        mov eax,dword ptr [eax*4+474440h]
    L_0040b6f2:
        mov byte ptr [data_00497c38],bl
    L_0040b6f8:
        mov esi,eax
    L_0040b6fa:
        lea ebx,[ebx+force_disp32_zero]
    L_0040b700:
        mov cl,byte ptr [eax]
    L_0040b702:
        inc eax
    L_0040b703:
        cmp cl,bl
    L_0040b705:
        jne short L_0040b700
    L_0040b707:
        mov edi,497C38h
    L_0040b70c:
        sub eax,esi
    L_0040b70e:
        dec edi
    L_0040b70f:
        nop
    L_0040b710:
        mov cl,byte ptr [edi+1]
    L_0040b713:
        inc edi
    L_0040b714:
        cmp cl,bl
    L_0040b716:
        jne short L_0040b710
    L_0040b718:
        mov ecx,eax
    L_0040b71a:
        shr ecx,2
    L_0040b71d:
        rep movsd
    L_0040b71f:
        mov ecx,eax
    L_0040b721:
        push ebx
    L_0040b722:
        and ecx,3
    L_0040b725:
        push ebx
    L_0040b726:
        mov eax,497C38h
    L_0040b72b:
        rep movsb
    L_0040b72d:
        call asm_FUN_0044b360_0044b360
    L_0040b732:
        cmp eax,ebx
    L_0040b734:
        mov dword ptr [ebp+14h],eax
    L_0040b737:
        pop edi
    L_0040b738:
        jne short L_0040b763
    L_0040b73a:
        push 46CB68h
    L_0040b73f:
        mov ecx,474F70h
    L_0040b744:
        call asm_TextLog_Append_0044b810
    L_0040b749:
        add esp,4
    L_0040b74c:
        pop esi
    L_0040b74d:
        pop ebp
    L_0040b74e:
        or eax,0FFFFFFFFh
    L_0040b751:
        pop ebx
    L_0040b752:
        mov ecx,dword ptr [esp+0Ch]
    L_0040b756:
        mov dword ptr fs:[0],ecx
    L_0040b75d:
        add esp,18h
    L_0040b760:
        ret 4
    L_0040b763:
        push 0ECh
    L_0040b768:
        call asm_operator_new_00452493
    L_0040b76d:
        add esp,4
    L_0040b770:
        mov dword ptr [esp+28h],eax
    L_0040b774:
        cmp eax,ebx
    L_0040b776:
        mov dword ptr [esp+20h],ebx
    L_0040b77a:
        je short L_0040b78d
    L_0040b77c:
        mov ecx,dword ptr [ebp+14h]
    L_0040b77f:
        mov edx,dword ptr [ecx+4]
    L_0040b782:
        add edx,ecx
    L_0040b784:
        push edx
    L_0040b785:
        push eax
    L_0040b786:
        call asm_FUN_0040ba90_0040ba90
    L_0040b78b:
        jmp short L_0040b78f
    L_0040b78d:
        xor eax,eax
    L_0040b78f:
        mov ecx,dword ptr [esp+18h]
    L_0040b793:
        mov dword ptr [ebp+18h],eax
    L_0040b796:
        pop esi
    L_0040b797:
        pop ebp
    L_0040b798:
        xor eax,eax
    L_0040b79a:
        pop ebx
    L_0040b79b:
        mov dword ptr fs:[0],ecx
    L_0040b7a2:
        add esp,18h
    L_0040b7a5:
        ret 4
    }
}
