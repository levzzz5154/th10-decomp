#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004389A0..0x004389AF: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004389a0() {
    __asm {
    L_004389a0:
        push edi
    L_004389a1:
        xor eax,eax
    L_004389a3:
        mov ecx,16h
    L_004389a8:
        mov edi,edx
    L_004389aa:
        rep stosd
    L_004389ac:
        mov eax,edx
    L_004389ae:
        pop edi
    L_004389af:
        ret
    }
}
