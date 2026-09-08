#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045D2CA..0x0045D2FB: __ZeroTail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ZeroTail_0045d2ca() {
    __asm {
    L_0045d2ca:
        mov eax,dword ptr [esp+8]
    L_0045d2ce:
        push 20h
    L_0045d2d0:
        pop ecx
    L_0045d2d1:
        cdq
    L_0045d2d2:
        idiv ecx
    L_0045d2d4:
        push 1Fh
    L_0045d2d6:
        pop ecx
    L_0045d2d7:
        sub ecx,edx
    L_0045d2d9:
        or edx,0FFFFFFFFh
    L_0045d2dc:
        shl edx,cl
    L_0045d2de:
        mov ecx,dword ptr [esp+4]
    L_0045d2e2:
        not edx
    L_0045d2e4:
        test dword ptr [ecx+eax*4],edx
    L_0045d2e7:
        je short L_0045d2f2
    L_0045d2e9:
        xor eax,eax
    L_0045d2eb:
        ret
    L_0045d2ec:
        cmp dword ptr [ecx+eax*4],0
    L_0045d2f0:
        jne short L_0045d2e9
    L_0045d2f2:
        inc eax
    L_0045d2f3:
        cmp eax,3
    L_0045d2f6:
        jl short L_0045d2ec
    L_0045d2f8:
        xor eax,eax
    L_0045d2fa:
        inc eax
    L_0045d2fb:
        ret
    }
}
