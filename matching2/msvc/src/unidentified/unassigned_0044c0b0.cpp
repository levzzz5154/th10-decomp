#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044C0B0..0x0044C0D3: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044c0b0() {
    __asm {
    L_0044c0b0:
        push esi
    L_0044c0b1:
        mov esi,edx
    L_0044c0b3:
        and esi,3
    L_0044c0b6:
        sub edx,esi
    L_0044c0b8:
        xor eax,eax
    L_0044c0ba:
        test edx,edx
    L_0044c0bc:
        jle short L_0044c0d2
    L_0044c0be:
        lea esi,[edx-1]
    L_0044c0c1:
        shr esi,2
    L_0044c0c4:
        inc esi
    L_0044c0c5:
        mov dl,byte ptr [ecx]
    L_0044c0c7:
        add dl,al
    L_0044c0c9:
        add ecx,4
    L_0044c0cc:
        dec esi
    L_0044c0cd:
        movzx eax,dl
    L_0044c0d0:
        jne short L_0044c0c5
    L_0044c0d2:
        pop esi
    L_0044c0d3:
        ret
    }
}
