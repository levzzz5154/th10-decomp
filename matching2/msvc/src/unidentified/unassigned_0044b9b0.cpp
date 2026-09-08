#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044B9B0..0x0044B9D6: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044b9b0() {
    __asm {
    L_0044b9b0:
        xor eax,eax
    L_0044b9b2:
        mov ax,word ptr [ecx]
    L_0044b9b5:
        xor ax,9630h
    L_0044b9b9:
        xor edx,edx
    L_0044b9bb:
        sub eax,6553h
    L_0044b9c0:
        mov dx,ax
    L_0044b9c3:
        shr dx,0Eh
    L_0044b9c7:
        shl eax,2
    L_0044b9ca:
        add eax,edx
    L_0044b9cc:
        mov edx,dword ptr [ecx+4]
    L_0044b9cf:
        inc edx
    L_0044b9d0:
        mov word ptr [ecx],ax
    L_0044b9d3:
        mov dword ptr [ecx+4],edx
    L_0044b9d6:
        ret
    }
}
