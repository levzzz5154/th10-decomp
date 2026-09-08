#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00464033..0x00464109: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00464033() {
    __asm {
    L_00464033:
        call asm_target_004640f9
    L_00464038:
        fxch
    L_0046403a:
        fstp st(0)
    L_0046403c:
        ret
    L_0046403d:
        call asm_target_004640f9
    L_00464042:
        jmp short L_0046403a
    L_00464044:
        fstp st(0)
    L_00464046:
        fstp st(0)
    L_00464048:
        fldz
    L_0046404a:
        ret
    L_0046404b:
        fstp st(0)
    L_0046404d:
        fstp st(0)
    L_0046404f:
        fld1
    L_00464051:
        ret
    L_00464052:
        fstp tbyte ptr [ebp-9Eh]
    L_00464058:
        fld tbyte ptr [ebp-9Eh]
    L_0046405e:
        test byte ptr [ebp-97h],40h
    L_00464065:
        je short L_0046406f
    L_00464067:
        mov byte ptr [ebp-90h],7
    L_0046406e:
        ret
    L_0046406f:
        mov byte ptr [ebp-90h],1
    L_00464076:
        fadd qword ptr [data_00477084]
    L_0046407c:
        ret
    L_0046407d:
        fxch
    L_0046407f:
        fstp tbyte ptr [ebp-9Eh]
    L_00464085:
        fld tbyte ptr [ebp-9Eh]
    L_0046408b:
        test byte ptr [ebp-97h],40h
    L_00464092:
        je short L_0046409d
    L_00464094:
        mov byte ptr [ebp-90h],7
    L_0046409b:
        jmp short L_004640a4
    L_0046409d:
        mov byte ptr [ebp-90h],1
    L_004640a4:
        faddp st(1),st
    L_004640a6:
        ret
    L_004640a7:
        fstp tbyte ptr [ebp-9Eh]
    L_004640ad:
        fld tbyte ptr [ebp-9Eh]
    L_004640b3:
        test byte ptr [ebp-97h],40h
    L_004640ba:
        je short L_004640dc
    L_004640bc:
        fxch
    L_004640be:
        fstp tbyte ptr [ebp-9Eh]
    L_004640c4:
        fld tbyte ptr [ebp-9Eh]
    L_004640ca:
        test byte ptr [ebp-97h],40h
    L_004640d1:
        je short L_004640dc
    L_004640d3:
        mov byte ptr [ebp-90h],7
    L_004640da:
        jmp short L_004640e3
    L_004640dc:
        mov byte ptr [ebp-90h],1
    L_004640e3:
        faddp st(1),st
    L_004640e5:
        ret
    L_004640e6:
        fstp st(0)
    L_004640e8:
        fstp st(0)
    L_004640ea:
        fld tbyte ptr [data_00477070]
    L_004640f0:
        cmp byte ptr [ebp-90h],0
    L_004640f7:
        jg short L_00464100
    L_004640f9:
        mov byte ptr [ebp-90h],1
    L_00464100:
        or cl,cl
    L_00464102:
        ret
    L_00464103:
        or cl,cl
    L_00464105:
        je short L_00464109
    L_00464107:
        fchs
    L_00464109:
        ret
    }
}
