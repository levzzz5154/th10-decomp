#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043CB80..0x0043CBD7: EntityScript_NextRandomModulo
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_EntityScript_NextRandomModulo_0043cb80() {
    __asm {
    L_0043cb80:
        xor eax,eax
    L_0043cb82:
        test edi,edi
    L_0043cb84:
        je short L_0043cbd7
    L_0043cb86:
        mov ax,word ptr [ecx]
    L_0043cb89:
        xor ax,9630h
    L_0043cb8d:
        xor edx,edx
    L_0043cb8f:
        push esi
    L_0043cb90:
        xor esi,esi
    L_0043cb92:
        sub eax,6553h
    L_0043cb97:
        mov dx,ax
    L_0043cb9a:
        shl eax,2
    L_0043cb9d:
        shr dx,0Eh
    L_0043cba1:
        add edx,eax
    L_0043cba3:
        mov eax,edx
    L_0043cba5:
        xor eax,9630h
    L_0043cbaa:
        sub eax,6553h
    L_0043cbaf:
        mov si,ax
    L_0043cbb2:
        shr si,0Eh
    L_0043cbb6:
        shl eax,2
    L_0043cbb9:
        mov word ptr [ecx],dx
    L_0043cbbc:
        add esi,eax
    L_0043cbbe:
        add dword ptr [ecx+4],2
    L_0043cbc2:
        movzx eax,dx
    L_0043cbc5:
        mov word ptr [ecx],si
    L_0043cbc8:
        movzx ecx,si
    L_0043cbcb:
        shl eax,10h
    L_0043cbce:
        or eax,ecx
    L_0043cbd0:
        xor edx,edx
    L_0043cbd2:
        div edi
    L_0043cbd4:
        pop esi
    L_0043cbd5:
        mov eax,edx
    L_0043cbd7:
        ret
    }
}
