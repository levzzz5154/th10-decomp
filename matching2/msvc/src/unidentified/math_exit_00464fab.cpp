#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00464FAB..0x00464FD4: __math_exit
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_math_exit_00464fab() {
    __asm {
    L_00464fab:
        mov ax,word ptr [esp]
    L_00464faf:
        cmp ax,27Fh
    L_00464fb3:
        je short L_00464fd3
    L_00464fb5:
        TH10_OPERAND16()
        and eax,20h
    L_00464fb9:
        je short L_00464fd0
    L_00464fbb:
        wait
        fnstsw ax
    L_00464fbe:
        TH10_OPERAND16()
        and eax,20h
    L_00464fc2:
        je short L_00464fd0
    L_00464fc4:
        mov eax,8
    L_00464fc9:
        call asm_startOneArgErrorHandling_00464eb7
    L_00464fce:
        pop edx
    L_00464fcf:
        ret
    L_00464fd0:
        fldcw word ptr [esp]
    L_00464fd3:
        pop edx
    L_00464fd4:
        ret
    }
}
