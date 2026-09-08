#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045A7B4..0x0045A82C: __store_num
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_store_num_0045a7b4() {
    __asm {
    L_0045a7b4:
        push ebp
    L_0045a7b5:
        mov ebp,esp
    L_0045a7b7:
        push ecx
    L_0045a7b8:
        push ebx
    L_0045a7b9:
        push esi
    L_0045a7ba:
        mov esi,edx
    L_0045a7bc:
        xor edx,edx
    L_0045a7be:
        cmp dword ptr [ebp+8],edx
    L_0045a7c1:
        mov dword ptr [ebp-4],edx
    L_0045a7c4:
        je short L_0045a7fb
    L_0045a7c6:
        cmp dword ptr [ecx],1
    L_0045a7c9:
        mov esi,dword ptr [edi]
    L_0045a7cb:
        jbe short L_0045a7e6
    L_0045a7cd:
        push 0Ah
    L_0045a7cf:
        cdq
    L_0045a7d0:
        pop ebx
    L_0045a7d1:
        idiv ebx
    L_0045a7d3:
        add dl,30h
    L_0045a7d6:
        mov byte ptr [esi],dl
    L_0045a7d8:
        inc esi
    L_0045a7d9:
        dec dword ptr [ecx]
    L_0045a7db:
        test eax,eax
    L_0045a7dd:
        mov edx,dword ptr [ecx]
    L_0045a7df:
        jle short L_0045a7e6
    L_0045a7e1:
        cmp edx,1
    L_0045a7e4:
        ja short L_0045a7cd
    L_0045a7e6:
        mov eax,dword ptr [edi]
    L_0045a7e8:
        mov dword ptr [edi],esi
    L_0045a7ea:
        dec esi
    L_0045a7eb:
        mov dl,byte ptr [eax]
    L_0045a7ed:
        mov cl,byte ptr [esi]
    L_0045a7ef:
        mov byte ptr [esi],dl
    L_0045a7f1:
        dec esi
    L_0045a7f2:
        mov byte ptr [eax],cl
    L_0045a7f4:
        inc eax
    L_0045a7f5:
        cmp eax,esi
    L_0045a7f7:
        jb short L_0045a7eb
    L_0045a7f9:
        jmp short L_0045a829
    L_0045a7fb:
        cmp esi,dword ptr [ecx]
    L_0045a7fd:
        jae short L_0045a827
    L_0045a7ff:
        dec esi
    L_0045a800:
        lea edx,[esi+1]
    L_0045a803:
        test edx,edx
    L_0045a805:
        je short L_0045a81e
    L_0045a807:
        push 0Ah
    L_0045a809:
        cdq
    L_0045a80a:
        pop ebx
    L_0045a80b:
        idiv ebx
    L_0045a80d:
        mov ebx,dword ptr [edi]
    L_0045a80f:
        add dl,30h
    L_0045a812:
        inc dword ptr [ebp-4]
    L_0045a815:
        mov byte ptr [esi+ebx],dl
    L_0045a818:
        dec esi
    L_0045a819:
        cmp esi,0FFFFFFFFh
    L_0045a81c:
        jne short L_0045a807
    L_0045a81e:
        mov eax,dword ptr [ebp-4]
    L_0045a821:
        add dword ptr [edi],eax
    L_0045a823:
        sub dword ptr [ecx],eax
    L_0045a825:
        jmp short L_0045a829
    L_0045a827:
        mov dword ptr [ecx],edx
    L_0045a829:
        pop esi
    L_0045a82a:
        pop ebx
    L_0045a82b:
        leave
    L_0045a82c:
        ret
    }
}
