#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041E700..0x0041EA2F: FUN_0041e700
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041e700_0041e700() {
    __asm {
    L_0041e700:
        sub esp,1Ch
    L_0041e703:
        push ebp
    L_0041e704:
        mov ebp,ecx
    L_0041e706:
        fld dword ptr [ebp+40h]
    L_0041e709:
        fcomp dword ptr [ebp+444h]
    L_0041e70f:
        fnstsw ax
    L_0041e711:
        test ah,5
    L_0041e714:
        jp short L_0041e73b
    L_0041e716:
        fld dword ptr [data_00476f78]
    L_0041e71c:
        fmul dword ptr [ebp+48h]
    L_0041e71f:
        fadd dword ptr [ebp+40h]
    L_0041e722:
        fst dword ptr [ebp+40h]
    L_0041e725:
        fcomp dword ptr [ebp+444h]
    L_0041e72b:
        fnstsw ax
    L_0041e72d:
        test ah,41h
    L_0041e730:
        jne short L_0041e73b
    L_0041e732:
        mov eax,dword ptr [ebp+444h]
    L_0041e738:
        mov dword ptr [ebp+40h],eax
    L_0041e73b:
        fld dword ptr [data_00476f78]
    L_0041e741:
        push ecx
    L_0041e742:
        fmul dword ptr [ebp+440h]
    L_0041e748:
        mov ecx,dword ptr [ebp+3Ch]
    L_0041e74b:
        fstp dword ptr [esp]
    L_0041e74e:
        push ecx
    L_0041e74f:
        call asm_Angle_NormalizeSum_0044bc10
    L_0041e754:
        fstp dword ptr [ebp+3Ch]
    L_0041e757:
        test byte ptr [ebp+468h],1
    L_0041e75e:
        je short L_0041e785
    L_0041e760:
        mov edx,dword ptr [data_00477704]
    L_0041e766:
        mov eax,dword ptr [edx+10h]
    L_0041e769:
        test eax,eax
    L_0041e76b:
        je short L_0041e785
    L_0041e76d:
        add eax,1068h
    L_0041e772:
        mov edx,dword ptr [eax]
    L_0041e774:
        lea ecx,[ebp+24h]
    L_0041e777:
        mov dword ptr [ecx],edx
    L_0041e779:
        mov edx,dword ptr [eax+4]
    L_0041e77c:
        mov dword ptr [ecx+4],edx
    L_0041e77f:
        mov eax,dword ptr [eax+8]
    L_0041e782:
        mov dword ptr [ecx+8],eax
    L_0041e785:
        fld dword ptr [data_00476f78]
    L_0041e78b:
        fmul dword ptr [ebp+430h]
    L_0041e791:
        fld dword ptr [data_00476f78]
    L_0041e797:
        fmul dword ptr [ebp+434h]
    L_0041e79d:
        fld dword ptr [data_00476f78]
    L_0041e7a3:
        fmul dword ptr [ebp+438h]
    L_0041e7a9:
        fstp dword ptr [esp+1Ch]
    L_0041e7ad:
        fxch
    L_0041e7af:
        fadd dword ptr [ebp+24h]
    L_0041e7b2:
        fstp dword ptr [ebp+24h]
    L_0041e7b5:
        fadd dword ptr [ebp+28h]
    L_0041e7b8:
        fstp dword ptr [ebp+28h]
    L_0041e7bb:
        fld dword ptr [esp+1Ch]
    L_0041e7bf:
        fadd dword ptr [ebp+2Ch]
    L_0041e7c2:
        fstp dword ptr [ebp+2Ch]
    L_0041e7c5:
        mov eax,dword ptr [ebp+0Ch]
    L_0041e7c8:
        add eax,0FFFFFFFEh
    L_0041e7cb:
        cmp eax,3
    L_0041e7ce:
        ja asm_target_0041e886
    L_0041e7d4:
        jmp dword ptr [eax*4+41EA30h]
    L_0041e7db:
        mov ecx,dword ptr [ebp+14h]
    L_0041e7de:
        cmp ecx,dword ptr [ebp+454h]
    L_0041e7e4:
        jl asm_target_0041e886
    L_0041e7ea:
        push 0
    L_0041e7ec:
        lea eax,[ebp+10h]
    L_0041e7ef:
        call asm_Player_SetSchedulerValue_00405410
    L_0041e7f4:
        mov dword ptr [ebp+0Ch],4
    L_0041e7fb:
        jmp asm_target_0041e886
    L_0041e800:
        mov eax,dword ptr [ebp+458h]
    L_0041e806:
        cmp dword ptr [ebp+14h],eax
    L_0041e809:
        mov dword ptr [esp+4],eax
    L_0041e80d:
        jl short L_0041e85e
    L_0041e80f:
        push 0
    L_0041e811:
        lea eax,[ebp+10h]
    L_0041e814:
        call asm_Player_SetSchedulerValue_00405410
    L_0041e819:
        mov edx,dword ptr [ebp+44Ch]
    L_0041e81f:
        mov dword ptr [ebp+0Ch],2
    L_0041e826:
        mov dword ptr [ebp+44h],edx
    L_0041e829:
        mov eax,dword ptr [ebp+14h]
    L_0041e82c:
        cmp eax,dword ptr [ebp+45Ch]
    L_0041e832:
        jl short L_0041e886
    L_0041e834:
        push 0
    L_0041e836:
        lea eax,[ebp+10h]
    L_0041e839:
        call asm_Player_SetSchedulerValue_00405410
    L_0041e83e:
        mov dword ptr [ebp+0Ch],5
    L_0041e845:
        mov eax,dword ptr [ebp+460h]
    L_0041e84b:
        cmp dword ptr [ebp+14h],eax
    L_0041e84e:
        mov dword ptr [esp+4],eax
    L_0041e852:
        jl short L_0041e870
    L_0041e854:
        mov eax,1
    L_0041e859:
        pop ebp
    L_0041e85a:
        add esp,1Ch
    L_0041e85d:
        ret
    L_0041e85e:
        fld dword ptr [ebp+44Ch]
    L_0041e864:
        fmul dword ptr [ebp+18h]
    L_0041e867:
        fidiv dword ptr [esp+4]
    L_0041e86b:
        fstp dword ptr [ebp+44h]
    L_0041e86e:
        jmp short L_0041e886
    L_0041e870:
        fld dword ptr [ebp+44Ch]
    L_0041e876:
        fld st(0)
    L_0041e878:
        fmul dword ptr [ebp+18h]
    L_0041e87b:
        fidiv dword ptr [esp+4]
    L_0041e87f:
        fsubr st,st(1)
    L_0041e881:
        fstp dword ptr [ebp+44h]
    L_0041e884:
        fstp st(0)
    L_0041e886:
        mov eax,dword ptr [ebp+0Ch]
    L_0041e889:
        cmp eax,4
    L_0041e88c:
        push esi
    L_0041e88d:
        je short L_0041e898
    L_0041e88f:
        cmp eax,2
    L_0041e892:
        jne asm_target_0041e9c7
    L_0041e898:
        fld dword ptr [ebp+40h]
    L_0041e89b:
        fcomp dword ptr [data_00470b48]
    L_0041e8a1:
        fnstsw ax
    L_0041e8a3:
        test ah,41h
    L_0041e8a6:
        jne asm_target_0041e9c7
    L_0041e8ac:
        fld dword ptr [ebp+40h]
    L_0041e8af:
        push ecx
    L_0041e8b0:
        fmul dword ptr [data_00470c18]
    L_0041e8b6:
        mov ecx,dword ptr [ebp+3Ch]
    L_0041e8b9:
        fstp dword ptr [esp]
    L_0041e8bc:
        push ecx
    L_0041e8bd:
        lea ecx,[esp+14h]
    L_0041e8c1:
        call asm_SetPolar_Vector2_0041f800
    L_0041e8c6:
        fld dword ptr [esp+0Ch]
    L_0041e8ca:
        fadd dword ptr [ebp+24h]
    L_0041e8cd:
        fstp dword ptr [esp+0Ch]
    L_0041e8d1:
        fld dword ptr [esp+10h]
    L_0041e8d5:
        fadd dword ptr [ebp+28h]
    L_0041e8d8:
        fstp dword ptr [esp+10h]
    L_0041e8dc:
        fld dword ptr [esp+14h]
    L_0041e8e0:
        fadd dword ptr [ebp+2Ch]
    L_0041e8e3:
        fstp dword ptr [esp+14h]
    L_0041e8e7:
        fld dword ptr [ebp+44h]
    L_0041e8ea:
        fcomp dword ptr [data_00470bcc]
    L_0041e8f0:
        fld dword ptr [ebp+44h]
    L_0041e8f3:
        fnstsw ax
    L_0041e8f5:
        test ah,5
    L_0041e8f8:
        jp short L_0041e902
    L_0041e8fa:
        fmul dword ptr [data_00470b0c]
    L_0041e900:
        jmp short L_0041e911
    L_0041e902:
        fadd dword ptr [data_00470b48]
    L_0041e908:
        fmul dword ptr [data_00470cc4]
    L_0041e90e:
        fsubr dword ptr [ebp+44h]
    L_0041e911:
        mov eax,dword ptr [ebp+3Ch]
    L_0041e914:
        fstp dword ptr [esp+8]
    L_0041e918:
        fld dword ptr [ebp+40h]
    L_0041e91b:
        mov edx,dword ptr [esp+8]
    L_0041e91f:
        fmul dword ptr [data_00470cc0]
    L_0041e925:
        push ecx
    L_0041e926:
        mov ecx,dword ptr [data_00477834]
    L_0041e92c:
        fstp dword ptr [esp]
    L_0041e92f:
        push edx
    L_0041e930:
        push eax
    L_0041e931:
        lea eax,[esp+18h]
    L_0041e935:
        call asm_FUN_004267f0_004267f0
    L_0041e93a:
        cmp eax,1
    L_0041e93d:
        jne short L_0041e975
    L_0041e93f:
        mov ecx,dword ptr [data_00477834]
    L_0041e945:
        mov edx,dword ptr [ebp]
    L_0041e948:
        push 0
    L_0041e94a:
        lea eax,[esp+1Ch]
    L_0041e94e:
        add ecx,3C0h
    L_0041e954:
        push eax
    L_0041e955:
        push ecx
    L_0041e956:
        mov ecx,ebp
    L_0041e958:
        mov dword ptr [esp+24h],42000000h
    L_0041e960:
        mov dword ptr [esp+28h],42000000h
    L_0041e968:
        mov dword ptr [esp+2Ch],0
    L_0041e970:
        call dword ptr [edx+18h]
    L_0041e973:
        jmp short L_0041e9c7
    L_0041e975:
        cmp eax,2
    L_0041e978:
        jne short L_0041e9c7
    L_0041e97a:
        mov eax,dword ptr [ebp+14h]
    L_0041e97d:
        cdq
    L_0041e97e:
        mov ecx,5
    L_0041e983:
        idiv ecx
    L_0041e985:
        test edx,edx
    L_0041e987:
        jne short L_0041e9c7
    L_0041e989:
        mov eax,dword ptr [data_004776f0]
    L_0041e98e:
        mov ecx,dword ptr [eax+3E0B50h]
    L_0041e994:
        push ebx
    L_0041e995:
        push edi
    L_0041e996:
        mov edi,dword ptr [data_00477834]
    L_0041e99c:
        push 1B2h
    L_0041e9a1:
        lea edx,[esp+14h]
    L_0041e9a5:
        push edx
    L_0041e9a6:
        add edi,3C0h
    L_0041e9ac:
        push ecx
    L_0041e9ad:
        call asm_PlayerAnimation_Create_00448db0
    L_0041e9b2:
        mov edx,dword ptr [ebp+24h]
    L_0041e9b5:
        push edx
    L_0041e9b6:
        mov ebx,1Ch
    L_0041e9bb:
        mov esi,492590h
    L_0041e9c0:
        call asm_FUN_0043dd10_0043dd10
    L_0041e9c5:
        pop edi
    L_0041e9c6:
        pop ebx
    L_0041e9c7:
        mov ecx,dword ptr [ebp+9B0h]
    L_0041e9cd:
        fld dword ptr [ebp+44h]
    L_0041e9d0:
        fdiv dword ptr [ecx+34h]
    L_0041e9d3:
        mov esi,dword ptr [ebp+978h]
    L_0041e9d9:
        lea eax,[ebp+61Ch]
    L_0041e9df:
        mov ecx,8
    L_0041e9e4:
        or esi,ecx
    L_0041e9e6:
        mov dword ptr [eax+35Ch],esi
    L_0041e9ec:
        push eax
    L_0041e9ed:
        fstp dword ptr [eax+3Ch]
    L_0041e9f0:
        fld dword ptr [ebp+40h]
    L_0041e9f3:
        mov edx,dword ptr [ebp+9B0h]
    L_0041e9f9:
        fdiv dword ptr [edx+30h]
    L_0041e9fc:
        or dword ptr [eax+35Ch],ecx
    L_0041ea02:
        fstp dword ptr [eax+40h]
    L_0041ea05:
        call asm_FUN_0043ee30_0043ee30
    L_0041ea0a:
        fld dword ptr [data_00470b04]
    L_0041ea10:
        fld dword ptr [ebp+4Ch]
    L_0041ea13:
        pop esi
    L_0041ea14:
        fucompp
    L_0041ea16:
        fnstsw ax
    L_0041ea18:
        test ah,44h
    L_0041ea1b:
        jp short L_0041ea29
    L_0041ea1d:
        add ebp,9C8h
    L_0041ea23:
        push ebp
    L_0041ea24:
        call asm_FUN_0043ee30_0043ee30
    L_0041ea29:
        xor eax,eax
    L_0041ea2b:
        pop ebp
    L_0041ea2c:
        add esp,1Ch
    L_0041ea2f:
        ret
    }
}
