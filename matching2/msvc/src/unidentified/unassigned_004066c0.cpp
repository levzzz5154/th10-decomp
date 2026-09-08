#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004066C0..0x004066D8: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004066c0() {
    __asm {
    L_004066c0:
        push esi
    L_004066c1:
        xor esi,esi
    L_004066c3:
        mov ecx,esi
    L_004066c5:
        mov eax,edi
    L_004066c7:
        call asm_FUN_004066e0_004066e0
    L_004066cc:
        inc esi
    L_004066cd:
        cmp esi,6
    L_004066d0:
        jl short L_004066c3
    L_004066d2:
        mov eax,1
    L_004066d7:
        pop esi
    L_004066d8:
        ret
    }
}
