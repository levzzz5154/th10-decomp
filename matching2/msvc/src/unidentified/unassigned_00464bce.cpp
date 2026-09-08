#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00464BCE..0x00464E9A: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00464bce() {
    __asm {
    L_00464bce:
        push eax
    L_00464bcf:
        push ebx
    L_00464bd0:
        push ecx
    L_00464bd1:
        mov eax,dword ptr [esp+16h]
    L_00464bd5:
        xor eax,700h
    L_00464bda:
        test eax,700h
    L_00464bdf:
        jne asm_target_00464d68
    L_00464be5:
        shr eax,0Bh
    L_00464be8:
        and eax,0Fh
    L_00464beb:
        cmp byte ptr [eax+4770BCh],0
    L_00464bf2:
        je asm_target_00464d68
    L_00464bf8:
        mov eax,dword ptr [esp+16h]
    L_00464bfc:
        and eax,7FFF0000h
    L_00464c01:
        cmp eax,7FFF0000h
    L_00464c06:
        je asm_target_00464d68
    L_00464c0c:
        mov eax,dword ptr [esp+2Eh]
    L_00464c10:
        and eax,7FFF0000h
    L_00464c15:
        je asm_target_00464d68
    L_00464c1b:
        cmp eax,7FFF0000h
    L_00464c20:
        je asm_target_00464d68
    L_00464c26:
        mov eax,dword ptr [esp+2Ch]
    L_00464c2a:
        add eax,eax
    L_00464c2c:
        jne asm_target_00464d68
    L_00464c32:
        mov eax,dword ptr [esp+14h]
    L_00464c36:
        add eax,eax
    L_00464c38:
        jne asm_target_00464d68
    L_00464c3e:
        mov eax,dword ptr [esp+18h]
    L_00464c42:
        and eax,7FFFh
    L_00464c47:
        add eax,3Fh
    L_00464c4a:
        mov ebx,dword ptr [esp+30h]
    L_00464c4e:
        and ebx,7FFFh
    L_00464c54:
        sub ebx,eax
    L_00464c56:
        ja short L_00464cb6
    L_00464c58:
        mov eax,dword ptr [esp+18h]
    L_00464c5c:
        and eax,7FFFh
    L_00464c61:
        add eax,0Ah
    L_00464c64:
        mov ebx,dword ptr [esp+30h]
    L_00464c68:
        and ebx,7FFFh
    L_00464c6e:
        sub ebx,eax
    L_00464c70:
        js asm_target_00464d68
    L_00464c76:
        fld tbyte ptr [esp+28h]
    L_00464c7a:
        mov eax,dword ptr [esp+18h]
    L_00464c7e:
        mov ebx,dword ptr [esp+30h]
    L_00464c82:
        and ebx,7FFFh
    L_00464c88:
        mov ecx,ebx
    L_00464c8a:
        sub ebx,eax
    L_00464c8c:
        and ebx,7
    L_00464c8f:
        or ebx,4
    L_00464c92:
        sub ecx,ebx
    L_00464c94:
        mov ebx,eax
    L_00464c96:
        and ebx,8000h
    L_00464c9c:
        or ecx,ebx
    L_00464c9e:
        mov dword ptr [esp+18h],ecx
    L_00464ca2:
        fld tbyte ptr [esp+10h]
    L_00464ca6:
        mov dword ptr [esp+18h],eax
    L_00464caa:
        fxch
    L_00464cac:
        fprem
    L_00464cae:
        fstp tbyte ptr [esp+28h]
    L_00464cb2:
        fstp st(0)
    L_00464cb4:
        jmp short L_00464c58
    L_00464cb6:
        test ebx,2
    L_00464cbc:
        jne short L_00464cc6
    L_00464cbe:
        fld tbyte ptr [esp+10h]
    L_00464cc2:
        fstp tbyte ptr [esp+1Ch]
    L_00464cc6:
        fnstcw word ptr [esp+34h]
    L_00464cca:
        mov eax,dword ptr [esp+34h]
    L_00464cce:
        or eax,33Fh
    L_00464cd3:
        mov dword ptr [esp+38h],eax
    L_00464cd7:
        fldcw word ptr [esp+38h]
    L_00464cdb:
        mov eax,dword ptr [esp+18h]
    L_00464cdf:
        and eax,7FFFh
    L_00464ce4:
        mov ebx,dword ptr [esp+30h]
    L_00464ce8:
        and ebx,7FFFh
    L_00464cee:
        sub ebx,eax
    L_00464cf0:
        and ebx,3Fh
    L_00464cf3:
        or ebx,20h
    L_00464cf6:
        add ebx,1
    L_00464cf9:
        mov ecx,ebx
    L_00464cfb:
        mov eax,dword ptr [esp+18h]
    L_00464cff:
        mov ebx,dword ptr [esp+30h]
    L_00464d03:
        and ebx,7FFFh
    L_00464d09:
        and eax,8000h
    L_00464d0e:
        or ebx,eax
    L_00464d10:
        mov dword ptr [esp+18h],ebx
    L_00464d14:
        fld tbyte ptr [esp+10h]
    L_00464d18:
        fabs
    L_00464d1a:
        fld tbyte ptr [esp+28h]
    L_00464d1e:
        fabs
    L_00464d20:
        fcom
    L_00464d22:
        fnstsw ax
    L_00464d24:
        and eax,100h
    L_00464d29:
        jne short L_00464d2d
    L_00464d2b:
        fsub st,st(1)
    L_00464d2d:
        fxch
    L_00464d2f:
        fmul qword ptr [data_004770ec]
    L_00464d35:
        fxch
    L_00464d37:
        sub ecx,1
    L_00464d3a:
        jne short L_00464d20
    L_00464d3c:
        mov ebx,dword ptr [esp+30h]
    L_00464d40:
        fstp tbyte ptr [esp+28h]
    L_00464d44:
        fstp st(0)
    L_00464d46:
        fld tbyte ptr [esp+1Ch]
    L_00464d4a:
        fld tbyte ptr [data_004770f4]
    L_00464d50:
        fprem1
    L_00464d52:
        fstp st(0)
    L_00464d54:
        fld tbyte ptr [esp+28h]
    L_00464d58:
        fldcw word ptr [esp+34h]
    L_00464d5c:
        and ebx,8000h
    L_00464d62:
        je short L_00464d72
    L_00464d64:
        fchs
    L_00464d66:
        jmp short L_00464d72
    L_00464d68:
        fld tbyte ptr [esp+10h]
    L_00464d6c:
        fld tbyte ptr [esp+28h]
    L_00464d70:
        fprem1
    L_00464d72:
        test edx,3
    L_00464d78:
        je short L_00464dd0
    L_00464d7a:
        fnstsw word ptr [esp+3Ch]
    L_00464d7e:
        test edx,1
    L_00464d84:
        je short L_00464da5
    L_00464d86:
        fnstcw word ptr [esp+34h]
    L_00464d8a:
        mov eax,dword ptr [esp+34h]
    L_00464d8e:
        or eax,300h
    L_00464d93:
        mov dword ptr [esp+38h],eax
    L_00464d97:
        fldcw word ptr [esp+38h]
    L_00464d9b:
        fmul qword ptr [data_004770dc]
    L_00464da1:
        fldcw word ptr [esp+34h]
    L_00464da5:
        mov eax,dword ptr [esp+3Ch]
    L_00464da9:
        fxch
    L_00464dab:
        fstp st(0)
    L_00464dad:
        fld tbyte ptr [esp+1Ch]
    L_00464db1:
        fxch
    L_00464db3:
        and eax,4300h
    L_00464db8:
        sub esp,1Ch
    L_00464dbb:
        fnstenv [esp]
    L_00464dbe:
        and dword ptr [esp+4],0BCFFh
    L_00464dc6:
        or dword ptr [esp+4],eax
    L_00464dca:
        fldenv [esp]
    L_00464dcd:
        add esp,1Ch
    L_00464dd0:
        pop ecx
    L_00464dd1:
        pop ebx
    L_00464dd2:
        pop eax
    L_00464dd3:
        ret
    L_00464dd4:
        push edx
    L_00464dd5:
        sub esp,30h
    L_00464dd8:
        fstp tbyte ptr [esp+18h]
    L_00464ddc:
        fstp tbyte ptr [esp]
    L_00464ddf:
        mov edx,0
    L_00464de4:
        mov eax,dword ptr [esp+6]
    L_00464de8:
        test eax,7FFF0000h
    L_00464ded:
        je short L_00464df9
    L_00464def:
        call asm_unassigned_00464bce
    L_00464df4:
        add esp,30h
    L_00464df7:
        pop edx
    L_00464df8:
        ret
    L_00464df9:
        fld tbyte ptr [esp]
    L_00464dfc:
        fld tbyte ptr [esp+18h]
    L_00464e00:
        mov eax,dword ptr [esp]
    L_00464e03:
        or eax,dword ptr [esp+4]
    L_00464e07:
        je short L_00464e82
    L_00464e09:
        fxch
    L_00464e0b:
        fstp tbyte ptr [esp+0Ch]
    L_00464e0f:
        fld tbyte ptr [esp]
    L_00464e12:
        fxch
    L_00464e14:
        or edx,2
    L_00464e17:
        fnstcw word ptr [esp+24h]
    L_00464e1b:
        mov eax,dword ptr [esp+24h]
    L_00464e1f:
        or eax,33Fh
    L_00464e24:
        mov dword ptr [esp+28h],eax
    L_00464e28:
        fldcw word ptr [esp+28h]
    L_00464e2c:
        mov eax,dword ptr [esp+20h]
    L_00464e30:
        and eax,7FFFh
    L_00464e35:
        cmp eax,7FBEh
    L_00464e3a:
        ja short L_00464e54
    L_00464e3c:
        or edx,1
    L_00464e3f:
        fmul qword ptr [data_004770d4]
    L_00464e45:
        fstp tbyte ptr [esp+18h]
    L_00464e49:
        fmul qword ptr [data_004770d4]
    L_00464e4f:
        fstp tbyte ptr [esp]
    L_00464e52:
        jmp short L_00464e74
    L_00464e54:
        fnstcw word ptr [esp+24h]
    L_00464e58:
        mov eax,dword ptr [esp+24h]
    L_00464e5c:
        or eax,300h
    L_00464e61:
        mov dword ptr [esp+28h],eax
    L_00464e65:
        fldcw word ptr [esp+28h]
    L_00464e69:
        fstp st(0)
    L_00464e6b:
        fmul qword ptr [data_004770d4]
    L_00464e71:
        fstp tbyte ptr [esp]
    L_00464e74:
        fldcw word ptr [esp+24h]
    L_00464e78:
        call asm_unassigned_00464bce
    L_00464e7d:
        add esp,30h
    L_00464e80:
        pop edx
    L_00464e81:
        ret
    L_00464e82:
        fprem
    L_00464e84:
        add esp,30h
    L_00464e87:
        pop edx
    L_00464e88:
        ret
    L_00464e89:
        call asm_FUN_00464b1c_00464b1c
    L_00464e8e:
        ret
    L_00464e8f:
        call asm_target_00464dd4
    L_00464e94:
        ret
    L_00464e95:
        fpatan
    L_00464e97:
        ret
    L_00464e98:
        fptan
    L_00464e9a:
        ret
    }
}
