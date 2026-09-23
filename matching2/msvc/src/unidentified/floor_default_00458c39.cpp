#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00458C39..0x00458D0B: __floor_default
// CRT fallback: one stack double, x87 ST(0) result, caller cleanup.
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) double __cdecl asm_floor_default_00458c39(double value) {
    __asm {
    L_00458c39:
        push ebp
    L_00458c3a:
        mov ebp,esp
    L_00458c3c:
        push ecx
    L_00458c3d:
        push ecx
    L_00458c3e:
        push ebx
    L_00458c3f:
        push esi
    L_00458c40:
        mov esi,0FFFFh
    L_00458c45:
        push esi
    L_00458c46:
        push dword ptr [data_0047365c]
    L_00458c4c:
        call asm_ctrlfp_0045ed87
    L_00458c51:
        fld qword ptr [ebp+8]
    L_00458c54:
        pop ecx
    L_00458c55:
        pop ecx
    L_00458c56:
        mov ebx,eax
    L_00458c58:
        mov eax,dword ptr [ebp+0Eh]
    L_00458c5b:
        push ecx
    L_00458c5c:
        and ax,7FF0h
    L_00458c60:
        cmp ax,7FF0h
    L_00458c64:
        push ecx
    L_00458c65:
        fstp qword ptr [esp]
    L_00458c68:
        jne short L_00458cbf
    L_00458c6a:
        call asm_sptype_0045ec59
    L_00458c6f:
        test eax,eax
    L_00458c71:
        pop ecx
    L_00458c72:
        pop ecx
    L_00458c73:
        jle short L_00458ca2
    L_00458c75:
        cmp eax,2
    L_00458c78:
        jle short L_00458c94
    L_00458c7a:
        cmp eax,3
    L_00458c7d:
        jne short L_00458ca2
    L_00458c7f:
        fld qword ptr [ebp+8]
    L_00458c82:
        push ebx
    L_00458c83:
        push ecx
    L_00458c84:
        push ecx
    L_00458c85:
        fstp qword ptr [esp]
    L_00458c88:
        push 0Bh
    L_00458c8a:
        call asm_handle_qnan1_0045e97f
    L_00458c8f:
        add esp,10h
    L_00458c92:
        jmp short L_00458d08
    L_00458c94:
        push esi
    L_00458c95:
        push ebx
    L_00458c96:
        call asm_ctrlfp_0045ed87
    L_00458c9b:
        fld qword ptr [ebp+8]
    L_00458c9e:
        pop ecx
    L_00458c9f:
        pop ecx
    L_00458ca0:
        jmp short L_00458d08
    L_00458ca2:
        fld qword ptr [ebp+8]
    L_00458ca5:
        push ebx
    L_00458ca6:
        fadd qword ptr [data_0046ac28]
    L_00458cac:
        sub esp,10h
    L_00458caf:
        fstp qword ptr [esp+8]
    L_00458cb3:
        fld qword ptr [ebp+8]
    L_00458cb6:
        fstp qword ptr [esp]
    L_00458cb9:
        push 0Bh
    L_00458cbb:
        push 8
    L_00458cbd:
        jmp short L_00458d00
    L_00458cbf:
        call asm_frnd_0045ebba
    L_00458cc4:
        fstp qword ptr [ebp-8]
    L_00458cc7:
        fld qword ptr [ebp+8]
    L_00458cca:
        pop ecx
    L_00458ccb:
        fld qword ptr [ebp-8]
    L_00458cce:
        pop ecx
    L_00458ccf:
        fucompp
    L_00458cd1:
        fnstsw ax
    L_00458cd3:
        test ah,44h
    L_00458cd6:
        jp short L_00458ce6
    L_00458cd8:
        push esi
    L_00458cd9:
        push ebx
    L_00458cda:
        call asm_ctrlfp_0045ed87
    L_00458cdf:
        fld qword ptr [ebp-8]
    L_00458ce2:
        pop ecx
    L_00458ce3:
        pop ecx
    L_00458ce4:
        jmp short L_00458d08
    L_00458ce6:
        test bl,20h
    L_00458ce9:
        jne short L_00458cd8
    L_00458ceb:
        fld qword ptr [ebp-8]
    L_00458cee:
        push ebx
    L_00458cef:
        sub esp,10h
    L_00458cf2:
        fstp qword ptr [esp+8]
    L_00458cf6:
        fld qword ptr [ebp+8]
    L_00458cf9:
        fstp qword ptr [esp]
    L_00458cfc:
        push 0Bh
    L_00458cfe:
        push 10h
    L_00458d00:
        call asm_FUN_0045ea31_0045ea31
    L_00458d05:
        add esp,1Ch
    L_00458d08:
        pop esi
    L_00458d09:
        pop ebx
    L_00458d0a:
        leave
    L_00458d0b:
        ret
    }
}
