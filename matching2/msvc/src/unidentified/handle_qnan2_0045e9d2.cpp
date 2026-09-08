#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045E9D2..0x0045EA30: __handle_qnan2
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_handle_qnan2_0045e9d2() {
    __asm {
    L_0045e9d2:
        push ebp
    L_0045e9d3:
        mov ebp,esp
    L_0045e9d5:
        push ecx
    L_0045e9d6:
        push ecx
    L_0045e9d7:
        cmp dword ptr [data_00473c90],0
    L_0045e9de:
        fld qword ptr [ebp+0Ch]
    L_0045e9e1:
        fadd qword ptr [ebp+14h]
    L_0045e9e4:
        fstp qword ptr [ebp-8]
    L_0045e9e7:
        jne short L_0045ea12
    L_0045e9e9:
        push dword ptr [ebp+1Ch]
    L_0045e9ec:
        fld qword ptr [ebp-8]
    L_0045e9ef:
        sub esp,18h
    L_0045e9f2:
        fstp qword ptr [esp+10h]
    L_0045e9f6:
        fld qword ptr [ebp+14h]
    L_0045e9f9:
        fstp qword ptr [esp+8]
    L_0045e9fd:
        fld qword ptr [ebp+0Ch]
    L_0045ea00:
        fstp qword ptr [esp]
    L_0045ea03:
        push dword ptr [ebp+8]
    L_0045ea06:
        push 1
    L_0045ea08:
        call asm_umatherr_0045e8e1
    L_0045ea0d:
        add esp,24h
    L_0045ea10:
        leave
    L_0045ea11:
        ret
    L_0045ea12:
        call asm_FUN_00456af2_00456af2
    L_0045ea17:
        push 0FFFFh
    L_0045ea1c:
        push dword ptr [ebp+1Ch]
    L_0045ea1f:
        mov dword ptr [eax],21h
    L_0045ea25:
        call asm_ctrlfp_0045ed87
    L_0045ea2a:
        fld qword ptr [ebp-8]
    L_0045ea2d:
        pop ecx
    L_0045ea2e:
        pop ecx
    L_0045ea2f:
        leave
    L_0045ea30:
        ret
    }
}
