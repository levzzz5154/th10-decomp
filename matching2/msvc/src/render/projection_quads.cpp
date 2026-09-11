#include "asm_encoding.hpp"
#include "asm_symbols.hpp"


// 0x00443B60..0x00443F76: FUN_00443b60
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00443b60_00443b60() {
    __asm {
    L_00443b60:
        sub esp,0A0h
    L_00443b66:
        push esi
    L_00443b67:
        mov esi,eax
    L_00443b69:
        mov eax,dword ptr [esi+2Ch]
    L_00443b6c:
        mov dword ptr [esp+48h],eax
    L_00443b70:
        fld dword ptr [esp+48h]
    L_00443b74:
        fsincos
    L_00443b76:
        fstp dword ptr [esp+4]
    L_00443b7a:
        fstp dword ptr [esp+8]
    L_00443b7e:
        fld dword ptr [esi+34Ch]
    L_00443b84:
        fadd dword ptr [esi+340h]
    L_00443b8a:
        mov eax,dword ptr [data_00491fac]
    L_00443b8f:
        lea edx,[eax+4Ch]
    L_00443b92:
        lea ecx,[esp+64h]
    L_00443b96:
        fadd dword ptr [esi+334h]
    L_00443b9c:
        push ecx
    L_00443b9d:
        push edx
    L_00443b9e:
        lea ecx,[eax+8Ch]
    L_00443ba4:
        fstp dword ptr [esp+9Ch]
    L_00443bab:
        push ecx
    L_00443bac:
        fld dword ptr [esi+350h]
    L_00443bb2:
        add eax,0CCh
    L_00443bb7:
        fadd dword ptr [esi+344h]
    L_00443bbd:
        push eax
    L_00443bbe:
        lea edx,[esp+24h]
    L_00443bc2:
        push edx
    L_00443bc3:
        fadd dword ptr [esi+338h]
    L_00443bc9:
        lea eax,[esp+48h]
    L_00443bcd:
        push eax
    L_00443bce:
        mov dword ptr [esp+2Ch],0
    L_00443bd6:
        fstp dword ptr [esp+0B0h]
    L_00443bdd:
        mov dword ptr [esp+30h],0
    L_00443be5:
        fld dword ptr [esi+354h]
    L_00443beb:
        mov dword ptr [esp+34h],0
    L_00443bf3:
        fadd dword ptr [esi+348h]
    L_00443bf9:
        mov dword ptr [esp+0A8h],0
    L_00443c04:
        mov dword ptr [esp+0A0h],0
    L_00443c0f:
        mov dword ptr [esp+9Ch],0
    L_00443c1a:
        fadd dword ptr [esi+33Ch]
    L_00443c20:
        mov dword ptr [esp+98h],0
    L_00443c2b:
        mov dword ptr [esp+94h],0
    L_00443c36:
        mov dword ptr [esp+8Ch],0
    L_00443c41:
        fstp dword ptr [esp+0B4h]
    L_00443c48:
        mov dword ptr [esp+88h],0
    L_00443c53:
        mov dword ptr [esp+84h],0
    L_00443c5e:
        mov dword ptr [esp+80h],0
    L_00443c69:
        mov dword ptr [esp+0B8h],3F800000h
    L_00443c74:
        mov dword ptr [esp+0A4h],3F800000h
    L_00443c7f:
        mov dword ptr [esp+90h],3F800000h
    L_00443c8a:
        mov dword ptr [esp+7Ch],3F800000h
    L_00443c92:
        call asm_D3DXVec3Project_0045218e
    L_00443c97:
        fld dword ptr [esp+3Ch]
    L_00443c9b:
        fcomp dword ptr [data_00470b04]
    L_00443ca1:
        fnstsw ax
    L_00443ca3:
        test ah,5
    L_00443ca6:
        jnp asm_target_00443f6c
    L_00443cac:
        fld dword ptr [esp+3Ch]
    L_00443cb0:
        fcomp dword ptr [data_00470afc]
    L_00443cb6:
        fnstsw ax
    L_00443cb8:
        test ah,41h
    L_00443cbb:
        je asm_target_00443f6c
    L_00443cc1:
        mov eax,dword ptr [data_00491fac]
    L_00443cc6:
        lea edx,[eax+4Ch]
    L_00443cc9:
        lea ecx,[esp+64h]
    L_00443ccd:
        push ecx
    L_00443cce:
        push edx
    L_00443ccf:
        lea ecx,[eax+8Ch]
    L_00443cd5:
        push ecx
    L_00443cd6:
        lea edx,[eax+0CCh]
    L_00443cdc:
        push edx
    L_00443cdd:
        add eax,30h
    L_00443ce0:
        push eax
    L_00443ce1:
        lea eax,[esp+6Ch]
    L_00443ce5:
        push eax
    L_00443ce6:
        call asm_D3DXVec3Project_0045218e
    L_00443ceb:
        fld dword ptr [esp+58h]
    L_00443cef:
        fsub dword ptr [esp+34h]
    L_00443cf3:
        fstp dword ptr [esp+24h]
    L_00443cf7:
        mov ecx,dword ptr [esp+24h]
    L_00443cfb:
        fld dword ptr [esp+5Ch]
    L_00443cff:
        mov dword ptr [esp+4Ch],ecx
    L_00443d03:
        fsub dword ptr [esp+38h]
    L_00443d07:
        mov ecx,dword ptr [esp+34h]
    L_00443d0b:
        mov dword ptr [esp+40h],ecx
    L_00443d0f:
        fstp dword ptr [esp+28h]
    L_00443d13:
        mov edx,dword ptr [esp+28h]
    L_00443d17:
        fld dword ptr [esp+60h]
    L_00443d1b:
        mov dword ptr [esp+50h],edx
    L_00443d1f:
        fsub dword ptr [esp+3Ch]
    L_00443d23:
        mov edx,dword ptr [esp+38h]
    L_00443d27:
        mov dword ptr [esp+44h],edx
    L_00443d2b:
        fstp dword ptr [esp+2Ch]
    L_00443d2f:
        mov eax,dword ptr [esp+2Ch]
    L_00443d33:
        mov dword ptr [esp+54h],eax
    L_00443d37:
        fld dword ptr [esp+54h]
    L_00443d3b:
        fmul dword ptr [esp+54h]
    L_00443d3f:
        mov eax,dword ptr [esp+3Ch]
    L_00443d43:
        fld dword ptr [esp+50h]
    L_00443d47:
        mov ecx,eax
    L_00443d49:
        fmul dword ptr [esp+50h]
    L_00443d4d:
        mov edx,eax
    L_00443d4f:
        faddp st(1),st
    L_00443d51:
        fld dword ptr [esp+4Ch]
    L_00443d55:
        fmul dword ptr [esp+4Ch]
    L_00443d59:
        faddp st(1),st
    L_00443d5b:
        fsqrt
    L_00443d5d:
        fmul dword ptr [data_00470b0c]
    L_00443d63:
        fld dword ptr [esi+4Ch]
    L_00443d66:
        fmul dword ptr [esi+3Ch]
    L_00443d69:
        fmul st,st(1)
    L_00443d6b:
        fstp dword ptr [esp+10h]
    L_00443d6f:
        fld dword ptr [esi+50h]
    L_00443d72:
        fmul dword ptr [esi+40h]
    L_00443d75:
        mov dword ptr [data_0049791c],eax
    L_00443d7a:
        mov dword ptr [data_00497900],ecx
    L_00443d80:
        mov dword ptr [data_004978e4],edx
    L_00443d86:
        fmul st,st(1)
    L_00443d88:
        mov dword ptr [data_004978c8],eax
    L_00443d8d:
        fstp dword ptr [esp+0Ch]
    L_00443d91:
        fstp st(0)
    L_00443d93:
        fld dword ptr [esp+48h]
    L_00443d97:
        fsincos
    L_00443d99:
        fstp dword ptr [esp+4]
    L_00443d9d:
        fstp dword ptr [esp+8]
    L_00443da1:
        mov esi,dword ptr [esi+35Ch]
    L_00443da7:
        mov eax,esi
    L_00443da9:
        shr eax,12h
    L_00443dac:
        and eax,3
    L_00443daf:
        sub eax,0
    L_00443db2:
        je short L_00443df6
    L_00443db4:
        dec eax
    L_00443db5:
        je short L_00443dd8
    L_00443db7:
        dec eax
    L_00443db8:
        jne short L_00443e18
    L_00443dba:
        fld dword ptr [esp+10h]
    L_00443dbe:
        mov dword ptr [esp+20h],0
    L_00443dc6:
        fchs
    L_00443dc8:
        fst dword ptr [esp+1Ch]
    L_00443dcc:
        fstp dword ptr [esp+14h]
    L_00443dd0:
        fld dword ptr [data_00470b04]
    L_00443dd6:
        jmp short L_00443e1c
    L_00443dd8:
        mov ecx,dword ptr [esp+10h]
    L_00443ddc:
        fld dword ptr [esp+10h]
    L_00443de0:
        mov dword ptr [esp+1Ch],0
    L_00443de8:
        mov dword ptr [esp+14h],0
    L_00443df0:
        mov dword ptr [esp+20h],ecx
    L_00443df4:
        jmp short L_00443e1c
    L_00443df6:
        fld dword ptr [esp+10h]
    L_00443dfa:
        fmul dword ptr [data_00470b78]
    L_00443e00:
        fst dword ptr [esp+1Ch]
    L_00443e04:
        fstp dword ptr [esp+14h]
    L_00443e08:
        fld dword ptr [esp+10h]
    L_00443e0c:
        fmul dword ptr [data_00470b0c]
    L_00443e12:
        fst dword ptr [esp+20h]
    L_00443e16:
        jmp short L_00443e1c
    L_00443e18:
        fld dword ptr [esp+18h]
    L_00443e1c:
        shr esi,14h
    L_00443e1f:
        and esi,3
    L_00443e22:
        sub esi,0
    L_00443e25:
        je short L_00443e69
    L_00443e27:
        dec esi
    L_00443e28:
        je short L_00443e4b
    L_00443e2a:
        dec esi
    L_00443e2b:
        jne short L_00443e8b
    L_00443e2d:
        fld dword ptr [esp+0Ch]
    L_00443e31:
        mov dword ptr [esp+30h],0
    L_00443e39:
        fchs
    L_00443e3b:
        fst dword ptr [esp+28h]
    L_00443e3f:
        fstp dword ptr [esp+24h]
    L_00443e43:
        fld dword ptr [data_00470b04]
    L_00443e49:
        jmp short L_00443e8f
    L_00443e4b:
        mov edx,dword ptr [esp+0Ch]
    L_00443e4f:
        fld dword ptr [esp+0Ch]
    L_00443e53:
        mov dword ptr [esp+28h],0
    L_00443e5b:
        mov dword ptr [esp+24h],0
    L_00443e63:
        mov dword ptr [esp+30h],edx
    L_00443e67:
        jmp short L_00443e8f
    L_00443e69:
        fld dword ptr [esp+0Ch]
    L_00443e6d:
        fmul dword ptr [data_00470b78]
    L_00443e73:
        fst dword ptr [esp+28h]
    L_00443e77:
        fstp dword ptr [esp+24h]
    L_00443e7b:
        fld dword ptr [esp+0Ch]
    L_00443e7f:
        fmul dword ptr [data_00470b0c]
    L_00443e85:
        fst dword ptr [esp+30h]
    L_00443e89:
        jmp short L_00443e8f
    L_00443e8b:
        fld dword ptr [esp+2Ch]
    L_00443e8f:
        fld dword ptr [esp+14h]
    L_00443e93:
        xor eax,eax
    L_00443e95:
        fmul dword ptr [esp+4]
    L_00443e99:
        pop esi
    L_00443e9a:
        fld dword ptr [esp+20h]
    L_00443e9e:
        fmul dword ptr [esp+4]
    L_00443ea2:
        fsubp st(1),st
    L_00443ea4:
        fadd dword ptr [esp+3Ch]
    L_00443ea8:
        fstp dword ptr [data_004978c0]
    L_00443eae:
        fld dword ptr [esp+20h]
    L_00443eb2:
        fmul dword ptr [esp]
    L_00443eb5:
        fld dword ptr [esp+10h]
    L_00443eb9:
        fmul dword ptr [esp+4]
    L_00443ebd:
        faddp st(1),st
    L_00443ebf:
        fadd dword ptr [esp+40h]
    L_00443ec3:
        fstp dword ptr [data_004978c4]
    L_00443ec9:
        fld st(1)
    L_00443ecb:
        fmul dword ptr [esp]
    L_00443ece:
        fld dword ptr [esp+24h]
    L_00443ed2:
        fmul dword ptr [esp+4]
    L_00443ed6:
        fsubp st(1),st
    L_00443ed8:
        fadd dword ptr [esp+3Ch]
    L_00443edc:
        fstp dword ptr [data_004978dc]
    L_00443ee2:
        fxch
    L_00443ee4:
        fmul dword ptr [esp+4]
    L_00443ee8:
        fld dword ptr [esp+24h]
    L_00443eec:
        fmul dword ptr [esp]
    L_00443eef:
        faddp st(1),st
    L_00443ef1:
        fadd dword ptr [esp+40h]
    L_00443ef5:
        fstp dword ptr [data_004978e0]
    L_00443efb:
        fld dword ptr [esp+18h]
    L_00443eff:
        fmul dword ptr [esp]
    L_00443f02:
        fld st(1)
    L_00443f04:
        fmul dword ptr [esp+4]
    L_00443f08:
        fsubp st(1),st
    L_00443f0a:
        fadd dword ptr [esp+3Ch]
    L_00443f0e:
        fstp dword ptr [data_004978f8]
    L_00443f14:
        fld dword ptr [esp]
    L_00443f17:
        fmul st,st(1)
    L_00443f19:
        fld dword ptr [esp+18h]
    L_00443f1d:
        fmul dword ptr [esp+4]
    L_00443f21:
        faddp st(1),st
    L_00443f23:
        fadd dword ptr [esp+40h]
    L_00443f27:
        fstp dword ptr [data_004978fc]
    L_00443f2d:
        fld dword ptr [esp+1Ch]
    L_00443f31:
        fmul dword ptr [esp]
    L_00443f34:
        fld dword ptr [esp+2Ch]
    L_00443f38:
        fmul dword ptr [esp+4]
    L_00443f3c:
        fsubp st(1),st
    L_00443f3e:
        fadd dword ptr [esp+3Ch]
    L_00443f42:
        fstp dword ptr [data_00497914]
    L_00443f48:
        fld dword ptr [esp+2Ch]
    L_00443f4c:
        fmul dword ptr [esp]
    L_00443f4f:
        fld dword ptr [esp+1Ch]
    L_00443f53:
        fmul dword ptr [esp+4]
    L_00443f57:
        faddp st(1),st
    L_00443f59:
        fadd dword ptr [esp+40h]
    L_00443f5d:
        fstp dword ptr [data_00497918]
    L_00443f63:
        fstp st(0)
    L_00443f65:
        add esp,0A0h
    L_00443f6b:
        ret
    L_00443f6c:
        or eax,0FFFFFFFFh
    L_00443f6f:
        pop esi
    L_00443f70:
        add esp,0A0h
    L_00443f76:
        ret
    }
}

