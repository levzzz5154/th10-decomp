#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004659A0..0x004659B1: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004659a0() {
    __asm {
    L_004659a0:
        push edi
    L_004659a1:
        mov ecx,80h
    L_004659a6:
        or eax,0FFFFFFFFh
    L_004659a9:
        mov edi,492998h
    L_004659ae:
        rep stosd
    L_004659b0:
        pop edi
    L_004659b1:
        ret
    }
}
