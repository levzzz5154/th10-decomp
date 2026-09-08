#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045B61B..0x0045B7E7: ___init_numeric
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_init_numeric_0045b61b() {
    __asm {
    L_0045b61b:
        push ebp
    L_0045b61c:
        mov ebp,esp
    L_0045b61e:
        push ecx
    L_0045b61f:
        push ecx
    L_0045b620:
        push ebx
    L_0045b621:
        push esi
    L_0045b622:
        xor esi,esi
    L_0045b624:
        cmp dword ptr [data_0047765c],esi
    L_0045b62a:
        push edi
    L_0045b62b:
        jne short L_0045b67c
    L_0045b62d:
        cmp dword ptr [data_00477658],esi
    L_0045b633:
        jne short L_0045b67c
    L_0045b635:
        mov eax,dword ptr [data_004981cc]
    L_0045b63a:
        cmp eax,esi
    L_0045b63c:
        je short L_0045b660
    L_0045b63e:
        cmp dword ptr [eax],esi
    L_0045b640:
        jne short L_0045b660
    L_0045b642:
        mov ecx,dword ptr [data_0047320c]
    L_0045b648:
        cmp eax,dword ptr [ecx+2Ch]
    L_0045b64b:
        je short L_0045b660
    L_0045b64d:
        push eax
    L_0045b64e:
        call asm_free_00452422
    L_0045b653:
        push dword ptr [data_00477624]
    L_0045b659:
        call asm_free_00452422
    L_0045b65e:
        pop ecx
    L_0045b65f:
        pop ecx
    L_0045b660:
        mov dword ptr [data_004981d0],esi
    L_0045b666:
        mov dword ptr [data_004981cc],esi
    L_0045b66c:
        mov ebx,473AA4h
    L_0045b671:
        mov dword ptr [data_00477624],esi
    L_0045b677:
        jmp asm_target_0045b7c8
    L_0045b67c:
        push 30h
    L_0045b67e:
        push 1
    L_0045b680:
        call asm_FUN_0045794d_0045794d
    L_0045b685:
        mov ebx,eax
    L_0045b687:
        cmp ebx,esi
    L_0045b689:
        pop ecx
    L_0045b68a:
        pop ecx
    L_0045b68b:
        je short L_0045b6b2
    L_0045b68d:
        mov esi,dword ptr [data_00473ad4]
    L_0045b693:
        push 0Ch
    L_0045b695:
        pop ecx
    L_0045b696:
        mov edi,ebx
    L_0045b698:
        push 4
    L_0045b69a:
        rep movsd
    L_0045b69c:
        call asm_malloc_00452706
    L_0045b6a1:
        xor esi,esi
    L_0045b6a3:
        cmp eax,esi
    L_0045b6a5:
        pop ecx
    L_0045b6a6:
        mov dword ptr [ebp-8],eax
    L_0045b6a9:
        jne short L_0045b6ba
    L_0045b6ab:
        push ebx
    L_0045b6ac:
        call asm_free_00452422
    L_0045b6b1:
        pop ecx
    L_0045b6b2:
        xor eax,eax
    L_0045b6b4:
        inc eax
    L_0045b6b5:
        jmp asm_target_0045b7e3
    L_0045b6ba:
        mov dword ptr [eax],esi
    L_0045b6bc:
        cmp dword ptr [data_0047765c],esi
    L_0045b6c2:
        je asm_target_0045b771
    L_0045b6c8:
        push 4
    L_0045b6ca:
        call asm_malloc_00452706
    L_0045b6cf:
        cmp eax,esi
    L_0045b6d1:
        pop ecx
    L_0045b6d2:
        mov dword ptr [data_004981d0],eax
    L_0045b6d7:
        jne short L_0045b6de
    L_0045b6d9:
        xor esi,esi
    L_0045b6db:
        inc esi
    L_0045b6dc:
        jmp short L_0045b726
    L_0045b6de:
        mov dword ptr [eax],esi
    L_0045b6e0:
        movzx esi,word ptr [data_00477686]
    L_0045b6e7:
        push ebx
    L_0045b6e8:
        push 0Eh
    L_0045b6ea:
        push esi
    L_0045b6eb:
        push 1
    L_0045b6ed:
        call asm_FUN_0046041e_0046041e
    L_0045b6f2:
        mov dword ptr [ebp-4],eax
    L_0045b6f5:
        lea eax,[ebx+4]
    L_0045b6f8:
        push eax
    L_0045b6f9:
        push 0Fh
    L_0045b6fb:
        push esi
    L_0045b6fc:
        push 1
    L_0045b6fe:
        call asm_FUN_0046041e_0046041e
    L_0045b703:
        or dword ptr [ebp-4],eax
    L_0045b706:
        lea edi,[ebx+8]
    L_0045b709:
        push edi
    L_0045b70a:
        push 10h
    L_0045b70c:
        push esi
    L_0045b70d:
        push 1
    L_0045b70f:
        call asm_FUN_0046041e_0046041e
    L_0045b714:
        add esp,30h
    L_0045b717:
        or eax,dword ptr [ebp-4]
    L_0045b71a:
        je short L_0045b73d
    L_0045b71c:
        push ebx
    L_0045b71d:
        call asm_free_lconv_num_0045b5bc
    L_0045b722:
        pop ecx
    L_0045b723:
        or esi,0FFFFFFFFh
    L_0045b726:
        push ebx
    L_0045b727:
        call asm_free_00452422
    L_0045b72c:
        push dword ptr [ebp-8]
    L_0045b72f:
        call asm_free_00452422
    L_0045b734:
        pop ecx
    L_0045b735:
        pop ecx
    L_0045b736:
        mov eax,esi
    L_0045b738:
        jmp asm_target_0045b7e3
    L_0045b73d:
        mov eax,dword ptr [edi]
    L_0045b73f:
        jmp short L_0045b753
    L_0045b741:
        mov cl,byte ptr [eax]
    L_0045b743:
        cmp cl,30h
    L_0045b746:
        jl short L_0045b75a
    L_0045b748:
        cmp cl,39h
    L_0045b74b:
        jg short L_0045b75a
    L_0045b74d:
        sub cl,30h
    L_0045b750:
        mov byte ptr [eax],cl
    L_0045b752:
        inc eax
    L_0045b753:
        cmp byte ptr [eax],0
    L_0045b756:
        jne short L_0045b741
    L_0045b758:
        jmp short L_0045b78e
    L_0045b75a:
        cmp cl,3Bh
    L_0045b75d:
        jne short L_0045b752
    L_0045b75f:
        mov esi,eax
    L_0045b761:
        lea edi,[esi+1]
    L_0045b764:
        mov cl,byte ptr [edi]
    L_0045b766:
        mov byte ptr [esi],cl
    L_0045b768:
        mov esi,edi
    L_0045b76a:
        cmp byte ptr [esi],0
    L_0045b76d:
        jne short L_0045b761
    L_0045b76f:
        jmp short L_0045b753
    L_0045b771:
        mov eax,dword ptr [data_00473aa4]
    L_0045b776:
        mov dword ptr [data_004981d0],esi
    L_0045b77c:
        mov dword ptr [ebx],eax
    L_0045b77e:
        mov eax,dword ptr [data_00473aa8]
    L_0045b783:
        mov dword ptr [ebx+4],eax
    L_0045b786:
        mov eax,dword ptr [data_00473aac]
    L_0045b78b:
        mov dword ptr [ebx+8],eax
    L_0045b78e:
        mov eax,dword ptr [data_004981cc]
    L_0045b793:
        test eax,eax
    L_0045b795:
        je short L_0045b7ba
    L_0045b797:
        cmp dword ptr [eax],0
    L_0045b79a:
        jne short L_0045b7ba
    L_0045b79c:
        mov ecx,dword ptr [data_0047320c]
    L_0045b7a2:
        cmp eax,dword ptr [ecx+2Ch]
    L_0045b7a5:
        je short L_0045b7ba
    L_0045b7a7:
        push eax
    L_0045b7a8:
        call asm_free_00452422
    L_0045b7ad:
        push dword ptr [data_00477624]
    L_0045b7b3:
        call asm_free_00452422
    L_0045b7b8:
        pop ecx
    L_0045b7b9:
        pop ecx
    L_0045b7ba:
        mov eax,dword ptr [ebp-8]
    L_0045b7bd:
        mov dword ptr [data_004981cc],eax
    L_0045b7c2:
        mov dword ptr [data_00477624],ebx
    L_0045b7c8:
        mov dword ptr [data_00473ad4],ebx
    L_0045b7ce:
        mov eax,dword ptr [ebx]
    L_0045b7d0:
        mov al,byte ptr [eax]
    L_0045b7d2:
        mov byte ptr [data_00473af4],al
    L_0045b7d7:
        mov dword ptr [data_00473af8],1
    L_0045b7e1:
        xor eax,eax
    L_0045b7e3:
        pop edi
    L_0045b7e4:
        pop esi
    L_0045b7e5:
        pop ebx
    L_0045b7e6:
        leave
    L_0045b7e7:
        ret
    }
}
