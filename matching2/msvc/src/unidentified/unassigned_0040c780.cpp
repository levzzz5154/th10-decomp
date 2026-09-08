#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C780..0x0040C7AE: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040c780() {
    __asm {
    L_0040c780:
        push esi
    L_0040c781:
        mov esi,dword ptr [ecx+1034h]
    L_0040c787:
        test esi,esi
    L_0040c789:
        mov dword ptr [ecx],46D0D8h
    L_0040c78f:
        je short L_0040c7ad
    L_0040c791:
        push edi
    L_0040c792:
        mov eax,dword ptr [esi]
    L_0040c794:
        mov edi,dword ptr [esi+4]
    L_0040c797:
        push eax
    L_0040c798:
        call asm_free_004524a1
    L_0040c79d:
        push esi
    L_0040c79e:
        call asm_free_004524a1
    L_0040c7a3:
        add esp,8
    L_0040c7a6:
        test edi,edi
    L_0040c7a8:
        mov esi,edi
    L_0040c7aa:
        jne short L_0040c792
    L_0040c7ac:
        pop edi
    L_0040c7ad:
        pop esi
    L_0040c7ae:
        ret
    }
}
