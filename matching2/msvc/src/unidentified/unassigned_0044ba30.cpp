#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044BA30..0x0044BA7D: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044ba30() {
    __asm {
    L_0044ba30:
        xor eax,eax
    L_0044ba32:
        mov ax,word ptr [ecx]
    L_0044ba35:
        xor ax,9630h
    L_0044ba39:
        xor edx,edx
    L_0044ba3b:
        push esi
    L_0044ba3c:
        xor esi,esi
    L_0044ba3e:
        sub eax,6553h
    L_0044ba43:
        mov dx,ax
    L_0044ba46:
        shl eax,2
    L_0044ba49:
        shr dx,0Eh
    L_0044ba4d:
        add edx,eax
    L_0044ba4f:
        mov eax,edx
    L_0044ba51:
        xor eax,9630h
    L_0044ba56:
        sub eax,6553h
    L_0044ba5b:
        mov si,ax
    L_0044ba5e:
        shr si,0Eh
    L_0044ba62:
        shl eax,2
    L_0044ba65:
        mov word ptr [ecx],dx
    L_0044ba68:
        add esi,eax
    L_0044ba6a:
        add dword ptr [ecx+4],2
    L_0044ba6e:
        mov word ptr [ecx],si
    L_0044ba71:
        movzx eax,dx
    L_0044ba74:
        movzx ecx,si
    L_0044ba77:
        shl eax,10h
    L_0044ba7a:
        or eax,ecx
    L_0044ba7c:
        pop esi
    L_0044ba7d:
        ret
    }
}
