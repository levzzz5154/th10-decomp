#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00428AD0..0x00428B04: FUN_00428ad0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00428ad0_00428ad0() {
    __asm {
    L_00428ad0:
        mov dword ptr [edx+4Ch],0
    L_00428ad7:
        mov eax,dword ptr [ecx+3504h]
    L_00428add:
        test eax,eax
    L_00428adf:
        je short L_00428b00
    L_00428ae1:
        mov dword ptr [edx+4Ch],eax
    L_00428ae4:
        fld dword ptr [eax+1068h]
    L_00428aea:
        fabs
    L_00428aec:
        fcomp dword ptr [data_00470b4c]
    L_00428af2:
        fnstsw ax
    L_00428af4:
        test ah,41h
    L_00428af7:
        jne short L_00428b00
    L_00428af9:
        mov dword ptr [edx+4Ch],0
    L_00428b00:
        xor eax,eax
    L_00428b02:
        ret 4
    }
}
