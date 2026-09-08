#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045EA31..0x0045EAEC: FUN_0045ea31
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045ea31_0045ea31() {
    __asm {
    L_0045ea31:
        push ebp
    L_0045ea32:
        mov ebp,esp
    L_0045ea34:
        and esp,0FFFFFFF0h
    L_0045ea37:
        sub esp,80h
    L_0045ea3d:
        mov eax,dword ptr [data_00473660]
    L_0045ea42:
        push dword ptr [ebp+20h]
    L_0045ea45:
        xor eax,ebp
    L_0045ea47:
        mov dword ptr [esp+80h],eax
    L_0045ea4e:
        lea eax,[ebp+18h]
    L_0045ea51:
        push eax
    L_0045ea52:
        push dword ptr [ebp+8]
    L_0045ea55:
        call asm_handle_exc_0045e648
    L_0045ea5a:
        add esp,0Ch
    L_0045ea5d:
        test eax,eax
    L_0045ea5f:
        jne short L_0045ea85
    L_0045ea61:
        and dword ptr [esp+40h],0FFFFFFFEh
    L_0045ea66:
        lea eax,[ebp+18h]
    L_0045ea69:
        push eax
    L_0045ea6a:
        lea eax,[ebp+10h]
    L_0045ea6d:
        push eax
    L_0045ea6e:
        push dword ptr [ebp+0Ch]
    L_0045ea71:
        lea eax,[ebp+20h]
    L_0045ea74:
        push dword ptr [ebp+8]
    L_0045ea77:
        push eax
    L_0045ea78:
        lea eax,[esp+14h]
    L_0045ea7c:
        push eax
    L_0045ea7d:
        call asm_raise_exc_0045e3a3
    L_0045ea82:
        add esp,18h
    L_0045ea85:
        push dword ptr [ebp+8]
    L_0045ea88:
        call asm_errcode_0045e8b4
    L_0045ea8d:
        add esp,4
    L_0045ea90:
        cmp dword ptr [data_00473c90],0
    L_0045ea97:
        jne short L_0045eac4
    L_0045ea99:
        test eax,eax
    L_0045ea9b:
        je short L_0045eac4
    L_0045ea9d:
        push dword ptr [ebp+20h]
    L_0045eaa0:
        fld qword ptr [ebp+18h]
    L_0045eaa3:
        sub esp,18h
    L_0045eaa6:
        fstp qword ptr [esp+10h]
    L_0045eaaa:
        fldz
    L_0045eaac:
        fstp qword ptr [esp+8]
    L_0045eab0:
        fld qword ptr [ebp+10h]
    L_0045eab3:
        fstp qword ptr [esp]
    L_0045eab6:
        push dword ptr [ebp+0Ch]
    L_0045eab9:
        push eax
    L_0045eaba:
        call asm_umatherr_0045e8e1
    L_0045eabf:
        add esp,24h
    L_0045eac2:
        jmp short L_0045eade
    L_0045eac4:
        push eax
    L_0045eac5:
        call asm_FID_conflict___set_errno_from_matherr_0045e86c
    L_0045eaca:
        mov dword ptr [esp],0FFFFh
    L_0045ead1:
        push dword ptr [ebp+20h]
    L_0045ead4:
        call asm_ctrlfp_0045ed87
    L_0045ead9:
        fld qword ptr [ebp+18h]
    L_0045eadc:
        pop ecx
    L_0045eadd:
        pop ecx
    L_0045eade:
        mov ecx,dword ptr [esp+7Ch]
    L_0045eae2:
        xor ecx,ebp
    L_0045eae4:
        call asm_security_check_cookie_00458ea5
    L_0045eae9:
        mov esp,ebp
    L_0045eaeb:
        pop ebp
    L_0045eaec:
        ret
    }
}
