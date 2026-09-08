#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045DFFA..0x0045E039: __ms_p5_test_fdiv
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ms_p5_test_fdiv_0045dffa() {
    __asm {
    L_0045dffa:
        push ebp
    L_0045dffb:
        mov ebp,esp
    L_0045dffd:
        sub esp,18h
    L_0045e000:
        fld qword ptr [data_0046c568]
    L_0045e006:
        fstp qword ptr [ebp-8]
    L_0045e009:
        fld qword ptr [data_0046c560]
    L_0045e00f:
        fstp qword ptr [ebp-10h]
    L_0045e012:
        fld qword ptr [ebp-10h]
    L_0045e015:
        fdiv qword ptr [ebp-8]
    L_0045e018:
        fmul qword ptr [ebp-8]
    L_0045e01b:
        fsubr qword ptr [ebp-10h]
    L_0045e01e:
        fstp qword ptr [ebp-18h]
    L_0045e021:
        fld qword ptr [ebp-18h]
    L_0045e024:
        fcomp qword ptr [data_0046ac28]
    L_0045e02a:
        fnstsw ax
    L_0045e02c:
        test ah,41h
    L_0045e02f:
        jne short L_0045e036
    L_0045e031:
        xor eax,eax
    L_0045e033:
        inc eax
    L_0045e034:
        leave
    L_0045e035:
        ret
    L_0045e036:
        xor eax,eax
    L_0045e038:
        leave
    L_0045e039:
        ret
    }
}
