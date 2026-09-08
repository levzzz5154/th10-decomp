#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045B81B..0x0045B8F3: ___free_lconv_mon
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_free_lconv_mon_0045b81b() {
    __asm {
    L_0045b81b:
        push esi
    L_0045b81c:
        mov esi,dword ptr [esp+8]
    L_0045b820:
        test esi,esi
    L_0045b822:
        je asm_target_0045b8f2
    L_0045b828:
        mov eax,dword ptr [esi+0Ch]
    L_0045b82b:
        mov ecx,dword ptr [data_00473ad4]
    L_0045b831:
        cmp eax,dword ptr [ecx+0Ch]
    L_0045b834:
        je short L_0045b845
    L_0045b836:
        cmp eax,dword ptr [data_00473ab0]
    L_0045b83c:
        je short L_0045b845
    L_0045b83e:
        push eax
    L_0045b83f:
        call asm_free_00452422
    L_0045b844:
        pop ecx
    L_0045b845:
        mov eax,dword ptr [esi+10h]
    L_0045b848:
        mov ecx,dword ptr [data_00473ad4]
    L_0045b84e:
        cmp eax,dword ptr [ecx+10h]
    L_0045b851:
        je short L_0045b862
    L_0045b853:
        cmp eax,dword ptr [data_00473ab4]
    L_0045b859:
        je short L_0045b862
    L_0045b85b:
        push eax
    L_0045b85c:
        call asm_free_00452422
    L_0045b861:
        pop ecx
    L_0045b862:
        mov eax,dword ptr [esi+14h]
    L_0045b865:
        mov ecx,dword ptr [data_00473ad4]
    L_0045b86b:
        cmp eax,dword ptr [ecx+14h]
    L_0045b86e:
        je short L_0045b87f
    L_0045b870:
        cmp eax,dword ptr [data_00473ab8]
    L_0045b876:
        je short L_0045b87f
    L_0045b878:
        push eax
    L_0045b879:
        call asm_free_00452422
    L_0045b87e:
        pop ecx
    L_0045b87f:
        mov eax,dword ptr [esi+18h]
    L_0045b882:
        mov ecx,dword ptr [data_00473ad4]
    L_0045b888:
        cmp eax,dword ptr [ecx+18h]
    L_0045b88b:
        je short L_0045b89c
    L_0045b88d:
        cmp eax,dword ptr [data_00473abc]
    L_0045b893:
        je short L_0045b89c
    L_0045b895:
        push eax
    L_0045b896:
        call asm_free_00452422
    L_0045b89b:
        pop ecx
    L_0045b89c:
        mov eax,dword ptr [esi+1Ch]
    L_0045b89f:
        mov ecx,dword ptr [data_00473ad4]
    L_0045b8a5:
        cmp eax,dword ptr [ecx+1Ch]
    L_0045b8a8:
        je short L_0045b8b9
    L_0045b8aa:
        cmp eax,dword ptr [data_00473ac0]
    L_0045b8b0:
        je short L_0045b8b9
    L_0045b8b2:
        push eax
    L_0045b8b3:
        call asm_free_00452422
    L_0045b8b8:
        pop ecx
    L_0045b8b9:
        mov eax,dword ptr [esi+20h]
    L_0045b8bc:
        mov ecx,dword ptr [data_00473ad4]
    L_0045b8c2:
        cmp eax,dword ptr [ecx+20h]
    L_0045b8c5:
        je short L_0045b8d6
    L_0045b8c7:
        cmp eax,dword ptr [data_00473ac4]
    L_0045b8cd:
        je short L_0045b8d6
    L_0045b8cf:
        push eax
    L_0045b8d0:
        call asm_free_00452422
    L_0045b8d5:
        pop ecx
    L_0045b8d6:
        mov esi,dword ptr [esi+24h]
    L_0045b8d9:
        mov eax,dword ptr [data_00473ad4]
    L_0045b8de:
        cmp esi,dword ptr [eax+24h]
    L_0045b8e1:
        je short L_0045b8f2
    L_0045b8e3:
        cmp esi,dword ptr [data_00473ac8]
    L_0045b8e9:
        je short L_0045b8f2
    L_0045b8eb:
        push esi
    L_0045b8ec:
        call asm_free_00452422
    L_0045b8f1:
        pop ecx
    L_0045b8f2:
        pop esi
    L_0045b8f3:
        ret
    }
}
