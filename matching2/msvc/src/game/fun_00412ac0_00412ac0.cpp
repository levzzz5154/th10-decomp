#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00404610..0x00404986: FUN_00404610
// Naked body preserves the retail register/stack ABI.

// 0x00412AC0..0x00412D4B: FUN_00412ac0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00412ac0_00412ac0() {
    __asm {
    L_00412ac0:
        sub esp,20h
    L_00412ac3:
        mov eax,dword ptr [esi+34h]
    L_00412ac6:
        test eax,eax
    L_00412ac8:
        mov dword ptr [esp],eax
    L_00412acb:
        jle asm_target_00412b90
    L_00412ad1:
        mov edx,dword ptr [esi+24h]
    L_00412ad4:
        mov ecx,dword ptr [esi+2Ch]
    L_00412ad7:
        mov dword ptr [esi+20h],edx
    L_00412ada:
        fld dword ptr [ecx]
    L_00412adc:
        fcomp dword ptr [data_00470b68]
    L_00412ae2:
        fnstsw ax
    L_00412ae4:
        test ah,41h
    L_00412ae7:
        jne short L_00412b0a
    L_00412ae9:
        fld dword ptr [ecx]
    L_00412aeb:
        fcomp dword ptr [data_00470b64]
    L_00412af1:
        fnstsw ax
    L_00412af3:
        test ah,5
    L_00412af6:
        jp short L_00412b0a
    L_00412af8:
        fld dword ptr [esi+28h]
    L_00412afb:
        inc edx
    L_00412afc:
        fadd dword ptr [data_00470afc]
    L_00412b02:
        mov dword ptr [esi+24h],edx
    L_00412b05:
        fstp dword ptr [esi+28h]
    L_00412b08:
        jmp short L_00412b1a
    L_00412b0a:
        fld dword ptr [ecx]
    L_00412b0c:
        fadd dword ptr [esi+28h]
    L_00412b0f:
        fst dword ptr [esi+28h]
    L_00412b12:
        call asm_FUN_00463b2c_00463b2c
    L_00412b17:
        mov dword ptr [esi+24h],eax
    L_00412b1a:
        mov ecx,dword ptr [esi+34h]
    L_00412b1d:
        cmp dword ptr [esi+24h],ecx
    L_00412b20:
        mov dword ptr [esp],ecx
    L_00412b23:
        jl short L_00412b90
    L_00412b25:
        mov eax,dword ptr [esi+30h]
    L_00412b28:
        test al,1
    L_00412b2a:
        mov dword ptr [esp+8],ecx
    L_00412b2e:
        jne short L_00412b52
    L_00412b30:
        or eax,1
    L_00412b33:
        mov dword ptr [esi+24h],0
    L_00412b3a:
        mov dword ptr [esi+20h],0FFF0BDC1h
    L_00412b41:
        mov dword ptr [esi+28h],0
    L_00412b48:
        mov dword ptr [esi+2Ch],476F78h
    L_00412b4f:
        mov dword ptr [esi+30h],eax
    L_00412b52:
        fild dword ptr [esp+8]
    L_00412b56:
        mov dword ptr [esi+24h],ecx
    L_00412b59:
        dec ecx
    L_00412b5a:
        mov dword ptr [esi+20h],ecx
    L_00412b5d:
        fstp dword ptr [esi+28h]
    L_00412b60:
        mov eax,dword ptr [esi+38h]
    L_00412b63:
        cmp eax,7
    L_00412b66:
        mov dword ptr [esi+34h],0
    L_00412b6d:
        je short L_00412b80
    L_00412b6f:
        mov eax,dword ptr [esi+8]
    L_00412b72:
        mov dword ptr [edi],eax
    L_00412b74:
        mov ecx,dword ptr [esi+0Ch]
    L_00412b77:
        mov dword ptr [edi+4],ecx
    L_00412b7a:
        mov eax,edi
    L_00412b7c:
        add esp,20h
    L_00412b7f:
        ret
    L_00412b80:
        mov edx,dword ptr [esi]
    L_00412b82:
        mov dword ptr [edi],edx
    L_00412b84:
        mov eax,dword ptr [esi+4]
    L_00412b87:
        mov dword ptr [edi+4],eax
    L_00412b8a:
        mov eax,edi
    L_00412b8c:
        add esp,20h
    L_00412b8f:
        ret
    L_00412b90:
        mov eax,dword ptr [esi+38h]
    L_00412b93:
        cmp eax,7
    L_00412b96:
        jne short L_00412bd1
    L_00412b98:
        mov ecx,dword ptr [esi]
    L_00412b9a:
        mov edx,dword ptr [esi+4]
    L_00412b9d:
        mov dword ptr [esp+8],ecx
    L_00412ba1:
        fld dword ptr [esp+8]
    L_00412ba5:
        fadd dword ptr [esi+8]
    L_00412ba8:
        mov dword ptr [esp+0Ch],edx
    L_00412bac:
        fstp dword ptr [esp]
    L_00412baf:
        mov eax,dword ptr [esp]
    L_00412bb2:
        fld dword ptr [esp+0Ch]
    L_00412bb6:
        fadd dword ptr [esi+0Ch]
    L_00412bb9:
        mov dword ptr [esi],eax
    L_00412bbb:
        fstp dword ptr [esp+4]
    L_00412bbf:
        mov ecx,dword ptr [esp+4]
    L_00412bc3:
        mov dword ptr [esi+4],ecx
    L_00412bc6:
        mov dword ptr [edi],eax
    L_00412bc8:
        mov dword ptr [edi+4],ecx
    L_00412bcb:
        mov eax,edi
    L_00412bcd:
        add esp,20h
    L_00412bd0:
        ret
    L_00412bd1:
        cmp eax,11h
    L_00412bd4:
        jne short L_00412c31
    L_00412bd6:
        mov eax,dword ptr [esi]
    L_00412bd8:
        mov ecx,dword ptr [esi+4]
    L_00412bdb:
        mov dword ptr [esp+8],eax
    L_00412bdf:
        fld dword ptr [esp+8]
    L_00412be3:
        fadd dword ptr [esi+18h]
    L_00412be6:
        mov dword ptr [esp+0Ch],ecx
    L_00412bea:
        fstp dword ptr [esp]
    L_00412bed:
        mov eax,dword ptr [esp]
    L_00412bf0:
        fld dword ptr [esp+0Ch]
    L_00412bf4:
        fadd dword ptr [esi+1Ch]
    L_00412bf7:
        mov dword ptr [esi],eax
    L_00412bf9:
        fstp dword ptr [esp+4]
    L_00412bfd:
        mov ecx,dword ptr [esp+4]
    L_00412c01:
        mov dword ptr [esi+4],ecx
    L_00412c04:
        fld dword ptr [esi+18h]
    L_00412c07:
        fadd dword ptr [esi+8]
    L_00412c0a:
        fstp dword ptr [esp+8]
    L_00412c0e:
        mov edx,dword ptr [esp+8]
    L_00412c12:
        fld dword ptr [esi+0Ch]
    L_00412c15:
        fadd dword ptr [esi+1Ch]
    L_00412c18:
        mov dword ptr [esi+18h],edx
    L_00412c1b:
        fstp dword ptr [esp+0Ch]
    L_00412c1f:
        mov edx,dword ptr [esp+0Ch]
    L_00412c23:
        mov dword ptr [esi+1Ch],edx
    L_00412c26:
        mov dword ptr [edi],eax
    L_00412c28:
        mov dword ptr [edi+4],ecx
    L_00412c2b:
        mov eax,edi
    L_00412c2d:
        add esp,20h
    L_00412c30:
        ret
    L_00412c31:
        cmp eax,8
    L_00412c34:
        fild dword ptr [esp]
    L_00412c37:
        jne asm_target_00412cfe
    L_00412c3d:
        fdivr dword ptr [esi+28h]
    L_00412c40:
        fld st(0)
    L_00412c42:
        fadd st,st(1)
    L_00412c44:
        fld st(1)
    L_00412c46:
        fsub dword ptr [data_00470afc]
    L_00412c4c:
        fstp dword ptr [esp]
    L_00412c4f:
        fld dword ptr [data_00470afc]
    L_00412c55:
        fadd st,st(1)
    L_00412c57:
        fmul dword ptr [esp]
    L_00412c5a:
        fmul dword ptr [esp]
    L_00412c5d:
        fstp dword ptr [esp+8]
    L_00412c61:
        fsubr dword ptr [data_00470bd4]
    L_00412c67:
        fmul st,st(1)
    L_00412c69:
        fmul st,st(1)
    L_00412c6b:
        fld dword ptr [data_00470afc]
    L_00412c71:
        fsub st,st(2)
    L_00412c73:
        fld st(0)
    L_00412c75:
        fmulp st(1),st
    L_00412c77:
        fmul st,st(2)
    L_00412c79:
        fld dword ptr [esp]
    L_00412c7c:
        fmul st,st(3)
    L_00412c7e:
        fmul st,st(3)
    L_00412c80:
        fld st(0)
    L_00412c82:
        fmul dword ptr [esi+18h]
    L_00412c85:
        fstp dword ptr [esp+10h]
    L_00412c89:
        fmul dword ptr [esi+1Ch]
    L_00412c8c:
        fstp dword ptr [esp+14h]
    L_00412c90:
        fld st(0)
    L_00412c92:
        fmul dword ptr [esi+10h]
    L_00412c95:
        fstp dword ptr [esp]
    L_00412c98:
        fmul dword ptr [esi+14h]
    L_00412c9b:
        fstp dword ptr [esp+4]
    L_00412c9f:
        fld st(0)
    L_00412ca1:
        fmul dword ptr [esi+8]
    L_00412ca4:
        fstp dword ptr [esp+18h]
    L_00412ca8:
        fmul dword ptr [esi+0Ch]
    L_00412cab:
        fstp st(1)
    L_00412cad:
        fld dword ptr [esp+8]
    L_00412cb1:
        fmul dword ptr [esi]
    L_00412cb3:
        fld dword ptr [esp+8]
    L_00412cb7:
        fmul dword ptr [esi+4]
    L_00412cba:
        fstp dword ptr [esp+0Ch]
    L_00412cbe:
        fadd dword ptr [esp+18h]
    L_00412cc2:
        fld dword ptr [esp+0Ch]
    L_00412cc6:
        fadd st,st(2)
    L_00412cc8:
        fstp dword ptr [esp+1Ch]
    L_00412ccc:
        fadd dword ptr [esp]
    L_00412ccf:
        fstp st(1)
    L_00412cd1:
        fld dword ptr [esp+1Ch]
    L_00412cd5:
        fadd dword ptr [esp+4]
    L_00412cd9:
        fxch
    L_00412cdb:
        fadd dword ptr [esp+10h]
    L_00412cdf:
        fstp dword ptr [esp+8]
    L_00412ce3:
        mov eax,dword ptr [esp+8]
    L_00412ce7:
        mov dword ptr [edi],eax
    L_00412ce9:
        fadd dword ptr [esp+14h]
    L_00412ced:
        mov eax,edi
    L_00412cef:
        fstp dword ptr [esp+0Ch]
    L_00412cf3:
        mov ecx,dword ptr [esp+0Ch]
    L_00412cf7:
        mov dword ptr [edi+4],ecx
    L_00412cfa:
        add esp,20h
    L_00412cfd:
        ret
    L_00412cfe:
        mov edx,dword ptr [esi+28h]
    L_00412d01:
        push ecx
    L_00412d02:
        fstp dword ptr [esp]
    L_00412d05:
        push edx
    L_00412d06:
        call asm_FUN_0044c350_0044c350
    L_00412d0b:
        fld dword ptr [esi+8]
    L_00412d0e:
        fsub dword ptr [esi]
    L_00412d10:
        fld dword ptr [esi+0Ch]
    L_00412d13:
        fsub dword ptr [esi+4]
    L_00412d16:
        fstp dword ptr [esp+1Ch]
    L_00412d1a:
        fmul st,st(1)
    L_00412d1c:
        fld dword ptr [esp+1Ch]
    L_00412d20:
        fmul st,st(2)
    L_00412d22:
        fstp dword ptr [esp+1Ch]
    L_00412d26:
        fadd dword ptr [esi]
    L_00412d28:
        fstp dword ptr [esp+10h]
    L_00412d2c:
        mov eax,dword ptr [esp+10h]
    L_00412d30:
        fstp st(0)
    L_00412d32:
        fld dword ptr [esp+1Ch]
    L_00412d36:
        fadd dword ptr [esi+4]
    L_00412d39:
        mov dword ptr [edi],eax
    L_00412d3b:
        mov eax,edi
    L_00412d3d:
        fstp dword ptr [esp+14h]
    L_00412d41:
        mov ecx,dword ptr [esp+14h]
    L_00412d45:
        mov dword ptr [edi+4],ecx
    L_00412d48:
        add esp,20h
    L_00412d4b:
        ret
    }
}
