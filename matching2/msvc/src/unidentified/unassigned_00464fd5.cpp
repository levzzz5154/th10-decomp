#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00464FD5..0x0046508B: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00464fd5() {
    __asm {
    L_00464fd5:
        sub esp,8
    L_00464fd8:
        fst qword ptr [esp]
    L_00464fdb:
        mov eax,dword ptr [esp+4]
    L_00464fdf:
        add esp,8
    L_00464fe2:
        and eax,7FF00000h
    L_00464fe7:
        jmp short L_00464ffd
    L_00464fe9:
        sub esp,8
    L_00464fec:
        fst qword ptr [esp]
    L_00464fef:
        mov eax,dword ptr [esp+4]
    L_00464ff3:
        add esp,8
    L_00464ff6:
        and eax,7FF00000h
    L_00464ffb:
        je short L_0046503a
    L_00464ffd:
        cmp eax,7FF00000h
    L_00465002:
        je short L_00465063
    L_00465004:
        mov ax,word ptr [esp]
    L_00465008:
        cmp ax,27Fh
    L_0046500c:
        je short L_00465038
    L_0046500e:
        TH10_OPERAND16()
        and eax,20h
    L_00465012:
        jne short L_00465035
    L_00465014:
        wait
        fnstsw ax
    L_00465017:
        TH10_OPERAND16()
        and eax,20h
    L_0046501b:
        je short L_00465035
    L_0046501d:
        mov eax,8
    L_00465022:
        cmp edx,1Dh
    L_00465025:
        je short L_0046502e
    L_00465027:
        call asm_startOneArgErrorHandling_00464eb7
    L_0046502c:
        pop edx
    L_0046502d:
        ret
    L_0046502e:
        call asm_FUN_00464ea0_00464ea0
    L_00465033:
        pop edx
    L_00465034:
        ret
    L_00465035:
        fldcw word ptr [esp]
    L_00465038:
        pop edx
    L_00465039:
        ret
    L_0046503a:
        fld qword ptr [data_00470dbc]
    L_00465040:
        fxch
    L_00465042:
        fscale
    L_00465044:
        fstp st(1)
    L_00465046:
        fld st(0)
    L_00465048:
        fabs
    L_0046504a:
        fcomp qword ptr [data_00470dac]
    L_00465050:
        wait
        fnstsw ax
    L_00465053:
        sahf
    L_00465054:
        mov eax,4
    L_00465059:
        jae short L_00465022
    L_0046505b:
        fmul qword ptr [data_00470dcc]
    L_00465061:
        jmp short L_00465022
    L_00465063:
        fld qword ptr [data_00470db4]
    L_00465069:
        fxch
    L_0046506b:
        fscale
    L_0046506d:
        fstp st(1)
    L_0046506f:
        fld st(0)
    L_00465071:
        fabs
    L_00465073:
        fcomp qword ptr [data_00470da4]
    L_00465079:
        wait
        fnstsw ax
    L_0046507c:
        sahf
    L_0046507d:
        mov eax,3
    L_00465082:
        jbe short L_00465022
    L_00465084:
        fmul qword ptr [data_00470dc4]
    L_0046508a:
        jmp short L_00465022
    }
}
