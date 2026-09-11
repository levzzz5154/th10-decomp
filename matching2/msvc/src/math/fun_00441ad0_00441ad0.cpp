#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00441600..0x00441933: FUN_00441600
// Naked body preserves the retail register/stack ABI.

// 0x00441AD0..0x00441D5B: FUN_00441ad0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00441ad0_00441ad0() {
    __asm {
    L_00441ad0:
        sub esp,20h
    L_00441ad3:
        mov eax,dword ptr [esi+34h]
    L_00441ad6:
        test eax,eax
    L_00441ad8:
        mov dword ptr [esp],eax
    L_00441adb:
        jle asm_target_00441ba0
    L_00441ae1:
        mov edx,dword ptr [esi+24h]
    L_00441ae4:
        mov ecx,dword ptr [esi+2Ch]
    L_00441ae7:
        mov dword ptr [esi+20h],edx
    L_00441aea:
        fld dword ptr [ecx]
    L_00441aec:
        fcomp dword ptr [data_00470b68]
    L_00441af2:
        fnstsw ax
    L_00441af4:
        test ah,41h
    L_00441af7:
        jne short L_00441b1a
    L_00441af9:
        fld dword ptr [ecx]
    L_00441afb:
        fcomp dword ptr [data_00470b64]
    L_00441b01:
        fnstsw ax
    L_00441b03:
        test ah,5
    L_00441b06:
        jp short L_00441b1a
    L_00441b08:
        fld dword ptr [esi+28h]
    L_00441b0b:
        inc edx
    L_00441b0c:
        fadd dword ptr [data_00470afc]
    L_00441b12:
        mov dword ptr [esi+24h],edx
    L_00441b15:
        fstp dword ptr [esi+28h]
    L_00441b18:
        jmp short L_00441b2a
    L_00441b1a:
        fld dword ptr [ecx]
    L_00441b1c:
        fadd dword ptr [esi+28h]
    L_00441b1f:
        fst dword ptr [esi+28h]
    L_00441b22:
        call asm_FUN_00463b2c_00463b2c
    L_00441b27:
        mov dword ptr [esi+24h],eax
    L_00441b2a:
        mov ecx,dword ptr [esi+34h]
    L_00441b2d:
        cmp dword ptr [esi+24h],ecx
    L_00441b30:
        mov dword ptr [esp],ecx
    L_00441b33:
        jl short L_00441ba0
    L_00441b35:
        mov eax,dword ptr [esi+30h]
    L_00441b38:
        test al,1
    L_00441b3a:
        mov dword ptr [esp+8],ecx
    L_00441b3e:
        jne short L_00441b62
    L_00441b40:
        or eax,1
    L_00441b43:
        mov dword ptr [esi+24h],0
    L_00441b4a:
        mov dword ptr [esi+20h],0FFF0BDC1h
    L_00441b51:
        mov dword ptr [esi+28h],0
    L_00441b58:
        mov dword ptr [esi+2Ch],476F78h
    L_00441b5f:
        mov dword ptr [esi+30h],eax
    L_00441b62:
        fild dword ptr [esp+8]
    L_00441b66:
        mov dword ptr [esi+24h],ecx
    L_00441b69:
        dec ecx
    L_00441b6a:
        mov dword ptr [esi+20h],ecx
    L_00441b6d:
        fstp dword ptr [esi+28h]
    L_00441b70:
        mov eax,dword ptr [esi+38h]
    L_00441b73:
        cmp eax,7
    L_00441b76:
        mov dword ptr [esi+34h],0
    L_00441b7d:
        je short L_00441b90
    L_00441b7f:
        mov eax,dword ptr [esi+8]
    L_00441b82:
        mov dword ptr [edi],eax
    L_00441b84:
        mov ecx,dword ptr [esi+0Ch]
    L_00441b87:
        mov dword ptr [edi+4],ecx
    L_00441b8a:
        mov eax,edi
    L_00441b8c:
        add esp,20h
    L_00441b8f:
        ret
    L_00441b90:
        mov edx,dword ptr [esi]
    L_00441b92:
        mov dword ptr [edi],edx
    L_00441b94:
        mov eax,dword ptr [esi+4]
    L_00441b97:
        mov dword ptr [edi+4],eax
    L_00441b9a:
        mov eax,edi
    L_00441b9c:
        add esp,20h
    L_00441b9f:
        ret
    L_00441ba0:
        mov eax,dword ptr [esi+38h]
    L_00441ba3:
        cmp eax,7
    L_00441ba6:
        jne short L_00441be1
    L_00441ba8:
        mov ecx,dword ptr [esi]
    L_00441baa:
        mov edx,dword ptr [esi+4]
    L_00441bad:
        mov dword ptr [esp+8],ecx
    L_00441bb1:
        fld dword ptr [esp+8]
    L_00441bb5:
        fadd dword ptr [esi+8]
    L_00441bb8:
        mov dword ptr [esp+0Ch],edx
    L_00441bbc:
        fstp dword ptr [esp]
    L_00441bbf:
        mov eax,dword ptr [esp]
    L_00441bc2:
        fld dword ptr [esp+0Ch]
    L_00441bc6:
        fadd dword ptr [esi+0Ch]
    L_00441bc9:
        mov dword ptr [esi],eax
    L_00441bcb:
        fstp dword ptr [esp+4]
    L_00441bcf:
        mov ecx,dword ptr [esp+4]
    L_00441bd3:
        mov dword ptr [esi+4],ecx
    L_00441bd6:
        mov dword ptr [edi],eax
    L_00441bd8:
        mov dword ptr [edi+4],ecx
    L_00441bdb:
        mov eax,edi
    L_00441bdd:
        add esp,20h
    L_00441be0:
        ret
    L_00441be1:
        cmp eax,11h
    L_00441be4:
        jne short L_00441c41
    L_00441be6:
        mov eax,dword ptr [esi]
    L_00441be8:
        mov ecx,dword ptr [esi+4]
    L_00441beb:
        mov dword ptr [esp+8],eax
    L_00441bef:
        fld dword ptr [esp+8]
    L_00441bf3:
        fadd dword ptr [esi+18h]
    L_00441bf6:
        mov dword ptr [esp+0Ch],ecx
    L_00441bfa:
        fstp dword ptr [esp]
    L_00441bfd:
        mov eax,dword ptr [esp]
    L_00441c00:
        fld dword ptr [esp+0Ch]
    L_00441c04:
        fadd dword ptr [esi+1Ch]
    L_00441c07:
        mov dword ptr [esi],eax
    L_00441c09:
        fstp dword ptr [esp+4]
    L_00441c0d:
        mov ecx,dword ptr [esp+4]
    L_00441c11:
        mov dword ptr [esi+4],ecx
    L_00441c14:
        fld dword ptr [esi+18h]
    L_00441c17:
        fadd dword ptr [esi+8]
    L_00441c1a:
        fstp dword ptr [esp+8]
    L_00441c1e:
        mov edx,dword ptr [esp+8]
    L_00441c22:
        fld dword ptr [esi+0Ch]
    L_00441c25:
        fadd dword ptr [esi+1Ch]
    L_00441c28:
        mov dword ptr [esi+18h],edx
    L_00441c2b:
        fstp dword ptr [esp+0Ch]
    L_00441c2f:
        mov edx,dword ptr [esp+0Ch]
    L_00441c33:
        mov dword ptr [esi+1Ch],edx
    L_00441c36:
        mov dword ptr [edi],eax
    L_00441c38:
        mov dword ptr [edi+4],ecx
    L_00441c3b:
        mov eax,edi
    L_00441c3d:
        add esp,20h
    L_00441c40:
        ret
    L_00441c41:
        cmp eax,8
    L_00441c44:
        fild dword ptr [esp]
    L_00441c47:
        jne asm_target_00441d0e
    L_00441c4d:
        fdivr dword ptr [esi+28h]
    L_00441c50:
        fld st(0)
    L_00441c52:
        fadd st,st(1)
    L_00441c54:
        fld st(1)
    L_00441c56:
        fsub dword ptr [data_00470afc]
    L_00441c5c:
        fstp dword ptr [esp]
    L_00441c5f:
        fld dword ptr [data_00470afc]
    L_00441c65:
        fadd st,st(1)
    L_00441c67:
        fmul dword ptr [esp]
    L_00441c6a:
        fmul dword ptr [esp]
    L_00441c6d:
        fstp dword ptr [esp+8]
    L_00441c71:
        fsubr dword ptr [data_00470bd4]
    L_00441c77:
        fmul st,st(1)
    L_00441c79:
        fmul st,st(1)
    L_00441c7b:
        fld dword ptr [data_00470afc]
    L_00441c81:
        fsub st,st(2)
    L_00441c83:
        fld st(0)
    L_00441c85:
        fmulp st(1),st
    L_00441c87:
        fmul st,st(2)
    L_00441c89:
        fld dword ptr [esp]
    L_00441c8c:
        fmul st,st(3)
    L_00441c8e:
        fmul st,st(3)
    L_00441c90:
        fld st(0)
    L_00441c92:
        fmul dword ptr [esi+18h]
    L_00441c95:
        fstp dword ptr [esp+10h]
    L_00441c99:
        fmul dword ptr [esi+1Ch]
    L_00441c9c:
        fstp dword ptr [esp+14h]
    L_00441ca0:
        fld st(0)
    L_00441ca2:
        fmul dword ptr [esi+10h]
    L_00441ca5:
        fstp dword ptr [esp]
    L_00441ca8:
        fmul dword ptr [esi+14h]
    L_00441cab:
        fstp dword ptr [esp+4]
    L_00441caf:
        fld st(0)
    L_00441cb1:
        fmul dword ptr [esi+8]
    L_00441cb4:
        fstp dword ptr [esp+18h]
    L_00441cb8:
        fmul dword ptr [esi+0Ch]
    L_00441cbb:
        fstp st(1)
    L_00441cbd:
        fld dword ptr [esp+8]
    L_00441cc1:
        fmul dword ptr [esi]
    L_00441cc3:
        fld dword ptr [esp+8]
    L_00441cc7:
        fmul dword ptr [esi+4]
    L_00441cca:
        fstp dword ptr [esp+0Ch]
    L_00441cce:
        fadd dword ptr [esp+18h]
    L_00441cd2:
        fld dword ptr [esp+0Ch]
    L_00441cd6:
        fadd st,st(2)
    L_00441cd8:
        fstp dword ptr [esp+1Ch]
    L_00441cdc:
        fadd dword ptr [esp]
    L_00441cdf:
        fstp st(1)
    L_00441ce1:
        fld dword ptr [esp+1Ch]
    L_00441ce5:
        fadd dword ptr [esp+4]
    L_00441ce9:
        fxch
    L_00441ceb:
        fadd dword ptr [esp+10h]
    L_00441cef:
        fstp dword ptr [esp+8]
    L_00441cf3:
        mov eax,dword ptr [esp+8]
    L_00441cf7:
        mov dword ptr [edi],eax
    L_00441cf9:
        fadd dword ptr [esp+14h]
    L_00441cfd:
        mov eax,edi
    L_00441cff:
        fstp dword ptr [esp+0Ch]
    L_00441d03:
        mov ecx,dword ptr [esp+0Ch]
    L_00441d07:
        mov dword ptr [edi+4],ecx
    L_00441d0a:
        add esp,20h
    L_00441d0d:
        ret
    L_00441d0e:
        mov edx,dword ptr [esi+28h]
    L_00441d11:
        push ecx
    L_00441d12:
        fstp dword ptr [esp]
    L_00441d15:
        push edx
    L_00441d16:
        call asm_FUN_0044c350_0044c350
    L_00441d1b:
        fld dword ptr [esi+8]
    L_00441d1e:
        fsub dword ptr [esi]
    L_00441d20:
        fld dword ptr [esi+0Ch]
    L_00441d23:
        fsub dword ptr [esi+4]
    L_00441d26:
        fstp dword ptr [esp+1Ch]
    L_00441d2a:
        fmul st,st(1)
    L_00441d2c:
        fld dword ptr [esp+1Ch]
    L_00441d30:
        fmul st,st(2)
    L_00441d32:
        fstp dword ptr [esp+1Ch]
    L_00441d36:
        fadd dword ptr [esi]
    L_00441d38:
        fstp dword ptr [esp+10h]
    L_00441d3c:
        mov eax,dword ptr [esp+10h]
    L_00441d40:
        fstp st(0)
    L_00441d42:
        fld dword ptr [esp+1Ch]
    L_00441d46:
        fadd dword ptr [esi+4]
    L_00441d49:
        mov dword ptr [edi],eax
    L_00441d4b:
        mov eax,edi
    L_00441d4d:
        fstp dword ptr [esp+14h]
    L_00441d51:
        mov ecx,dword ptr [esp+14h]
    L_00441d55:
        mov dword ptr [edi+4],ecx
    L_00441d58:
        add esp,20h
    L_00441d5b:
        ret
    }
}
