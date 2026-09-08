#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00439660..0x004396F7: FUN_00439660
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00439660_00439660() {
    __asm {
    L_00439660:
        mov eax,dword ptr [data_00492508]
    L_00439665:
        mov ecx,dword ptr [data_0049250c]
    L_0043966b:
        sub esp,8
    L_0043966e:
        or eax,ecx
    L_00439670:
        je short L_004396a6
    L_00439672:
        lea ecx,[esp]
    L_00439675:
        push ecx
    L_00439676:
        call dword ptr [data_004660fc]
    L_0043967c:
        mov edx,dword ptr [esp]
    L_0043967f:
        mov eax,dword ptr [data_00492510]
    L_00439684:
        mov ecx,dword ptr [data_00492514]
    L_0043968a:
        sub edx,eax
    L_0043968c:
        mov eax,dword ptr [esp+4]
    L_00439690:
        sbb eax,ecx
    L_00439692:
        mov dword ptr [esp],edx
    L_00439695:
        mov dword ptr [esp+4],eax
    L_00439699:
        fild qword ptr [esp]
    L_0043969c:
        fild qword ptr [data_00492508]
    L_004396a2:
        fdivp st(1),st
    L_004396a4:
        jmp short L_004396d9
    L_004396a6:
        push 1
    L_004396a8:
        call dword ptr [data_00466278]
    L_004396ae:
        call dword ptr [data_00466270]
    L_004396b4:
        test eax,eax
    L_004396b6:
        mov dword ptr [esp],eax
    L_004396b9:
        fild dword ptr [esp]
    L_004396bc:
        jge short L_004396c4
    L_004396be:
        fadd qword ptr [data_00470b30]
    L_004396c4:
        push 1
    L_004396c6:
        fstp qword ptr [esp+4]
    L_004396ca:
        call dword ptr [data_00466274]
    L_004396d0:
        fld qword ptr [esp]
    L_004396d3:
        fmul qword ptr [data_00470b28]
    L_004396d9:
        fld qword ptr [data_00492540]
    L_004396df:
        fcomp
    L_004396e1:
        fnstsw ax
    L_004396e3:
        test ah,41h
    L_004396e6:
        jne short L_004396ee
    L_004396e8:
        fst qword ptr [data_00492540]
    L_004396ee:
        fsub qword ptr [data_00492540]
    L_004396f4:
        add esp,8
    L_004396f7:
        ret
    }
}
