#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045EAED..0x0045EBB9: FUN_0045eaed
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045eaed_0045eaed() {
    __asm {
    L_0045eaed:
        push ebp
    L_0045eaee:
        mov ebp,esp
    L_0045eaf0:
        and esp,0FFFFFFF0h
    L_0045eaf3:
        sub esp,80h
    L_0045eaf9:
        mov eax,dword ptr [data_00473660]
    L_0045eafe:
        push dword ptr [ebp+28h]
    L_0045eb01:
        xor eax,ebp
    L_0045eb03:
        mov dword ptr [esp+80h],eax
    L_0045eb0a:
        lea eax,[ebp+20h]
    L_0045eb0d:
        push eax
    L_0045eb0e:
        push dword ptr [ebp+8]
    L_0045eb11:
        call asm_handle_exc_0045e648
    L_0045eb16:
        add esp,0Ch
    L_0045eb19:
        test eax,eax
    L_0045eb1b:
        jne short L_0045eb51
    L_0045eb1d:
        mov eax,dword ptr [esp+40h]
    L_0045eb21:
        fld qword ptr [ebp+18h]
    L_0045eb24:
        and eax,0FFFFFFE3h
    L_0045eb27:
        fstp qword ptr [esp+30h]
    L_0045eb2b:
        or eax,3
    L_0045eb2e:
        mov dword ptr [esp+40h],eax
    L_0045eb32:
        lea eax,[ebp+20h]
    L_0045eb35:
        push eax
    L_0045eb36:
        lea eax,[ebp+10h]
    L_0045eb39:
        push eax
    L_0045eb3a:
        push dword ptr [ebp+0Ch]
    L_0045eb3d:
        lea eax,[ebp+28h]
    L_0045eb40:
        push dword ptr [ebp+8]
    L_0045eb43:
        push eax
    L_0045eb44:
        lea eax,[esp+14h]
    L_0045eb48:
        push eax
    L_0045eb49:
        call asm_raise_exc_0045e3a3
    L_0045eb4e:
        add esp,18h
    L_0045eb51:
        push dword ptr [ebp+8]
    L_0045eb54:
        call asm_errcode_0045e8b4
    L_0045eb59:
        add esp,4
    L_0045eb5c:
        cmp dword ptr [data_00473c90],0
    L_0045eb63:
        jne short L_0045eb91
    L_0045eb65:
        test eax,eax
    L_0045eb67:
        je short L_0045eb91
    L_0045eb69:
        push dword ptr [ebp+28h]
    L_0045eb6c:
        fld qword ptr [ebp+20h]
    L_0045eb6f:
        sub esp,18h
    L_0045eb72:
        fstp qword ptr [esp+10h]
    L_0045eb76:
        fld qword ptr [ebp+18h]
    L_0045eb79:
        fstp qword ptr [esp+8]
    L_0045eb7d:
        fld qword ptr [ebp+10h]
    L_0045eb80:
        fstp qword ptr [esp]
    L_0045eb83:
        push dword ptr [ebp+0Ch]
    L_0045eb86:
        push eax
    L_0045eb87:
        call asm_umatherr_0045e8e1
    L_0045eb8c:
        add esp,24h
    L_0045eb8f:
        jmp short L_0045ebab
    L_0045eb91:
        push eax
    L_0045eb92:
        call asm_FID_conflict___set_errno_from_matherr_0045e86c
    L_0045eb97:
        mov dword ptr [esp],0FFFFh
    L_0045eb9e:
        push dword ptr [ebp+28h]
    L_0045eba1:
        call asm_ctrlfp_0045ed87
    L_0045eba6:
        fld qword ptr [ebp+20h]
    L_0045eba9:
        pop ecx
    L_0045ebaa:
        pop ecx
    L_0045ebab:
        mov ecx,dword ptr [esp+7Ch]
    L_0045ebaf:
        xor ecx,ebp
    L_0045ebb1:
        call asm_security_check_cookie_00458ea5
    L_0045ebb6:
        mov esp,ebp
    L_0045ebb8:
        pop ebp
    L_0045ebb9:
        ret
    }
}
