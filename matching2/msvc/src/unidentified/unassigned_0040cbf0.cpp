#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040CBF0..0x0040CC00: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040cbf0() {
    __asm {
    L_0040cbf0:
        push edi
    L_0040cbf1:
        mov edi,edx
    L_0040cbf3:
        add edi,4
    L_0040cbf6:
        mov ecx,0Ch
    L_0040cbfb:
        xor eax,eax
    L_0040cbfd:
        rep stosd
    L_0040cbff:
        pop edi
    L_0040cc00:
        ret
    }
}
