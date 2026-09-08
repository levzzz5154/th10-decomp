#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045C527..0x0045C543: _GetPrimaryLen
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_GetPrimaryLen_0045c527() {
    __asm {
    L_0045c527:
        xor eax,eax
    L_0045c529:
        mov cl,byte ptr [edx]
    L_0045c52b:
        inc edx
    L_0045c52c:
        cmp cl,41h
    L_0045c52f:
        jl short L_0045c536
    L_0045c531:
        cmp cl,5Ah
    L_0045c534:
        jle short L_0045c540
    L_0045c536:
        cmp cl,61h
    L_0045c539:
        jl short L_0045c543
    L_0045c53b:
        cmp cl,7Ah
    L_0045c53e:
        jg short L_0045c543
    L_0045c540:
        inc eax
    L_0045c541:
        jmp short L_0045c529
    L_0045c543:
        ret
    }
}
