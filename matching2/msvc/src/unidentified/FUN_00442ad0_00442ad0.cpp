#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00442AD0..0x00442F26: FUN_00442ad0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00442ad0_00442ad0() {
    __asm {
    L_00442ad0:
        fld dword ptr [data_004978c0]
    L_00442ad6:
        sub esp,0Ch
    L_00442ad9:
        push ebx
    L_00442ada:
        push ebp
    L_00442adb:
        push esi
    L_00442adc:
        mov esi,ecx
    L_00442ade:
        fadd dword ptr [esi+5Ch]
    L_00442ae1:
        mov bl,byte ptr [esp+1Ch]
    L_00442ae5:
        test bl,1
    L_00442ae8:
        push edi
    L_00442ae9:
        fstp dword ptr [data_004978c0]
    L_00442aef:
        mov edi,eax
    L_00442af1:
        fld dword ptr [data_004978c4]
    L_00442af7:
        fadd dword ptr [esi+60h]
    L_00442afa:
        fstp dword ptr [data_004978c4]
    L_00442b00:
        fld dword ptr [data_004978dc]
    L_00442b06:
        fadd dword ptr [esi+5Ch]
    L_00442b09:
        fstp dword ptr [data_004978dc]
    L_00442b0f:
        fld dword ptr [data_004978e0]
    L_00442b15:
        fadd dword ptr [esi+60h]
    L_00442b18:
        fstp dword ptr [data_004978e0]
    L_00442b1e:
        fld dword ptr [data_004978f8]
    L_00442b24:
        fadd dword ptr [esi+5Ch]
    L_00442b27:
        fstp dword ptr [data_004978f8]
    L_00442b2d:
        fld dword ptr [data_004978fc]
    L_00442b33:
        fadd dword ptr [esi+60h]
    L_00442b36:
        fstp dword ptr [data_004978fc]
    L_00442b3c:
        fld dword ptr [data_00497914]
    L_00442b42:
        fadd dword ptr [esi+5Ch]
    L_00442b45:
        fstp dword ptr [data_00497914]
    L_00442b4b:
        fld dword ptr [data_00497918]
    L_00442b51:
        fadd dword ptr [esi+60h]
    L_00442b54:
        fstp dword ptr [data_00497918]
    L_00442b5a:
        je short L_00442bc4
    L_00442b5c:
        fld dword ptr [data_004978c0]
    L_00442b62:
        frndint
    L_00442b64:
        fsub dword ptr [data_004700e8]
    L_00442b6a:
        fld dword ptr [data_004978dc]
    L_00442b70:
        frndint
    L_00442b72:
        fsub dword ptr [data_004700e8]
    L_00442b78:
        fld dword ptr [data_004978c4]
    L_00442b7e:
        frndint
    L_00442b80:
        fsub dword ptr [data_004700e8]
    L_00442b86:
        fld dword ptr [data_004978fc]
    L_00442b8c:
        frndint
    L_00442b8e:
        fsub dword ptr [data_004700e8]
    L_00442b94:
        fst dword ptr [data_004978fc]
    L_00442b9a:
        fstp dword ptr [data_00497918]
    L_00442ba0:
        fst dword ptr [data_004978c4]
    L_00442ba6:
        fstp dword ptr [data_004978e0]
    L_00442bac:
        fst dword ptr [data_004978dc]
    L_00442bb2:
        fstp dword ptr [data_00497914]
    L_00442bb8:
        fst dword ptr [data_004978c0]
    L_00442bbe:
        fstp dword ptr [data_004978f8]
    L_00442bc4:
        mov eax,dword ptr [edi+394h]
    L_00442bca:
        fld dword ptr [eax+28h]
    L_00442bcd:
        fadd dword ptr [edi+54h]
    L_00442bd0:
        fst dword ptr [data_0049790c]
    L_00442bd6:
        fstp dword ptr [data_004978d4]
    L_00442bdc:
        mov ecx,dword ptr [edi+394h]
    L_00442be2:
        fld dword ptr [ecx+20h]
    L_00442be5:
        fadd dword ptr [edi+54h]
    L_00442be8:
        fst dword ptr [data_00497928]
    L_00442bee:
        fstp dword ptr [data_004978f0]
    L_00442bf4:
        mov edx,dword ptr [edi+394h]
    L_00442bfa:
        fld dword ptr [edx+24h]
    L_00442bfd:
        fadd dword ptr [edi+58h]
    L_00442c00:
        fst dword ptr [data_004978f4]
    L_00442c06:
        fstp dword ptr [data_004978d8]
    L_00442c0c:
        mov eax,dword ptr [edi+394h]
    L_00442c12:
        fld dword ptr [eax+2Ch]
    L_00442c15:
        fadd dword ptr [edi+58h]
    L_00442c18:
        fst dword ptr [data_0049792c]
    L_00442c1e:
        fstp dword ptr [data_00497910]
    L_00442c24:
        fld dword ptr [data_004978c0]
    L_00442c2a:
        fcomp dword ptr [data_004978dc]
    L_00442c30:
        fnstsw ax
    L_00442c32:
        test ah,41h
    L_00442c35:
        jne short L_00442c3f
    L_00442c37:
        fld dword ptr [data_004978c0]
    L_00442c3d:
        jmp short L_00442c45
    L_00442c3f:
        fld dword ptr [data_004978dc]
    L_00442c45:
        fld dword ptr [data_004978f8]
    L_00442c4b:
        fcomp
    L_00442c4d:
        fnstsw ax
    L_00442c4f:
        test ah,41h
    L_00442c52:
        jne short L_00442c5c
    L_00442c54:
        fstp st(0)
    L_00442c56:
        fld dword ptr [data_004978f8]
    L_00442c5c:
        fld dword ptr [data_00497914]
    L_00442c62:
        fcomp
    L_00442c64:
        fnstsw ax
    L_00442c66:
        test ah,41h
    L_00442c69:
        jne short L_00442c73
    L_00442c6b:
        fstp st(0)
    L_00442c6d:
        fld dword ptr [data_00497914]
    L_00442c73:
        fld dword ptr [data_004978c4]
    L_00442c79:
        fcomp dword ptr [data_004978e0]
    L_00442c7f:
        fnstsw ax
    L_00442c81:
        test ah,41h
    L_00442c84:
        jne short L_00442c92
    L_00442c86:
        mov ecx,dword ptr [data_004978c4]
    L_00442c8c:
        mov dword ptr [esp+20h],ecx
    L_00442c90:
        jmp short L_00442c9c
    L_00442c92:
        mov edx,dword ptr [data_004978e0]
    L_00442c98:
        mov dword ptr [esp+20h],edx
    L_00442c9c:
        fld dword ptr [data_004978fc]
    L_00442ca2:
        fcomp dword ptr [esp+20h]
    L_00442ca6:
        fnstsw ax
    L_00442ca8:
        test ah,41h
    L_00442cab:
        jne short L_00442cb6
    L_00442cad:
        mov eax,dword ptr [data_004978fc]
    L_00442cb2:
        mov dword ptr [esp+20h],eax
    L_00442cb6:
        fld dword ptr [data_00497918]
    L_00442cbc:
        fcomp dword ptr [esp+20h]
    L_00442cc0:
        fnstsw ax
    L_00442cc2:
        test ah,41h
    L_00442cc5:
        jne short L_00442cd1
    L_00442cc7:
        mov ecx,dword ptr [data_00497918]
    L_00442ccd:
        mov dword ptr [esp+20h],ecx
    L_00442cd1:
        fld dword ptr [data_004978c0]
    L_00442cd7:
        fcomp dword ptr [data_004978dc]
    L_00442cdd:
        fnstsw ax
    L_00442cdf:
        test ah,5
    L_00442ce2:
        jp short L_00442cf0
    L_00442ce4:
        mov edx,dword ptr [data_004978c0]
    L_00442cea:
        mov dword ptr [esp+10h],edx
    L_00442cee:
        jmp short L_00442cf9
    L_00442cf0:
        mov eax,dword ptr [data_004978dc]
    L_00442cf5:
        mov dword ptr [esp+10h],eax
    L_00442cf9:
        fld dword ptr [data_004978f8]
    L_00442cff:
        fcomp dword ptr [esp+10h]
    L_00442d03:
        fnstsw ax
    L_00442d05:
        test ah,5
    L_00442d08:
        jp short L_00442d14
    L_00442d0a:
        mov ecx,dword ptr [data_004978f8]
    L_00442d10:
        mov dword ptr [esp+10h],ecx
    L_00442d14:
        fld dword ptr [data_00497914]
    L_00442d1a:
        fcomp dword ptr [esp+10h]
    L_00442d1e:
        fnstsw ax
    L_00442d20:
        test ah,5
    L_00442d23:
        jp short L_00442d2f
    L_00442d25:
        mov edx,dword ptr [data_00497914]
    L_00442d2b:
        mov dword ptr [esp+10h],edx
    L_00442d2f:
        fld dword ptr [data_004978c4]
    L_00442d35:
        fcomp dword ptr [data_004978e0]
    L_00442d3b:
        fnstsw ax
    L_00442d3d:
        test ah,5
    L_00442d40:
        jp short L_00442d4d
    L_00442d42:
        mov eax,dword ptr [data_004978c4]
    L_00442d47:
        mov dword ptr [esp+14h],eax
    L_00442d4b:
        jmp short L_00442d57
    L_00442d4d:
        mov ecx,dword ptr [data_004978e0]
    L_00442d53:
        mov dword ptr [esp+14h],ecx
    L_00442d57:
        fld dword ptr [data_004978fc]
    L_00442d5d:
        fcomp dword ptr [esp+14h]
    L_00442d61:
        fnstsw ax
    L_00442d63:
        test ah,5
    L_00442d66:
        jp short L_00442d72
    L_00442d68:
        mov edx,dword ptr [data_004978fc]
    L_00442d6e:
        mov dword ptr [esp+14h],edx
    L_00442d72:
        fld dword ptr [data_00497918]
    L_00442d78:
        fcomp dword ptr [esp+14h]
    L_00442d7c:
        fnstsw ax
    L_00442d7e:
        test ah,5
    L_00442d81:
        jp short L_00442d8c
    L_00442d83:
        mov eax,dword ptr [data_00497918]
    L_00442d88:
        mov dword ptr [esp+14h],eax
    L_00442d8c:
        mov ecx,dword ptr [data_00491fac]
    L_00442d92:
        mov ebp,dword ptr [ecx+0CCh]
    L_00442d98:
        fild dword ptr [ecx+0CCh]
    L_00442d9e:
        test ebp,ebp
    L_00442da0:
        jge short L_00442da8
    L_00442da2:
        fadd dword ptr [data_00470b98]
    L_00442da8:
        fxch
    L_00442daa:
        fcompp
    L_00442dac:
        fnstsw ax
    L_00442dae:
        test ah,5
    L_00442db1:
        jnp asm_target_00442f1b
    L_00442db7:
        mov edx,dword ptr [ecx+0D0h]
    L_00442dbd:
        fild dword ptr [ecx+0D0h]
    L_00442dc3:
        test edx,edx
    L_00442dc5:
        jge short L_00442dcd
    L_00442dc7:
        fadd dword ptr [data_00470b98]
    L_00442dcd:
        fcomp dword ptr [esp+20h]
    L_00442dd1:
        fnstsw ax
    L_00442dd3:
        test ah,41h
    L_00442dd6:
        je asm_target_00442f1b
    L_00442ddc:
        mov eax,dword ptr [ecx+0D4h]
    L_00442de2:
        add eax,ebp
    L_00442de4:
        test eax,eax
    L_00442de6:
        mov dword ptr [esp+20h],eax
    L_00442dea:
        fild dword ptr [esp+20h]
    L_00442dee:
        jge short L_00442df6
    L_00442df0:
        fadd dword ptr [data_00470b98]
    L_00442df6:
        fcomp dword ptr [esp+10h]
    L_00442dfa:
        fnstsw ax
    L_00442dfc:
        test ah,5
    L_00442dff:
        jnp asm_target_00442f1b
    L_00442e05:
        mov ecx,dword ptr [ecx+0D8h]
    L_00442e0b:
        add ecx,edx
    L_00442e0d:
        test ecx,ecx
    L_00442e0f:
        mov dword ptr [esp+20h],ecx
    L_00442e13:
        fild dword ptr [esp+20h]
    L_00442e17:
        jge short L_00442e1f
    L_00442e19:
        fadd dword ptr [data_00470b98]
    L_00442e1f:
        fcomp dword ptr [esp+14h]
    L_00442e23:
        fnstsw ax
    L_00442e25:
        test ah,5
    L_00442e28:
        jnp asm_target_00442f1b
    L_00442e2e:
        mov edx,dword ptr [edi+394h]
    L_00442e34:
        mov eax,dword ptr [edx+4]
    L_00442e37:
        cmp dword ptr [esi+3ADA64h],eax
    L_00442e3d:
        je short L_00442e61
    L_00442e3f:
        mov dword ptr [esi+3ADA64h],eax
    L_00442e45:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00442e4a:
        mov edx,dword ptr [esi+3ADA64h]
    L_00442e50:
        mov eax,dword ptr [data_00491c30]
    L_00442e55:
        mov ecx,dword ptr [eax]
    L_00442e57:
        push edx
    L_00442e58:
        push 0
    L_00442e5a:
        push eax
    L_00442e5b:
        call dword ptr [ecx+104h]
    L_00442e61:
        cmp byte ptr [esi+3ADA6Ah],1
    L_00442e68:
        je short L_00442e76
    L_00442e6a:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00442e6f:
        mov byte ptr [esi+3ADA6Ah],1
    L_00442e76:
        test bl,2
    L_00442e79:
        jne asm_target_00442f08
    L_00442e7f:
        mov eax,dword ptr [edi+35Ch]
    L_00442e85:
        test ah,ah
    L_00442e87:
        jns short L_00442e91
    L_00442e89:
        mov eax,dword ptr [edi+300h]
    L_00442e8f:
        jmp short L_00442e97
    L_00442e91:
        mov eax,dword ptr [edi+2FCh]
    L_00442e97:
        mov ecx,dword ptr [esi+73245Ch]
    L_00442e9d:
        test ecx,ecx
    L_00442e9f:
        mov dword ptr [esp+20h],eax
    L_00442ea3:
        je short L_00442ef4
    L_00442ea5:
        mov cl,byte ptr [esi+73245Ah]
    L_00442eab:
        shr eax,10h
    L_00442eae:
        call asm_AnimationColor_MultiplyChannel_004423c0
    L_00442eb3:
        mov cl,byte ptr [esi+732459h]
    L_00442eb9:
        mov byte ptr [esp+22h],al
    L_00442ebd:
        mov al,byte ptr [esp+21h]
    L_00442ec1:
        call asm_AnimationColor_MultiplyChannel_004423c0
    L_00442ec6:
        mov cl,byte ptr [esi+732458h]
    L_00442ecc:
        mov byte ptr [esp+21h],al
    L_00442ed0:
        mov al,byte ptr [esp+20h]
    L_00442ed4:
        call asm_AnimationColor_MultiplyChannel_004423c0
    L_00442ed9:
        mov cl,byte ptr [esi+73245Bh]
    L_00442edf:
        mov byte ptr [esp+20h],al
    L_00442ee3:
        mov al,byte ptr [esp+23h]
    L_00442ee7:
        call asm_AnimationColor_MultiplyChannel_004423c0
    L_00442eec:
        mov byte ptr [esp+23h],al
    L_00442ef0:
        mov eax,dword ptr [esp+20h]
    L_00442ef4:
        mov dword ptr [data_004978d0],eax
    L_00442ef9:
        mov dword ptr [data_004978ec],eax
    L_00442efe:
        mov dword ptr [data_00497908],eax
    L_00442f03:
        mov dword ptr [data_00497924],eax
    L_00442f08:
        mov eax,esi
    L_00442f0a:
        call asm_AnmManager_SyncEntityRenderStateRetail_004425a0
    L_00442f0f:
        mov edx,4978C0h
    L_00442f14:
        mov eax,esi
    L_00442f16:
        call asm_AnimationManager_AppendQuadVertices_00442fe0
    L_00442f1b:
        pop edi
    L_00442f1c:
        pop esi
    L_00442f1d:
        pop ebp
    L_00442f1e:
        xor eax,eax
    L_00442f20:
        pop ebx
    L_00442f21:
        add esp,0Ch
    L_00442f24:
        ret 4
    }
}
