#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045B7E8..0x0045B81A: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0045b7e8() {
    __asm {
    L_0045b7e8:
        xor dl,dl
    L_0045b7ea:
        cmp byte ptr [ecx],dl
    L_0045b7ec:
        je short L_0045b805
    L_0045b7ee:
        push ebx
    L_0045b7ef:
        push esi
    L_0045b7f0:
        mov al,byte ptr [ecx]
    L_0045b7f2:
        cmp al,30h
    L_0045b7f4:
        jl short L_0045b806
    L_0045b7f6:
        cmp al,39h
    L_0045b7f8:
        jg short L_0045b806
    L_0045b7fa:
        sub al,30h
    L_0045b7fc:
        mov byte ptr [ecx],al
    L_0045b7fe:
        inc ecx
    L_0045b7ff:
        cmp byte ptr [ecx],dl
    L_0045b801:
        jne short L_0045b7f0
    L_0045b803:
        pop esi
    L_0045b804:
        pop ebx
    L_0045b805:
        ret
    L_0045b806:
        cmp al,3Bh
    L_0045b808:
        jne short L_0045b7fe
    L_0045b80a:
        mov eax,ecx
    L_0045b80c:
        lea esi,[eax+1]
    L_0045b80f:
        mov bl,byte ptr [esi]
    L_0045b811:
        mov byte ptr [eax],bl
    L_0045b813:
        mov eax,esi
    L_0045b815:
        cmp byte ptr [eax],dl
    L_0045b817:
        jne short L_0045b80c
    L_0045b819:
        jmp short L_0045b7ff
    }
}
