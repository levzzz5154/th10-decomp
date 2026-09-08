#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045E648..0x0045E86B: __handle_exc
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_handle_exc_0045e648() {
    __asm {
    L_0045e648:
        push ebp
    L_0045e649:
        mov ebp,esp
    L_0045e64b:
        sub esp,10h
    L_0045e64e:
        mov eax,dword ptr [ebp+8]
    L_0045e651:
        push ebx
    L_0045e652:
        push esi
    L_0045e653:
        xor ebx,ebx
    L_0045e655:
        mov esi,eax
    L_0045e657:
        and esi,1Fh
    L_0045e65a:
        inc ebx
    L_0045e65b:
        test al,8
    L_0045e65d:
        mov dword ptr [ebp-4],esi
    L_0045e660:
        je short L_0045e676
    L_0045e662:
        test byte ptr [ebp+10h],bl
    L_0045e665:
        je short L_0045e676
    L_0045e667:
        push ebx
    L_0045e668:
        call asm_FUN_0045edab_0045edab
    L_0045e66d:
        pop ecx
    L_0045e66e:
        and esi,0FFFFFFF7h
    L_0045e671:
        jmp asm_target_0045e84a
    L_0045e676:
        test al,4
    L_0045e678:
        je short L_0045e690
    L_0045e67a:
        test byte ptr [ebp+10h],4
    L_0045e67e:
        je short L_0045e690
    L_0045e680:
        push 4
    L_0045e682:
        call asm_FUN_0045edab_0045edab
    L_0045e687:
        pop ecx
    L_0045e688:
        and esi,0FFFFFFFBh
    L_0045e68b:
        jmp asm_target_0045e84a
    L_0045e690:
        test al,bl
    L_0045e692:
        je asm_target_0045e770
    L_0045e698:
        test byte ptr [ebp+10h],8
    L_0045e69c:
        je asm_target_0045e770
    L_0045e6a2:
        push 8
    L_0045e6a4:
        call asm_FUN_0045edab_0045edab
    L_0045e6a9:
        mov eax,dword ptr [ebp+10h]
    L_0045e6ac:
        pop ecx
    L_0045e6ad:
        mov ecx,0C00h
    L_0045e6b2:
        and eax,ecx
    L_0045e6b4:
        je asm_target_0045e746
    L_0045e6ba:
        cmp eax,400h
    L_0045e6bf:
        je short L_0045e71c
    L_0045e6c1:
        cmp eax,800h
    L_0045e6c6:
        je short L_0045e6f2
    L_0045e6c8:
        cmp eax,ecx
    L_0045e6ca:
        jne asm_target_0045e768
    L_0045e6d0:
        mov ecx,dword ptr [ebp+0Ch]
    L_0045e6d3:
        fld qword ptr [ecx]
    L_0045e6d5:
        fcomp qword ptr [data_00470b70]
    L_0045e6db:
        fld qword ptr [data_00473d90]
    L_0045e6e1:
        fnstsw ax
    L_0045e6e3:
        test ah,41h
    L_0045e6e6:
        je short L_0045e6ea
    L_0045e6e8:
        fchs
    L_0045e6ea:
        fstp qword ptr [ebp-10h]
    L_0045e6ed:
        fld qword ptr [ebp-10h]
    L_0045e6f0:
        jmp short L_0045e766
    L_0045e6f2:
        mov ecx,dword ptr [ebp+0Ch]
    L_0045e6f5:
        fld qword ptr [ecx]
    L_0045e6f7:
        fcomp qword ptr [data_00470b70]
    L_0045e6fd:
        fnstsw ax
    L_0045e6ff:
        test ah,41h
    L_0045e702:
        jne short L_0045e70c
    L_0045e704:
        fld qword ptr [data_00473d80]
    L_0045e70a:
        jmp short L_0045e714
    L_0045e70c:
        fld qword ptr [data_00473d90]
    L_0045e712:
        fchs
    L_0045e714:
        fstp qword ptr [ebp-10h]
    L_0045e717:
        fld qword ptr [ebp-10h]
    L_0045e71a:
        jmp short L_0045e766
    L_0045e71c:
        mov ecx,dword ptr [ebp+0Ch]
    L_0045e71f:
        fld qword ptr [ecx]
    L_0045e721:
        fcomp qword ptr [data_00470b70]
    L_0045e727:
        fnstsw ax
    L_0045e729:
        test ah,41h
    L_0045e72c:
        jne short L_0045e736
    L_0045e72e:
        fld qword ptr [data_00473d90]
    L_0045e734:
        jmp short L_0045e73e
    L_0045e736:
        fld qword ptr [data_00473d80]
    L_0045e73c:
        fchs
    L_0045e73e:
        fstp qword ptr [ebp-10h]
    L_0045e741:
        fld qword ptr [ebp-10h]
    L_0045e744:
        jmp short L_0045e766
    L_0045e746:
        mov ecx,dword ptr [ebp+0Ch]
    L_0045e749:
        fld qword ptr [ecx]
    L_0045e74b:
        fcomp qword ptr [data_00470b70]
    L_0045e751:
        fld qword ptr [data_00473d80]
    L_0045e757:
        fnstsw ax
    L_0045e759:
        test ah,41h
    L_0045e75c:
        je short L_0045e760
    L_0045e75e:
        fchs
    L_0045e760:
        fstp qword ptr [ebp-10h]
    L_0045e763:
        fld qword ptr [ebp-10h]
    L_0045e766:
        fstp qword ptr [ecx]
    L_0045e768:
        and esi,0FFFFFFFEh
    L_0045e76b:
        jmp asm_target_0045e84a
    L_0045e770:
        test al,2
    L_0045e772:
        je asm_target_0045e84a
    L_0045e778:
        test byte ptr [ebp+10h],10h
    L_0045e77c:
        je asm_target_0045e84a
    L_0045e782:
        xor esi,esi
    L_0045e784:
        test al,10h
    L_0045e786:
        je short L_0045e78a
    L_0045e788:
        mov esi,ebx
    L_0045e78a:
        fld qword ptr [data_00470b70]
    L_0045e790:
        push edi
    L_0045e791:
        mov edi,dword ptr [ebp+0Ch]
    L_0045e794:
        fld qword ptr [edi]
    L_0045e796:
        fucompp
    L_0045e798:
        fnstsw ax
    L_0045e79a:
        test ah,44h
    L_0045e79d:
        jnp asm_target_0045e834
    L_0045e7a3:
        fld qword ptr [edi]
    L_0045e7a5:
        lea eax,[ebp-8]
    L_0045e7a8:
        push eax
    L_0045e7a9:
        push ecx
    L_0045e7aa:
        push ecx
    L_0045e7ab:
        fstp qword ptr [esp]
    L_0045e7ae:
        call asm_decomp_0045ecb4
    L_0045e7b3:
        mov ecx,dword ptr [ebp-8]
    L_0045e7b6:
        fstp qword ptr [ebp-10h]
    L_0045e7b9:
        fld qword ptr [ebp-10h]
    L_0045e7bc:
        add ecx,0FFFFFA00h
    L_0045e7c2:
        add esp,0Ch
    L_0045e7c5:
        cmp ecx,0FFFFFBCEh
    L_0045e7cb:
        jge short L_0045e7d7
    L_0045e7cd:
        fmul qword ptr [data_00470b70]
    L_0045e7d3:
        mov esi,ebx
    L_0045e7d5:
        jmp short L_0045e82a
    L_0045e7d7:
        fcomp qword ptr [data_00470b70]
    L_0045e7dd:
        fnstsw ax
    L_0045e7df:
        test ah,5
    L_0045e7e2:
        jp short L_0045e7e8
    L_0045e7e4:
        mov edx,ebx
    L_0045e7e6:
        jmp short L_0045e7ea
    L_0045e7e8:
        xor edx,edx
    L_0045e7ea:
        xor eax,eax
    L_0045e7ec:
        mov al,byte ptr [ebp-0Ah]
    L_0045e7ef:
        and eax,0Fh
    L_0045e7f2:
        or eax,10h
    L_0045e7f5:
        mov word ptr [ebp-0Ah],ax
    L_0045e7f9:
        mov eax,0FFFFFC03h
    L_0045e7fe:
        cmp ecx,eax
    L_0045e800:
        jge short L_0045e821
    L_0045e802:
        sub eax,ecx
    L_0045e804:
        test byte ptr [ebp-10h],bl
    L_0045e807:
        je short L_0045e80f
    L_0045e809:
        test esi,esi
    L_0045e80b:
        jne short L_0045e80f
    L_0045e80d:
        mov esi,ebx
    L_0045e80f:
        shr dword ptr [ebp-10h],1
    L_0045e812:
        test byte ptr [ebp-0Ch],bl
    L_0045e815:
        je short L_0045e81b
    L_0045e817:
        or byte ptr [ebp-0Dh],80h
    L_0045e81b:
        shr dword ptr [ebp-0Ch],1
    L_0045e81e:
        dec eax
    L_0045e81f:
        jne short L_0045e804
    L_0045e821:
        test edx,edx
    L_0045e823:
        je short L_0045e82d
    L_0045e825:
        fld qword ptr [ebp-10h]
    L_0045e828:
        fchs
    L_0045e82a:
        fstp qword ptr [ebp-10h]
    L_0045e82d:
        fld qword ptr [ebp-10h]
    L_0045e830:
        fstp qword ptr [edi]
    L_0045e832:
        jmp short L_0045e836
    L_0045e834:
        mov esi,ebx
    L_0045e836:
        test esi,esi
    L_0045e838:
        pop edi
    L_0045e839:
        je short L_0045e843
    L_0045e83b:
        push 10h
    L_0045e83d:
        call asm_FUN_0045edab_0045edab
    L_0045e842:
        pop ecx
    L_0045e843:
        and dword ptr [ebp-4],0FFFFFFFDh
    L_0045e847:
        mov esi,dword ptr [ebp-4]
    L_0045e84a:
        test byte ptr [ebp+8],10h
    L_0045e84e:
        je short L_0045e861
    L_0045e850:
        test byte ptr [ebp+10h],20h
    L_0045e854:
        je short L_0045e861
    L_0045e856:
        push 20h
    L_0045e858:
        call asm_FUN_0045edab_0045edab
    L_0045e85d:
        pop ecx
    L_0045e85e:
        and esi,0FFFFFFEFh
    L_0045e861:
        xor eax,eax
    L_0045e863:
        test esi,esi
    L_0045e865:
        pop esi
    L_0045e866:
        sete al
    L_0045e869:
        pop ebx
    L_0045e86a:
        leave
    L_0045e86b:
        ret
    }
}
