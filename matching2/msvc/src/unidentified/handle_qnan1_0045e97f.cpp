#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045E97F..0x0045E9D1: __handle_qnan1
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_handle_qnan1_0045e97f() {
    __asm {
    L_0045e97f:
        push ebp
    L_0045e980:
        mov ebp,esp
    L_0045e982:
        cmp dword ptr [data_00473c90],0
    L_0045e989:
        jne short L_0045e9b3
    L_0045e98b:
        push dword ptr [ebp+14h]
    L_0045e98e:
        fld qword ptr [ebp+0Ch]
    L_0045e991:
        sub esp,18h
    L_0045e994:
        fstp qword ptr [esp+10h]
    L_0045e998:
        fldz
    L_0045e99a:
        fstp qword ptr [esp+8]
    L_0045e99e:
        fld qword ptr [ebp+0Ch]
    L_0045e9a1:
        fstp qword ptr [esp]
    L_0045e9a4:
        push dword ptr [ebp+8]
    L_0045e9a7:
        push 1
    L_0045e9a9:
        call asm_umatherr_0045e8e1
    L_0045e9ae:
        add esp,24h
    L_0045e9b1:
        pop ebp
    L_0045e9b2:
        ret
    L_0045e9b3:
        call asm_FUN_00456af2_00456af2
    L_0045e9b8:
        push 0FFFFh
    L_0045e9bd:
        push dword ptr [ebp+14h]
    L_0045e9c0:
        mov dword ptr [eax],21h
    L_0045e9c6:
        call asm_ctrlfp_0045ed87
    L_0045e9cb:
        fld qword ptr [ebp+0Ch]
    L_0045e9ce:
        pop ecx
    L_0045e9cf:
        pop ecx
    L_0045e9d0:
        pop ebp
    L_0045e9d1:
        ret
    }
}
