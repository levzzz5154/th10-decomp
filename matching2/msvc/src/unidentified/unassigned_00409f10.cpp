#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00409F10..0x00409F20: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00409f10() {
    __asm {
    L_00409f10:
        push edi
    L_00409f11:
        mov edi,edx
    L_00409f13:
        add edi,14h
    L_00409f16:
        mov ecx,873A8h
    L_00409f1b:
        xor eax,eax
    L_00409f1d:
        rep stosd
    L_00409f1f:
        pop edi
    L_00409f20:
        ret
    }
}
