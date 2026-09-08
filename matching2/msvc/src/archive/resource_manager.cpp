#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004356F0..0x0043572C: FUN_004356f0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004356f0_004356f0() {
    __asm {
    L_004356f0:
        sub esp,108h
    L_004356f6:
        mov eax,dword ptr [data_00473660]
    L_004356fb:
        xor eax,esp
    L_004356fd:
        push ebx
    L_004356fe:
        push ebp
    L_004356ff:
        push esi
    L_00435700:
        push edi
    L_00435701:
        mov esi,ecx
    L_00435703:
        push 2Fh
    L_00435705:
        push esi
    L_00435706:
        mov dword ptr [esp+11Ch],eax
    L_0043570d:
        call asm_FUN_00452730_00452730
    L_00435712:
        add esp,8
    L_00435715:
        test eax,eax
    L_00435717:
        je short L_0043571c
    L_00435719:
        inc eax
    L_0043571a:
        jmp short L_0043571e
    L_0043571c:
        mov eax,esi
    L_0043571e:
        sub eax,esi
    L_00435720:
        dec eax
    L_00435721:
        lea edx,[esp+10h]
    L_00435725:
        mov edi,eax
    L_00435727:
        mov eax,esi
    L_00435729:
        sub edx,esi
    L_0043572b:
        TH10_REL8(0xeb, 0x0043572b, VA_asm_FUN_004356f0_part_00435730)
    }
}

// 0x00435730..0x004357C3: FUN_004356f0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004356f0_part_00435730() {
    __asm {
    L_00435730:
        mov cl,byte ptr [eax]
    L_00435732:
        mov byte ptr [edx+eax],cl
    L_00435735:
        inc eax
    L_00435736:
        test cl,cl
    L_00435738:
        jne short L_00435730
    L_0043573a:
        test edi,edi
    L_0043573c:
        jl short L_00435753
    L_0043573e:
        mov ecx,dword ptr [data_0046f274]
    L_00435744:
        mov dl,byte ptr [data_0046f278]
    L_0043574a:
        lea eax,[esp+edi+10h]
    L_0043574e:
        mov dword ptr [eax],ecx
    L_00435750:
        mov byte ptr [eax+4],dl
    L_00435753:
        mov eax,dword ptr [data_00477850]
    L_00435758:
        xor ebp,ebp
    L_0043575a:
        test eax,eax
    L_0043575c:
        mov edi,4923B0h
    L_00435761:
        jle short L_004357a5
    L_00435763:
        mov ecx,dword ptr [edi+8]
    L_00435766:
        lea esi,[esp+10h]
    L_0043576a:
        lea ebx,[ebx+force_disp32_zero]
    L_00435770:
        mov bl,byte ptr [ecx]
    L_00435772:
        mov dl,bl
    L_00435774:
        cmp bl,byte ptr [esi]
    L_00435776:
        jne short L_00435794
    L_00435778:
        test dl,dl
    L_0043577a:
        je short L_00435790
    L_0043577c:
        mov bl,byte ptr [ecx+1]
    L_0043577f:
        mov dl,bl
    L_00435781:
        cmp bl,byte ptr [esi+1]
    L_00435784:
        jne short L_00435794
    L_00435786:
        add ecx,2
    L_00435789:
        add esi,2
    L_0043578c:
        test dl,dl
    L_0043578e:
        jne short L_00435770
    L_00435790:
        xor ecx,ecx
    L_00435792:
        jmp short L_00435799
    L_00435794:
        sbb ecx,ecx
    L_00435796:
        sbb ecx,0FFFFFFFFh
    L_00435799:
        test ecx,ecx
    L_0043579b:
        je short L_004357c0
    L_0043579d:
        inc ebp
    L_0043579e:
        add edi,10h
    L_004357a1:
        cmp ebp,eax
    L_004357a3:
        jl short L_00435763
    L_004357a5:
        xor eax,eax
    L_004357a7:
        mov ecx,dword ptr [esp+114h]
    L_004357ae:
        pop edi
    L_004357af:
        pop esi
    L_004357b0:
        pop ebp
    L_004357b1:
        pop ebx
    L_004357b2:
        xor ecx,esp
    L_004357b4:
        call asm_security_check_cookie_00458ea5
    L_004357b9:
        add esp,108h
    L_004357bf:
        ret
    L_004357c0:
        mov eax,edi
    L_004357c2:
        jmp short L_004357a7
    }
}

// 0x00435800..0x004358D5: FUN_00435800
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00435800_00435800() {
    __asm {
    L_00435800:
        mov eax,dword ptr fs:[0]
    L_00435806:
        push 0FFFFFFFFh
    L_00435808:
        push 4653A8h
    L_0043580d:
        push eax
    L_0043580e:
        mov dword ptr fs:[0],esp
    L_00435815:
        sub esp,0Ch
    L_00435818:
        push esi
    L_00435819:
        push edi
    L_0043581a:
        mov esi,ecx
    L_0043581c:
        call asm_FUN_004356f0_004356f0
    L_00435821:
        mov edi,eax
    L_00435823:
        test edi,edi
    L_00435825:
        je short L_00435859
    L_00435827:
        push 2Fh
    L_00435829:
        push esi
    L_0043582a:
        call asm_FUN_00452730_00452730
    L_0043582f:
        add esp,8
    L_00435832:
        test eax,eax
    L_00435834:
        lea ecx,[eax+1]
    L_00435837:
        jne short L_0043583b
    L_00435839:
        mov ecx,esi
    L_0043583b:
        mov eax,dword ptr [esp+24h]
    L_0043583f:
        push eax
    L_00435840:
        push edi
    L_00435841:
        call asm_DatArchive_Read_00434dd0
    L_00435846:
        pop edi
    L_00435847:
        pop esi
    L_00435848:
        mov ecx,dword ptr [esp+0Ch]
    L_0043584c:
        mov dword ptr fs:[0],ecx
    L_00435853:
        add esp,18h
    L_00435856:
        ret 4
    L_00435859:
        mov edi,46F230h
    L_0043585e:
        mov dword ptr [esp+8],edi
    L_00435862:
        mov dword ptr [esp+0Ch],0FFFFFFFFh
    L_0043586a:
        mov dword ptr [esp+10h],0
    L_00435872:
        mov dword ptr [esp+1Ch],0
    L_0043587a:
        mov ecx,dword ptr [data_00474908]
    L_00435880:
        push ecx
    L_00435881:
        push esi
    L_00435882:
        lea ecx,[esp+10h]
    L_00435886:
        call asm_FileHandle_OpenRetail_00435370
    L_0043588b:
        mov eax,dword ptr [esp+0Ch]
    L_0043588f:
        cmp eax,0FFFFFFFFh
    L_00435892:
        jne short L_00435898
    L_00435894:
        xor eax,eax
    L_00435896:
        jmp short L_004358a1
    L_00435898:
        push 0
    L_0043589a:
        push eax
    L_0043589b:
        call dword ptr [data_004660d8]
    L_004358a1:
        push eax
    L_004358a2:
        lea ecx,[esp+0Ch]
    L_004358a6:
        call asm_ReadWhole_FileHandle_00435580
    L_004358ab:
        mov esi,eax
    L_004358ad:
        mov eax,dword ptr [esp+0Ch]
    L_004358b1:
        cmp eax,0FFFFFFFFh
    L_004358b4:
        mov dword ptr [esp+8],edi
    L_004358b8:
        je short L_004358c1
    L_004358ba:
        push eax
    L_004358bb:
        call dword ptr [data_004660cc]
    L_004358c1:
        mov ecx,dword ptr [esp+14h]
    L_004358c5:
        pop edi
    L_004358c6:
        mov eax,esi
    L_004358c8:
        pop esi
    L_004358c9:
        mov dword ptr fs:[0],ecx
    L_004358d0:
        add esp,18h
    L_004358d3:
        ret 4
    }
}

// 0x004358E0..0x0043599D: Resource_GetFileSizeRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Resource_GetFileSizeRetail_004358e0() {
    __asm {
    L_004358e0:
        push 0FFFFFFFFh
    L_004358e2:
        mov eax,dword ptr fs:[0]
    L_004358e8:
        push 465388h
    L_004358ed:
        push eax
    L_004358ee:
        mov dword ptr fs:[0],esp
    L_004358f5:
        sub esp,0Ch
    L_004358f8:
        push ebx
    L_004358f9:
        push ebp
    L_004358fa:
        push esi
    L_004358fb:
        push edi
    L_004358fc:
        mov esi,ecx
    L_004358fe:
        call asm_FUN_004356f0_004356f0
    L_00435903:
        mov ebp,eax
    L_00435905:
        xor edi,edi
    L_00435907:
        cmp ebp,edi
    L_00435909:
        je short L_00435939
    L_0043590b:
        push 2Fh
    L_0043590d:
        push esi
    L_0043590e:
        call asm_FUN_00452730_00452730
    L_00435913:
        add esp,8
    L_00435916:
        cmp eax,edi
    L_00435918:
        je short L_0043591d
    L_0043591a:
        lea esi,[eax+1]
    L_0043591d:
        mov ebx,esi
    L_0043591f:
        mov eax,ebp
    L_00435921:
        call asm_DatArchive_FindSize_00434ef0
    L_00435926:
        pop edi
    L_00435927:
        pop esi
    L_00435928:
        pop ebp
    L_00435929:
        pop ebx
    L_0043592a:
        mov ecx,dword ptr [esp+0Ch]
    L_0043592e:
        mov dword ptr fs:[0],ecx
    L_00435935:
        add esp,18h
    L_00435938:
        ret
    L_00435939:
        mov ebx,46F230h
    L_0043593e:
        mov dword ptr [esp+10h],ebx
    L_00435942:
        mov dword ptr [esp+14h],0FFFFFFFFh
    L_0043594a:
        mov dword ptr [esp+18h],edi
    L_0043594e:
        mov dword ptr [esp+24h],edi
    L_00435952:
        mov eax,dword ptr [data_00474908]
    L_00435957:
        push eax
    L_00435958:
        push esi
    L_00435959:
        lea ecx,[esp+18h]
    L_0043595d:
        call asm_FileHandle_OpenRetail_00435370
    L_00435962:
        mov eax,dword ptr [esp+14h]
    L_00435966:
        cmp eax,0FFFFFFFFh
    L_00435969:
        je short L_00435979
    L_0043596b:
        push edi
    L_0043596c:
        push eax
    L_0043596d:
        call dword ptr [data_004660d8]
    L_00435973:
        mov edi,eax
    L_00435975:
        mov eax,dword ptr [esp+14h]
    L_00435979:
        cmp eax,0FFFFFFFFh
    L_0043597c:
        mov dword ptr [esp+10h],ebx
    L_00435980:
        je short L_00435989
    L_00435982:
        push eax
    L_00435983:
        call dword ptr [data_004660cc]
    L_00435989:
        mov ecx,dword ptr [esp+1Ch]
    L_0043598d:
        mov eax,edi
    L_0043598f:
        pop edi
    L_00435990:
        pop esi
    L_00435991:
        pop ebp
    L_00435992:
        pop ebx
    L_00435993:
        mov dword ptr fs:[0],ecx
    L_0043599a:
        add esp,18h
    L_0043599d:
        ret
    }
}
