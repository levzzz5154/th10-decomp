#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045C651..0x0045C86E: FUN_0045c651
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045c651_0045c651() {
    __asm {
    L_0045c651:
        push ebp
    L_0045c652:
        mov ebp,esp
    L_0045c654:
        sub esp,7Ch
    L_0045c657:
        mov eax,dword ptr [data_00473660]
    L_0045c65c:
        mov edx,dword ptr [ebp+8]
    L_0045c65f:
        xor eax,ebp
    L_0045c661:
        push esi
    L_0045c662:
        mov dword ptr [ebp-4],eax
    L_0045c665:
        call asm_LcidFromHexString_0045c4f2
    L_0045c66a:
        mov esi,eax
    L_0045c66c:
        push 78h
    L_0045c66e:
        lea eax,[ebp-7Ch]
    L_0045c671:
        push eax
    L_0045c672:
        mov eax,dword ptr [data_00477638]
    L_0045c677:
        neg eax
    L_0045c679:
        sbb eax,eax
    L_0045c67b:
        and eax,0FFFFF005h
    L_0045c680:
        add eax,1002h
    L_0045c685:
        push eax
    L_0045c686:
        push esi
    L_0045c687:
        call dword ptr [data_00477648]
    L_0045c68d:
        test eax,eax
    L_0045c68f:
        jne short L_0045c69d
    L_0045c691:
        and dword ptr [data_00477628],eax
    L_0045c697:
        inc eax
    L_0045c698:
        jmp asm_target_0045c860
    L_0045c69d:
        push ebx
    L_0045c69e:
        push edi
    L_0045c69f:
        lea eax,[ebp-7Ch]
    L_0045c6a2:
        push eax
    L_0045c6a3:
        push dword ptr [data_0047763c]
    L_0045c6a9:
        call asm_stricmp_0046054e
    L_0045c6ae:
        test eax,eax
    L_0045c6b0:
        pop ecx
    L_0045c6b1:
        pop ecx
    L_0045c6b2:
        mov ebx,0FFFFF002h
    L_0045c6b7:
        mov edi,1001h
    L_0045c6bc:
        jne asm_target_0045c77e
    L_0045c6c2:
        push 78h
    L_0045c6c4:
        lea eax,[ebp-7Ch]
    L_0045c6c7:
        push eax
    L_0045c6c8:
        mov eax,dword ptr [data_00477634]
    L_0045c6cd:
        neg eax
    L_0045c6cf:
        sbb eax,eax
    L_0045c6d1:
        and eax,ebx
    L_0045c6d3:
        add eax,edi
    L_0045c6d5:
        push eax
    L_0045c6d6:
        push esi
    L_0045c6d7:
        call dword ptr [data_00477648]
    L_0045c6dd:
        test eax,eax
    L_0045c6df:
        je asm_target_0045c7b2
    L_0045c6e5:
        lea eax,[ebp-7Ch]
    L_0045c6e8:
        push eax
    L_0045c6e9:
        push dword ptr [data_00477644]
    L_0045c6ef:
        call asm_stricmp_0046054e
    L_0045c6f4:
        test eax,eax
    L_0045c6f6:
        pop ecx
    L_0045c6f7:
        pop ecx
    L_0045c6f8:
        jne short L_0045c70b
    L_0045c6fa:
        or word ptr [data_00477628],304h
    L_0045c703:
        mov dword ptr [data_0047762c],esi
    L_0045c709:
        jmp short L_0045c778
    L_0045c70b:
        test byte ptr [data_00477628],2
    L_0045c712:
        jne short L_0045c77e
    L_0045c714:
        mov eax,dword ptr [data_00477640]
    L_0045c719:
        test eax,eax
    L_0045c71b:
        je short L_0045c75d
    L_0045c71d:
        push eax
    L_0045c71e:
        lea eax,[ebp-7Ch]
    L_0045c721:
        push eax
    L_0045c722:
        push dword ptr [data_00477644]
    L_0045c728:
        call asm_strnicmp_004605b7
    L_0045c72d:
        add esp,0Ch
    L_0045c730:
        test eax,eax
    L_0045c732:
        jne short L_0045c75d
    L_0045c734:
        push dword ptr [data_00477644]
    L_0045c73a:
        or dword ptr [data_00477628],2
    L_0045c741:
        mov dword ptr [data_00477630],esi
    L_0045c747:
        call asm_strlen_00456720
    L_0045c74c:
        cmp eax,dword ptr [data_00477640]
    L_0045c752:
        pop ecx
    L_0045c753:
        jne short L_0045c77e
    L_0045c755:
        mov dword ptr [data_0047762c],esi
    L_0045c75b:
        jmp short L_0045c77e
    L_0045c75d:
        test byte ptr [data_00477628],1
    L_0045c764:
        jne short L_0045c77e
    L_0045c766:
        push esi
    L_0045c767:
        call asm_FUN_0045c3f1_0045c3f1
    L_0045c76c:
        test eax,eax
    L_0045c76e:
        pop ecx
    L_0045c76f:
        je short L_0045c77e
    L_0045c771:
        or dword ptr [data_00477628],1
    L_0045c778:
        mov dword ptr [data_00477630],esi
    L_0045c77e:
        mov ecx,dword ptr [data_00477628]
    L_0045c784:
        mov eax,300h
    L_0045c789:
        and ecx,eax
    L_0045c78b:
        cmp ecx,eax
    L_0045c78d:
        je asm_target_0045c851
    L_0045c793:
        push 78h
    L_0045c795:
        lea eax,[ebp-7Ch]
    L_0045c798:
        push eax
    L_0045c799:
        mov eax,dword ptr [data_00477634]
    L_0045c79e:
        neg eax
    L_0045c7a0:
        sbb eax,eax
    L_0045c7a2:
        and eax,ebx
    L_0045c7a4:
        add eax,edi
    L_0045c7a6:
        push eax
    L_0045c7a7:
        push esi
    L_0045c7a8:
        call dword ptr [data_00477648]
    L_0045c7ae:
        test eax,eax
    L_0045c7b0:
        jne short L_0045c7c1
    L_0045c7b2:
        and dword ptr [data_00477628],0
    L_0045c7b9:
        xor eax,eax
    L_0045c7bb:
        inc eax
    L_0045c7bc:
        jmp asm_target_0045c85e
    L_0045c7c1:
        lea eax,[ebp-7Ch]
    L_0045c7c4:
        push eax
    L_0045c7c5:
        push dword ptr [data_00477644]
    L_0045c7cb:
        call asm_stricmp_0046054e
    L_0045c7d0:
        pop ecx
    L_0045c7d1:
        xor edi,edi
    L_0045c7d3:
        test eax,eax
    L_0045c7d5:
        pop ecx
    L_0045c7d6:
        jne short L_0045c807
    L_0045c7d8:
        or byte ptr [data_00477629],2
    L_0045c7df:
        cmp dword ptr [data_00477634],edi
    L_0045c7e5:
        jne short L_0045c83c
    L_0045c7e7:
        cmp dword ptr [data_00477640],edi
    L_0045c7ed:
        je short L_0045c83c
    L_0045c7ef:
        push dword ptr [data_00477644]
    L_0045c7f5:
        call asm_strlen_00456720
    L_0045c7fa:
        cmp eax,dword ptr [data_00477640]
    L_0045c800:
        pop ecx
    L_0045c801:
        jne short L_0045c83c
    L_0045c803:
        push 1
    L_0045c805:
        jmp short L_0045c830
    L_0045c807:
        cmp dword ptr [data_00477634],edi
    L_0045c80d:
        jne short L_0045c851
    L_0045c80f:
        mov eax,dword ptr [data_00477640]
    L_0045c814:
        cmp eax,edi
    L_0045c816:
        je short L_0045c851
    L_0045c818:
        push eax
    L_0045c819:
        lea eax,[ebp-7Ch]
    L_0045c81c:
        push eax
    L_0045c81d:
        push dword ptr [data_00477644]
    L_0045c823:
        call asm_strnicmp_004605b7
    L_0045c828:
        add esp,0Ch
    L_0045c82b:
        test eax,eax
    L_0045c82d:
        jne short L_0045c851
    L_0045c82f:
        push edi
    L_0045c830:
        push esi
    L_0045c831:
        call asm_FUN_0045c5dc_0045c5dc
    L_0045c836:
        test eax,eax
    L_0045c838:
        pop ecx
    L_0045c839:
        pop ecx
    L_0045c83a:
        je short L_0045c851
    L_0045c83c:
        or byte ptr [data_00477629],1
    L_0045c843:
        cmp dword ptr [data_0047762c],edi
    L_0045c849:
        jne short L_0045c851
    L_0045c84b:
        mov dword ptr [data_0047762c],esi
    L_0045c851:
        mov eax,dword ptr [data_00477628]
    L_0045c856:
        shr eax,2
    L_0045c859:
        not eax
    L_0045c85b:
        and eax,1
    L_0045c85e:
        pop edi
    L_0045c85f:
        pop ebx
    L_0045c860:
        mov ecx,dword ptr [ebp-4]
    L_0045c863:
        xor ecx,ebp
    L_0045c865:
        pop esi
    L_0045c866:
        call asm_security_check_cookie_00458ea5
    L_0045c86b:
        leave
    L_0045c86c:
        ret 4
    }
}
