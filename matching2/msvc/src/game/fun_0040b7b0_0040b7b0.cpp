#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405F70..0x0040605B: ItemManager_DestroyRetail
// Naked body preserves the retail register/stack ABI.

// 0x0040B7B0..0x0040B919: FUN_0040b7b0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040b7b0_0040b7b0() {
    __asm {
    L_0040b7b0:
        mov eax,dword ptr [esp+4]
    L_0040b7b4:
        push ebx
    L_0040b7b5:
        mov ebx,dword ptr [data_004660b0]
    L_0040b7bb:
        push ebp
    L_0040b7bc:
        mov ebp,dword ptr [data_004660b4]
    L_0040b7c2:
        push esi
    L_0040b7c3:
        mov esi,dword ptr [eax+8]
    L_0040b7c6:
        test esi,esi
    L_0040b7c8:
        push edi
    L_0040b7c9:
        mov edi,dword ptr [data_00491be4]
    L_0040b7cf:
        je short L_0040b7f4
    L_0040b7d1:
        push 492274h
    L_0040b7d6:
        call ebx
    L_0040b7d8:
        inc byte ptr [data_0049231c]
    L_0040b7de:
        mov ecx,esi
    L_0040b7e0:
        mov edx,edi
    L_0040b7e2:
        call asm_Scheduler_Remove_00449f60
    L_0040b7e7:
        push 492274h
    L_0040b7ec:
        call ebp
    L_0040b7ee:
        dec byte ptr [data_0049231c]
    L_0040b7f4:
        mov ecx,dword ptr [esp+14h]
    L_0040b7f8:
        mov esi,dword ptr [ecx+0Ch]
    L_0040b7fb:
        test esi,esi
    L_0040b7fd:
        mov edi,dword ptr [data_00491be4]
    L_0040b803:
        je short L_0040b828
    L_0040b805:
        push 492274h
    L_0040b80a:
        call ebx
    L_0040b80c:
        inc byte ptr [data_0049231c]
    L_0040b812:
        mov ecx,esi
    L_0040b814:
        mov edx,edi
    L_0040b816:
        call asm_Scheduler_Remove_00449f60
    L_0040b81b:
        push 492274h
    L_0040b820:
        call ebp
    L_0040b822:
        dec byte ptr [data_0049231c]
    L_0040b828:
        mov edi,dword ptr [data_00491c10]
    L_0040b82e:
        xor esi,esi
    L_0040b830:
        call asm_AnimationManager_ClearIndexedResources_00447f70
    L_0040b835:
        mov ebp,dword ptr [esp+14h]
    L_0040b839:
        mov esi,dword ptr [ebp+18h]
    L_0040b83c:
        xor ebx,ebx
    L_0040b83e:
        cmp esi,ebx
    L_0040b840:
        je short L_0040b852
    L_0040b842:
        mov eax,esi
    L_0040b844:
        call asm_FUN_0040b3a0_0040b3a0
    L_0040b849:
        push esi
    L_0040b84a:
        call asm_free_004524a1
    L_0040b84f:
        add esp,4
    L_0040b852:
        mov esi,dword ptr [data_00491c10]
    L_0040b858:
        add esi,3AD0E0h
    L_0040b85e:
        mov dword ptr [ebp+18h],ebx
    L_0040b861:
        mov edi,dword ptr [esi]
    L_0040b863:
        cmp edi,ebx
    L_0040b865:
        je short L_0040b879
    L_0040b867:
        call asm_FUN_00447810_00447810
    L_0040b86c:
        mov edx,dword ptr [esi]
    L_0040b86e:
        push edx
    L_0040b86f:
        call asm_free_004524a1
    L_0040b874:
        add esp,4
    L_0040b877:
        mov dword ptr [esi],ebx
    L_0040b879:
        mov esi,dword ptr [data_00491c10]
    L_0040b87f:
        mov edi,dword ptr [esi+3AD0E4h]
    L_0040b885:
        add esi,3AD0E4h
    L_0040b88b:
        cmp edi,ebx
    L_0040b88d:
        je short L_0040b8a1
    L_0040b88f:
        call asm_FUN_00447810_00447810
    L_0040b894:
        mov eax,dword ptr [esi]
    L_0040b896:
        push eax
    L_0040b897:
        call asm_free_004524a1
    L_0040b89c:
        add esp,4
    L_0040b89f:
        mov dword ptr [esi],ebx
    L_0040b8a1:
        mov esi,dword ptr [data_00491c10]
    L_0040b8a7:
        mov edi,dword ptr [esi+3AD0E8h]
    L_0040b8ad:
        add esi,3AD0E8h
    L_0040b8b3:
        cmp edi,ebx
    L_0040b8b5:
        je short L_0040b8c9
    L_0040b8b7:
        call asm_FUN_00447810_00447810
    L_0040b8bc:
        mov ecx,dword ptr [esi]
    L_0040b8be:
        push ecx
    L_0040b8bf:
        call asm_free_004524a1
    L_0040b8c4:
        add esp,4
    L_0040b8c7:
        mov dword ptr [esi],ebx
    L_0040b8c9:
        mov esi,dword ptr [data_00491c10]
    L_0040b8cf:
        mov edi,dword ptr [esi+3AD0ECh]
    L_0040b8d5:
        add esi,3AD0ECh
    L_0040b8db:
        cmp edi,ebx
    L_0040b8dd:
        je short L_0040b8f1
    L_0040b8df:
        call asm_FUN_00447810_00447810
    L_0040b8e4:
        mov edx,dword ptr [esi]
    L_0040b8e6:
        push edx
    L_0040b8e7:
        call asm_free_004524a1
    L_0040b8ec:
        add esp,4
    L_0040b8ef:
        mov dword ptr [esi],ebx
    L_0040b8f1:
        mov eax,dword ptr [ebp+14h]
    L_0040b8f4:
        cmp eax,ebx
    L_0040b8f6:
        je short L_0040b904
    L_0040b8f8:
        push eax
    L_0040b8f9:
        call asm_free_00452422
    L_0040b8fe:
        add esp,4
    L_0040b901:
        mov dword ptr [ebp+14h],ebx
    L_0040b904:
        pop edi
    L_0040b905:
        pop esi
    L_0040b906:
        mov dword ptr [ebp+14h],ebx
    L_0040b909:
        pop ebp
    L_0040b90a:
        mov dword ptr [data_00477700],ebx
    L_0040b910:
        mov dword ptr [data_004918a4],ebx
    L_0040b916:
        pop ebx
    L_0040b917:
        ret 4
    }
}
