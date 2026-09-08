#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043E580..0x0043E59F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0043e580() {
    __asm {
    L_0043e580:
        push edi
    L_0043e581:
        xor eax,eax
    L_0043e583:
        mov ecx,14B4h
    L_0043e588:
        mov edi,edx
    L_0043e58a:
        rep stosd
    L_0043e58c:
        or eax,0FFFFFFFFh
    L_0043e58f:
        lea edi,[edx+408h]
    L_0043e595:
        mov ecx,80h
    L_0043e59a:
        rep stosd
    L_0043e59c:
        mov eax,edx
    L_0043e59e:
        pop edi
    L_0043e59f:
        ret
    }
}
