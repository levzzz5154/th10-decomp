#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00460EE4..0x00460F75: __abstract_cw
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_abstract_cw_00460ee4() {
    __asm {
    L_00460ee4:
        xor eax,eax
    L_00460ee6:
        test bl,1
    L_00460ee9:
        je short L_00460eee
    L_00460eeb:
        push 10h
    L_00460eed:
        pop eax
    L_00460eee:
        test bl,4
    L_00460ef1:
        je short L_00460ef6
    L_00460ef3:
        or eax,8
    L_00460ef6:
        test bl,8
    L_00460ef9:
        je short L_00460efe
    L_00460efb:
        or eax,4
    L_00460efe:
        test bl,10h
    L_00460f01:
        je short L_00460f06
    L_00460f03:
        or eax,2
    L_00460f06:
        test bl,20h
    L_00460f09:
        je short L_00460f0e
    L_00460f0b:
        or eax,1
    L_00460f0e:
        test bl,2
    L_00460f11:
        je short L_00460f18
    L_00460f13:
        or eax,80000h
    L_00460f18:
        push ebp
    L_00460f19:
        movzx edx,bx
    L_00460f1c:
        push esi
    L_00460f1d:
        mov ecx,edx
    L_00460f1f:
        mov esi,0C00h
    L_00460f24:
        and ecx,esi
    L_00460f26:
        push edi
    L_00460f27:
        mov edi,300h
    L_00460f2c:
        mov ebp,200h
    L_00460f31:
        je short L_00460f54
    L_00460f33:
        cmp ecx,400h
    L_00460f39:
        je short L_00460f4f
    L_00460f3b:
        cmp ecx,800h
    L_00460f41:
        je short L_00460f4b
    L_00460f43:
        cmp ecx,esi
    L_00460f45:
        jne short L_00460f54
    L_00460f47:
        or eax,edi
    L_00460f49:
        jmp short L_00460f54
    L_00460f4b:
        or eax,ebp
    L_00460f4d:
        jmp short L_00460f54
    L_00460f4f:
        or eax,100h
    L_00460f54:
        and edx,edi
    L_00460f56:
        je short L_00460f63
    L_00460f58:
        cmp edx,ebp
    L_00460f5a:
        jne short L_00460f68
    L_00460f5c:
        or eax,10000h
    L_00460f61:
        jmp short L_00460f68
    L_00460f63:
        or eax,20000h
    L_00460f68:
        test bh,10h
    L_00460f6b:
        pop edi
    L_00460f6c:
        pop esi
    L_00460f6d:
        pop ebp
    L_00460f6e:
        je short L_00460f75
    L_00460f70:
        or eax,40000h
    L_00460f75:
        ret
    }
}
