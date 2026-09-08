#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045EBCB..0x0045EBF4: __set_exp
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_set_exp_0045ebcb() {
    __asm {
    L_0045ebcb:
        push ebp
    L_0045ebcc:
        mov ebp,esp
    L_0045ebce:
        push ecx
    L_0045ebcf:
        push ecx
    L_0045ebd0:
        mov eax,dword ptr [ebp+10h]
    L_0045ebd3:
        fld qword ptr [ebp+8]
    L_0045ebd6:
        mov ecx,dword ptr [ebp+0Eh]
    L_0045ebd9:
        fstp qword ptr [ebp-8]
    L_0045ebdc:
        add eax,3FEh
    L_0045ebe1:
        shl eax,4
    L_0045ebe4:
        and ecx,0FFFF800Fh
    L_0045ebea:
        or eax,ecx
    L_0045ebec:
        mov word ptr [ebp-2],ax
    L_0045ebf0:
        fld qword ptr [ebp-8]
    L_0045ebf3:
        leave
    L_0045ebf4:
        ret
    }
}
