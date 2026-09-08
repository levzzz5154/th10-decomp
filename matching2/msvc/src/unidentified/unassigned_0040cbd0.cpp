#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040CBD0..0x0040CBE8: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040cbd0() {
    __asm {
    L_0040cbd0:
        push edi
    L_0040cbd1:
        xor eax,eax
    L_0040cbd3:
        mov ecx,0Fh
    L_0040cbd8:
        mov edi,edx
    L_0040cbda:
        rep stosd
    L_0040cbdc:
        mov eax,42000000h
    L_0040cbe1:
        mov dword ptr [edx+38h],eax
    L_0040cbe4:
        mov dword ptr [edx+34h],eax
    L_0040cbe7:
        pop edi
    L_0040cbe8:
        ret
    }
}
