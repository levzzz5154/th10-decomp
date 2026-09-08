#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00460F76..0x00461003: __hw_cw
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_hw_cw_00460f76() {
    __asm {
    L_00460f76:
        xor eax,eax
    L_00460f78:
        test bl,10h
    L_00460f7b:
        je short L_00460f7e
    L_00460f7d:
        inc eax
    L_00460f7e:
        test bl,8
    L_00460f81:
        je short L_00460f86
    L_00460f83:
        or eax,4
    L_00460f86:
        test bl,4
    L_00460f89:
        je short L_00460f8e
    L_00460f8b:
        or eax,8
    L_00460f8e:
        test bl,2
    L_00460f91:
        je short L_00460f96
    L_00460f93:
        or eax,10h
    L_00460f96:
        test bl,1
    L_00460f99:
        je short L_00460f9e
    L_00460f9b:
        or eax,20h
    L_00460f9e:
        test ebx,80000h
    L_00460fa4:
        je short L_00460fa9
    L_00460fa6:
        or eax,2
    L_00460fa9:
        mov ecx,ebx
    L_00460fab:
        mov edx,300h
    L_00460fb0:
        and ecx,edx
    L_00460fb2:
        push esi
    L_00460fb3:
        mov esi,200h
    L_00460fb8:
        je short L_00460fdd
    L_00460fba:
        cmp ecx,100h
    L_00460fc0:
        je short L_00460fd8
    L_00460fc2:
        cmp ecx,esi
    L_00460fc4:
        je short L_00460fd1
    L_00460fc6:
        cmp ecx,edx
    L_00460fc8:
        jne short L_00460fdd
    L_00460fca:
        or eax,0C00h
    L_00460fcf:
        jmp short L_00460fdd
    L_00460fd1:
        or eax,800h
    L_00460fd6:
        jmp short L_00460fdd
    L_00460fd8:
        or eax,400h
    L_00460fdd:
        mov ecx,ebx
    L_00460fdf:
        and ecx,30000h
    L_00460fe5:
        je short L_00460ff3
    L_00460fe7:
        cmp ecx,10000h
    L_00460fed:
        jne short L_00460ff5
    L_00460fef:
        or eax,esi
    L_00460ff1:
        jmp short L_00460ff5
    L_00460ff3:
        or eax,edx
    L_00460ff5:
        test ebx,40000h
    L_00460ffb:
        pop esi
    L_00460ffc:
        je short L_00461003
    L_00460ffe:
        or eax,1000h
    L_00461003:
        ret
    }
}
