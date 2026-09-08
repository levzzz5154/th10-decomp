#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045B5BC..0x0045B61A: ___free_lconv_num
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_free_lconv_num_0045b5bc() {
    __asm {
    L_0045b5bc:
        push esi
    L_0045b5bd:
        mov esi,dword ptr [esp+8]
    L_0045b5c1:
        test esi,esi
    L_0045b5c3:
        je short L_0045b619
    L_0045b5c5:
        mov eax,dword ptr [esi]
    L_0045b5c7:
        mov ecx,dword ptr [data_00473ad4]
    L_0045b5cd:
        cmp eax,dword ptr [ecx]
    L_0045b5cf:
        je short L_0045b5e0
    L_0045b5d1:
        cmp eax,dword ptr [data_00473aa4]
    L_0045b5d7:
        je short L_0045b5e0
    L_0045b5d9:
        push eax
    L_0045b5da:
        call asm_free_00452422
    L_0045b5df:
        pop ecx
    L_0045b5e0:
        mov eax,dword ptr [esi+4]
    L_0045b5e3:
        mov ecx,dword ptr [data_00473ad4]
    L_0045b5e9:
        cmp eax,dword ptr [ecx+4]
    L_0045b5ec:
        je short L_0045b5fd
    L_0045b5ee:
        cmp eax,dword ptr [data_00473aa8]
    L_0045b5f4:
        je short L_0045b5fd
    L_0045b5f6:
        push eax
    L_0045b5f7:
        call asm_free_00452422
    L_0045b5fc:
        pop ecx
    L_0045b5fd:
        mov esi,dword ptr [esi+8]
    L_0045b600:
        mov eax,dword ptr [data_00473ad4]
    L_0045b605:
        cmp esi,dword ptr [eax+8]
    L_0045b608:
        je short L_0045b619
    L_0045b60a:
        cmp esi,dword ptr [data_00473aac]
    L_0045b610:
        je short L_0045b619
    L_0045b612:
        push esi
    L_0045b613:
        call asm_free_00452422
    L_0045b618:
        pop ecx
    L_0045b619:
        pop esi
    L_0045b61a:
        ret
    }
}
