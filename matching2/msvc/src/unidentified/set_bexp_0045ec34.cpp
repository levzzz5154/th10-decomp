#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045EC34..0x0045EC58: __set_bexp
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_set_bexp_0045ec34() {
    __asm {
    L_0045ec34:
        push ebp
    L_0045ec35:
        mov ebp,esp
    L_0045ec37:
        push ecx
    L_0045ec38:
        push ecx
    L_0045ec39:
        mov eax,dword ptr [ebp+10h]
    L_0045ec3c:
        fld qword ptr [ebp+8]
    L_0045ec3f:
        mov ecx,dword ptr [ebp+0Eh]
    L_0045ec42:
        fstp qword ptr [ebp-8]
    L_0045ec45:
        shl eax,4
    L_0045ec48:
        and ecx,0FFFF800Fh
    L_0045ec4e:
        or eax,ecx
    L_0045ec50:
        mov word ptr [ebp-2],ax
    L_0045ec54:
        fld qword ptr [ebp-8]
    L_0045ec57:
        leave
    L_0045ec58:
        ret
    }
}
