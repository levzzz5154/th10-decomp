#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045EDAB..0x0045EE00: FUN_0045edab
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045edab_0045edab() {
    __asm {
    L_0045edab:
        push ecx
    L_0045edac:
        push ecx
    L_0045edad:
        mov cl,byte ptr [esp+0Ch]
    L_0045edb1:
        test cl,1
    L_0045edb4:
        je short L_0045edc1
    L_0045edb6:
        fld tbyte ptr [data_00473da8]
    L_0045edbc:
        fistp dword ptr [esp+0Ch]
    L_0045edc0:
        wait
    L_0045edc1:
        test cl,8
    L_0045edc4:
        je short L_0045edd6
    L_0045edc6:
        wait
        fnstsw ax
    L_0045edc9:
        fld tbyte ptr [data_00473da8]
    L_0045edcf:
        fstp qword ptr [esp]
    L_0045edd2:
        wait
    L_0045edd3:
        wait
        fnstsw ax
    L_0045edd6:
        test cl,10h
    L_0045edd9:
        je short L_0045ede5
    L_0045eddb:
        fld tbyte ptr [data_00473db4]
    L_0045ede1:
        fstp qword ptr [esp]
    L_0045ede4:
        wait
    L_0045ede5:
        test cl,4
    L_0045ede8:
        je short L_0045edf3
    L_0045edea:
        fldz
    L_0045edec:
        fld1
    L_0045edee:
        fdivrp st(1),st
    L_0045edf0:
        fstp st(0)
    L_0045edf2:
        wait
    L_0045edf3:
        test cl,20h
    L_0045edf6:
        je short L_0045edfe
    L_0045edf8:
        fldpi
    L_0045edfa:
        fstp qword ptr [esp]
    L_0045edfd:
        wait
    L_0045edfe:
        pop ecx
    L_0045edff:
        pop ecx
    L_0045ee00:
        ret
    }
}
