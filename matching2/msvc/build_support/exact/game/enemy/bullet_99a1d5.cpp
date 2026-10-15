#include "th10/source_views/bullet_99a1d5_0.hpp"
static void ClearActiveFlag(unsigned* flag) {
    *flag &= ~1u;
}
#include "../../../../src/game/enemy/entity_clear_anims.cpp"
#include "th10/source_views/bullet_99a1d5_1.hpp"
extern "C" __declspec(naked) void __cdecl asm_FUN_0040dc80_0040dc80() {
    __asm {
    L_0040dc80:
        sub esp,18h
    L_0040dc83:
        push ebp
    L_0040dc84:
        mov ebp,dword ptr [esp+20h]
    L_0040dc88:
        mov eax,dword ptr [ebp+1444h]
    L_0040dc8e:
        test ah,4
    L_0040dc91:
        je short L_0040dc9c
    L_0040dc93:
        xor eax,eax
    L_0040dc95:
        pop ebp
    L_0040dc96:
        add esp,18h
    L_0040dc99:
        ret 4
    L_0040dc9c:
        or eax,400h
    L_0040dca1:
        push esi
    L_0040dca2:
        push edi
    L_0040dca3:
        mov dword ptr [ebp+1444h],eax
    L_0040dca9:
        mov eax,dword ptr [ebp+208h]
    L_0040dcaf:
        test eax,eax
    L_0040dcb1:
        lea esi,[ebp+2Ch]
    L_0040dcb4:
        mov ecx,0Bh
    L_0040dcb9:
        mov edi,ebp
    L_0040dcbb:
        rep movsd
    L_0040dcbd:
        je short L_0040dce2
    L_0040dcbf:
        lea esi,[ebp+1D4h]
    L_0040dcc5:
        lea edi,[esp+0Ch]
    L_0040dcc9:
        call asm_FUN_00412ac0_00412ac0
    L_0040dcce:
        mov eax,dword ptr [esp+0Ch]
    L_0040dcd2:
        push eax
    L_0040dcd3:
        call asm_Angle_Normalize_0044bc70
    L_0040dcd8:
        fstp dword ptr [ebp+74h]
    L_0040dcdb:
        mov ecx,dword ptr [esp+10h]
    L_0040dcdf:
        mov dword ptr [ebp+70h],ecx
    L_0040dce2:
        mov eax,dword ptr [ebp+280h]
    L_0040dce8:
        test eax,eax
    L_0040dcea:
        je short L_0040dd09
    L_0040dcec:
        lea esi,[ebp+24Ch]
    L_0040dcf2:
        lea edi,[esp+0Ch]
    L_0040dcf6:
        call asm_FUN_00412ac0_00412ac0
    L_0040dcfb:
        mov edx,dword ptr [esp+0Ch]
    L_0040dcff:
        mov eax,dword ptr [esp+10h]
    L_0040dd03:
        mov dword ptr [ebp+78h],edx
    L_0040dd06:
        mov dword ptr [ebp+7Ch],eax
    L_0040dd09:
        mov eax,dword ptr [ebp+244h]
    L_0040dd0f:
        test eax,eax
    L_0040dd11:
        je short L_0040dd3c
    L_0040dd13:
        lea esi,[ebp+210h]
    L_0040dd19:
        lea edi,[esp+0Ch]
    L_0040dd1d:
        call asm_FUN_00412ac0_00412ac0
    L_0040dd22:
        mov ecx,dword ptr [esp+0Ch]
    L_0040dd26:
        push ecx
    L_0040dd27:
        call asm_Angle_Normalize_0044bc70
    L_0040dd2c:
        fstp dword ptr [ebp+0A0h]
    L_0040dd32:
        mov edx,dword ptr [esp+10h]
    L_0040dd36:
        mov dword ptr [ebp+9Ch],edx
    L_0040dd3c:
        mov eax,dword ptr [ebp+2BCh]
    L_0040dd42:
        test eax,eax
    L_0040dd44:
        je short L_0040dd69
    L_0040dd46:
        lea esi,[ebp+288h]
    L_0040dd4c:
        lea edi,[esp+0Ch]
    L_0040dd50:
        call asm_FUN_00412ac0_00412ac0
    L_0040dd55:
        mov eax,dword ptr [esp+0Ch]
    L_0040dd59:
        mov ecx,dword ptr [esp+10h]
    L_0040dd5d:
        mov dword ptr [ebp+0A4h],eax
    L_0040dd63:
        mov dword ptr [ebp+0A8h],ecx
    L_0040dd69:
        mov eax,dword ptr [ebp+180h]
    L_0040dd6f:
        test eax,eax
    L_0040dd71:
        je short L_0040ddb8
    L_0040dd73:
        lea eax,[ebp+13Ch]
    L_0040dd79:
        lea edi,[esp+18h]
    L_0040dd7d:
        call asm_FUN_00404610_00404610
    L_0040dd82:
        fld dword ptr [eax]
    L_0040dd84:
        fsub dword ptr [ebp+58h]
    L_0040dd87:
        lea edx,[ebp+64h]
    L_0040dd8a:
        fstp dword ptr [esp+0Ch]
    L_0040dd8e:
        fld dword ptr [eax+4]
    L_0040dd91:
        fsub dword ptr [ebp+5Ch]
    L_0040dd94:
        fstp dword ptr [esp+10h]
    L_0040dd98:
        mov ecx,dword ptr [esp+10h]
    L_0040dd9c:
        fld dword ptr [eax+8]
    L_0040dd9f:
        mov eax,dword ptr [esp+0Ch]
    L_0040dda3:
        fsub dword ptr [ebp+60h]
    L_0040dda6:
        mov dword ptr [edx],eax
    L_0040dda8:
        mov dword ptr [edx+4],ecx
    L_0040ddab:
        fstp dword ptr [esp+14h]
    L_0040ddaf:
        mov eax,dword ptr [esp+14h]
    L_0040ddb3:
        mov dword ptr [edx+8],eax
    L_0040ddb6:
        jmp short L_0040ddf5
    L_0040ddb8:
        test byte ptr [ebp+80h],1
    L_0040ddbf:
        jne short L_0040ddda
    L_0040ddc1:
        mov ecx,dword ptr [ebp+70h]
    L_0040ddc4:
        mov edx,dword ptr [ebp+74h]
    L_0040ddc7:
        push ecx
    L_0040ddc8:
        push edx
    L_0040ddc9:
        lea ecx,[ebp+64h]
    L_0040ddcc:
        call asm_Recovery_PolarToVectorRetail_0044c5d0
    L_0040ddd1:
        mov dword ptr [ebp+6Ch],0
    L_0040ddd8:
        jmp short L_0040ddf5
    L_0040ddda:
        fld dword ptr [ebp+7Ch]
    L_0040dddd:
        push ecx
    L_0040ddde:
        fadd dword ptr [ebp+78h]
    L_0040dde1:
        fstp dword ptr [ebp+78h]
    L_0040dde4:
        fld dword ptr [ebp+70h]
    L_0040dde7:
        fadd dword ptr [ebp+74h]
    L_0040ddea:
        fstp dword ptr [esp]
    L_0040dded:
        call asm_Angle_Normalize_0044bc70
    L_0040ddf2:
        fstp dword ptr [ebp+74h]
    L_0040ddf5:
        mov eax,dword ptr [ebp+1CCh]
    L_0040ddfb:
        test eax,eax
    L_0040ddfd:
        push ebx
    L_0040ddfe:
        lea ebx,[ebp+84h]
    L_0040de04:
        je short L_0040de4d
    L_0040de06:
        lea eax,[ebp+188h]
    L_0040de0c:
        lea edi,[esp+1Ch]
    L_0040de10:
        call asm_FUN_00404610_00404610
    L_0040de15:
        fld dword ptr [eax]
    L_0040de17:
        fsub dword ptr [ebx]
    L_0040de19:
        fstp dword ptr [esp+10h]
    L_0040de1d:
        mov ecx,dword ptr [esp+10h]
    L_0040de21:
        fld dword ptr [eax+4]
    L_0040de24:
        fsub dword ptr [ebx+4]
    L_0040de27:
        fstp dword ptr [esp+14h]
    L_0040de2b:
        mov edx,dword ptr [esp+14h]
    L_0040de2f:
        fld dword ptr [eax+8]
    L_0040de32:
        lea eax,[ebp+90h]
    L_0040de38:
        fsub dword ptr [ebx+8]
    L_0040de3b:
        mov dword ptr [eax],ecx
    L_0040de3d:
        mov dword ptr [eax+4],edx
    L_0040de40:
        fstp dword ptr [esp+18h]
    L_0040de44:
        mov ecx,dword ptr [esp+18h]
    L_0040de48:
        mov dword ptr [eax+8],ecx
    L_0040de4b:
        jmp short L_0040de87
    L_0040de4d:
        test byte ptr [ebx+28h],1
    L_0040de51:
        jne short L_0040de6c
    L_0040de53:
        mov edx,dword ptr [ebx+18h]
    L_0040de56:
        mov eax,dword ptr [ebx+1Ch]
    L_0040de59:
        push edx
    L_0040de5a:
        push eax
    L_0040de5b:
        lea ecx,[ebx+0Ch]
    L_0040de5e:
        call asm_Recovery_PolarToVectorRetail_0044c5d0
    L_0040de63:
        mov dword ptr [ebx+14h],0
    L_0040de6a:
        jmp short L_0040de87
    L_0040de6c:
        fld dword ptr [ebx+24h]
    L_0040de6f:
        push ecx
    L_0040de70:
        fadd dword ptr [ebx+20h]
    L_0040de73:
        fstp dword ptr [ebx+20h]
    L_0040de76:
        fld dword ptr [ebx+18h]
    L_0040de79:
        fadd dword ptr [ebx+1Ch]
    L_0040de7c:
        fstp dword ptr [esp]
    L_0040de7f:
        call asm_Angle_Normalize_0044bc70
    L_0040de84:
        fstp dword ptr [ebx+1Ch]
    L_0040de87:
        lea edi,[ebp+58h]
    L_0040de8a:
        mov esi,edi
    L_0040de8c:
        call asm_Recovery_AdvancePolarMotion_0044c2a0
    L_0040de91:
        test dword ptr [ebp+1444h],40000h
    L_0040de9b:
        je short L_0040debf
    L_0040de9d:
        fld dword ptr [data_00491e6c]
    L_0040dea3:
        fadd dword ptr [ebx]
    L_0040dea5:
        fstp dword ptr [ebx]
    L_0040dea7:
        fld dword ptr [data_00491e70]
    L_0040dead:
        fadd dword ptr [ebx+4]
    L_0040deb0:
        fstp dword ptr [ebx+4]
    L_0040deb3:
        fld dword ptr [data_00491e74]
    L_0040deb9:
        fadd dword ptr [ebx+8]
    L_0040debc:
        fstp dword ptr [ebx+8]
    L_0040debf:
        mov esi,ebx
    L_0040dec1:
        call asm_Recovery_AdvancePolarMotion_0044c2a0
    L_0040dec6:
        fld dword ptr [ebx]
    L_0040dec8:
        fadd dword ptr [edi]
    L_0040deca:
        lea esi,[ebp+2Ch]
    L_0040decd:
        fld dword ptr [ebx+4]
    L_0040ded0:
        lea eax,[ebp+38h]
    L_0040ded3:
        fadd dword ptr [edi+4]
    L_0040ded6:
        fld dword ptr [ebx+8]
    L_0040ded9:
        fadd dword ptr [edi+8]
    L_0040dedc:
        fstp dword ptr [esp+24h]
    L_0040dee0:
        fxch
    L_0040dee2:
        fsub dword ptr [esi]
    L_0040dee4:
        fstp dword ptr [esp+10h]
    L_0040dee8:
        mov ecx,dword ptr [esp+10h]
    L_0040deec:
        fsub dword ptr [esi+4]
    L_0040deef:
        fstp dword ptr [esp+14h]
    L_0040def3:
        mov edx,dword ptr [esp+14h]
    L_0040def7:
        fld dword ptr [esp+24h]
    L_0040defb:
        fsub dword ptr [esi+8]
    L_0040defe:
        mov dword ptr [eax],ecx
    L_0040df00:
        mov dword ptr [eax+4],edx
    L_0040df03:
        fstp dword ptr [esp+18h]
    L_0040df07:
        mov ecx,dword ptr [esp+18h]
    L_0040df0b:
        mov dword ptr [eax+8],ecx
    L_0040df0e:
        call asm_Recovery_AdvancePolarMotion_0044c2a0
    L_0040df13:
        mov ecx,dword ptr [ebp+1444h]
    L_0040df19:
        test ch,2
    L_0040df1c:
        je asm_target_0040dfda
    L_0040df22:
        fld dword ptr [ebp+13B4h]
    L_0040df28:
        fmul dword ptr [flt_0_5]
    L_0040df2e:
        fstp dword ptr [esp+2Ch]
    L_0040df32:
        fld dword ptr [ebp+13ACh]
    L_0040df38:
        fsub dword ptr [esp+2Ch]
    L_0040df3c:
        fcom dword ptr [esi]
    L_0040df3e:
        fnstsw ax
    L_0040df40:
        test ah,41h
    L_0040df43:
        jne short L_0040df49
    L_0040df45:
        fstp dword ptr [esi]
    L_0040df47:
        jmp short L_0040df64
    L_0040df49:
        fstp st(0)
    L_0040df4b:
        fld dword ptr [esp+2Ch]
    L_0040df4f:
        fadd dword ptr [ebp+13ACh]
    L_0040df55:
        fcom dword ptr [esi]
    L_0040df57:
        fnstsw ax
    L_0040df59:
        test ah,5
    L_0040df5c:
        jp short L_0040df62
    L_0040df5e:
        fstp dword ptr [esi]
    L_0040df60:
        jmp short L_0040df64
    L_0040df62:
        fstp st(0)
    L_0040df64:
        fld dword ptr [ebp+13B8h]
    L_0040df6a:
        fmul dword ptr [flt_0_5]
    L_0040df70:
        fstp dword ptr [esp+2Ch]
    L_0040df74:
        fld dword ptr [ebp+13B0h]
    L_0040df7a:
        fsub dword ptr [esp+2Ch]
    L_0040df7e:
        fcom dword ptr [ebp+30h]
    L_0040df81:
        fnstsw ax
    L_0040df83:
        test ah,41h
    L_0040df86:
        jne short L_0040df8d
    L_0040df88:
        fstp dword ptr [ebp+30h]
    L_0040df8b:
        jmp short L_0040dfaa
    L_0040df8d:
        fstp st(0)
    L_0040df8f:
        fld dword ptr [esp+2Ch]
    L_0040df93:
        fadd dword ptr [ebp+13B0h]
    L_0040df99:
        fcom dword ptr [ebp+30h]
    L_0040df9c:
        fnstsw ax
    L_0040df9e:
        test ah,5
    L_0040dfa1:
        jp short L_0040dfa8
    L_0040dfa3:
        fstp dword ptr [ebp+30h]
    L_0040dfa6:
        jmp short L_0040dfaa
    L_0040dfa8:
        fstp st(0)
    L_0040dfaa:
        fld dword ptr [esi]
    L_0040dfac:
        fsub dword ptr [ebx]
    L_0040dfae:
        fstp dword ptr [esp+10h]
    L_0040dfb2:
        mov edx,dword ptr [esp+10h]
    L_0040dfb6:
        fld dword ptr [esi+4]
    L_0040dfb9:
        fsub dword ptr [ebx+4]
    L_0040dfbc:
        fstp dword ptr [esp+14h]
    L_0040dfc0:
        mov eax,dword ptr [esp+14h]
    L_0040dfc4:
        fld dword ptr [esi+8]
    L_0040dfc7:
        fsub dword ptr [ebx+8]
    L_0040dfca:
        mov dword ptr [edi],edx
    L_0040dfcc:
        mov dword ptr [edi+4],eax
    L_0040dfcf:
        fstp dword ptr [esp+18h]
    L_0040dfd3:
        mov edx,dword ptr [esp+18h]
    L_0040dfd7:
        mov dword ptr [edi+8],edx
    L_0040dfda:
        fld dword ptr [ebp+13A4h]
    L_0040dfe0:
        fmul dword ptr [flt_0_5]
    L_0040dfe6:
        fld st(0)
    L_0040dfe8:
        fadd dword ptr [esi]
    L_0040dfea:
        fcomp dword ptr [flt_neg192]
    L_0040dff0:
        fnstsw ax
    L_0040dff2:
        test ah,5
    L_0040dff5:
        jnp asm_target_0040e09b
    L_0040dffb:
        fld dword ptr [esi]
    L_0040dffd:
        fsub st,st(1)
    L_0040dfff:
        fcomp dword ptr [flt_192]
    L_0040e005:
        fnstsw ax
    L_0040e007:
        fstp st(0)
    L_0040e009:
        test ah,41h
    L_0040e00c:
        je asm_target_0040e09d
    L_0040e012:
        fld dword ptr [ebp+13A8h]
    L_0040e018:
        fmul dword ptr [flt_0_5]
    L_0040e01e:
        fld st(0)
    L_0040e020:
        fadd dword ptr [ebp+30h]
    L_0040e023:
        fcomp dword ptr [flt_0]
    L_0040e029:
        fnstsw ax
    L_0040e02b:
        test ah,5
    L_0040e02e:
        jnp short L_0040e09b
    L_0040e030:
        fld dword ptr [ebp+30h]
    L_0040e033:
        fsub st,st(1)
    L_0040e035:
        fcomp dword ptr [flt_448]
    L_0040e03b:
        fnstsw ax
    L_0040e03d:
        fstp st(0)
    L_0040e03f:
        test ah,41h
    L_0040e042:
        je short L_0040e09d
    L_0040e044:
        or ecx,100h
    L_0040e04a:
        mov dword ptr [ebp+1444h],ecx
    L_0040e050:
        mov ecx,dword ptr [ebp+1444h]
    L_0040e056:
        test ecx,100000h
    L_0040e05c:
        je asm_target_0040e0e9
    L_0040e062:
        mov eax,dword ptr [g_bomb]
    L_0040e067:
        mov eax,dword ptr [eax+28h]
    L_0040e06a:
        test eax,eax
    L_0040e06c:
        je short L_0040e0b8
    L_0040e06e:
        test ecx,200000h
    L_0040e074:
        jne short L_0040e0b4
    L_0040e076:
        mov eax,dword ptr [ebp+1448h]
    L_0040e07c:
        mov dword ptr [ebp+0F4h],eax
    L_0040e082:
        push eax
    L_0040e083:
        lea eax,[ebp+0C0h]
    L_0040e089:
        call asm_FUN_004496d0_004496d0
    L_0040e08e:
        mov eax,dword ptr [ebp+1444h]
    L_0040e094:
        or eax,200001h
    L_0040e099:
        jmp short L_0040e0e3
    L_0040e09b:
        fstp st(0)
    L_0040e09d:
        test ch,1
    L_0040e0a0:
        je short L_0040e050
    L_0040e0a2:
        test cl,4
    L_0040e0a5:
        jne short L_0040e050
    L_0040e0a7:
        pop ebx
    L_0040e0a8:
        pop edi
    L_0040e0a9:
        pop esi
    L_0040e0aa:
        or eax,0FFFFFFFFh
    L_0040e0ad:
        pop ebp
    L_0040e0ae:
        add esp,18h
    L_0040e0b1:
        ret 4
    L_0040e0b4:
        test eax,eax
    L_0040e0b6:
        jne short L_0040e0e9
    L_0040e0b8:
        test ecx,200000h
    L_0040e0be:
        je short L_0040e0e9
    L_0040e0c0:
        mov eax,dword ptr [ebp+144Ch]
    L_0040e0c6:
        mov dword ptr [ebp+0F4h],eax
    L_0040e0cc:
        push eax
    L_0040e0cd:
        lea eax,[ebp+0C0h]
    L_0040e0d3:
        call asm_FUN_004496d0_004496d0
    L_0040e0d8:
        mov eax,dword ptr [ebp+1444h]
    L_0040e0de:
        and eax,0FFDFFFFEh
    L_0040e0e3:
        mov dword ptr [ebp+1444h],eax
    L_0040e0e9:
        mov ecx,dword ptr [ebp+128h]
    L_0040e0ef:
        mov edx,dword ptr [ecx]
    L_0040e0f1:
        mov edi,dword ptr [ebp+14D8h]
    L_0040e0f7:
        mov eax,edx
    L_0040e0f9:
        push eax
    L_0040e0fa:
        mov dword ptr [esp+30h],edx
    L_0040e0fe:
        call asm_EclVm_TickChildren_0044fd10
    L_0040e103:
        test eax,eax
    L_0040e105:
        jne short L_0040e0a7
    L_0040e107:
        mov edx,dword ptr [ebp+1444h]
    L_0040e10d:
        and edx,0FFFFDFFFh
    L_0040e113:
        mov eax,edx
    L_0040e115:
        test al,11h
    L_0040e117:
        mov dword ptr [ebp+1444h],edx
    L_0040e11d:
        mov ebx,8
    L_0040e122:
        jne asm_target_0040e275
    L_0040e128:
        mov edx,dword ptr [g_player]
    L_0040e12e:
        lea ecx,[ebp+0B0h]
    L_0040e134:
        push ecx
    L_0040e135:
        lea eax,[ebp+2Ch]
    L_0040e138:
        push eax
    L_0040e139:
        push edx
    L_0040e13a:
        xor ecx,ecx
    L_0040e13c:
        call asm_FUN_00428630_00428630
    L_0040e141:
        mov ecx,eax
    L_0040e143:
        mov eax,dword ptr [g_player]
    L_0040e148:
        mov eax,dword ptr [eax+458h]
    L_0040e14e:
        cmp eax,2
    L_0040e151:
        je short L_0040e157
    L_0040e153:
        test eax,eax
    L_0040e155:
        jne short L_0040e167
    L_0040e157:
        mov eax,66666667h
    L_0040e15c:
        imul ecx
    L_0040e15e:
        sar edx,1
    L_0040e160:
        mov ecx,edx
    L_0040e162:
        shr ecx,1Fh
    L_0040e165:
        add ecx,edx
    L_0040e167:
        test ecx,ecx
    L_0040e169:
        je asm_target_0040e26b
    L_0040e16f:
        mov edx,dword ptr [g_card]
    L_0040e175:
        test byte ptr [edx+378Ch],1
    L_0040e17c:
        je short L_0040e1a3
    L_0040e17e:
        mov eax,dword ptr [ebp+1444h]
    L_0040e184:
        test ah,ah
    L_0040e186:
        jns short L_0040e1a3
    L_0040e188:
        mov eax,66666667h
    L_0040e18d:
        imul ecx
    L_0040e18f:
        sar edx,1
    L_0040e191:
        mov eax,edx
    L_0040e193:
        shr eax,1Fh
    L_0040e196:
        add eax,edx
    L_0040e198:
        mov ecx,eax
    L_0040e19a:
        test ecx,ecx
    L_0040e19c:
        jg short L_0040e1a3
    L_0040e19e:
        mov ecx,1
    L_0040e1a3:
        test byte ptr [ebp+1444h],8
    L_0040e1aa:
        jne short L_0040e1bc
    L_0040e1ac:
        mov eax,dword ptr [ebp+1420h]
    L_0040e1b2:
        test eax,eax
    L_0040e1b4:
        jg short L_0040e1bc
    L_0040e1b6:
        sub dword ptr [ebp+13C0h],ecx
    L_0040e1bc:
        mov ecx,dword ptr [ebp+14D8h]
    L_0040e1c2:
        call asm_FUN_004127a0_004127a0
    L_0040e1c7:
        mov esi,eax
    L_0040e1c9:
        test esi,esi
    L_0040e1cb:
        je short L_0040e212
    L_0040e1cd:
        mov eax,dword ptr [ebp+14D8h]
    L_0040e1d3:
        call asm_BulletEntity_ClearResourceList_0040c6e0
    L_0040e1d8:
        mov eax,dword ptr [ebp+14D8h]
    L_0040e1de:
        call asm_FUN_0040c730_0040c730
    L_0040e1e3:
        mov ecx,esi
    L_0040e1e5:
        mov esi,dword ptr [ebp+14D8h]
    L_0040e1eb:
        call asm_FUN_00450700_00450700
    L_0040e1f0:
        mov ecx,dword ptr [ebp+128h]
    L_0040e1f6:
        mov edx,dword ptr [ecx]
    L_0040e1f8:
        mov edi,dword ptr [ebp+14D8h]
    L_0040e1fe:
        mov eax,edx
    L_0040e200:
        push eax
    L_0040e201:
        mov dword ptr [esp+30h],edx
    L_0040e205:
        call asm_EclVm_TickChildren_0044fd10
    L_0040e20a:
        test eax,eax
    L_0040e20c:
        jne asm_target_0040e0a7
    L_0040e212:
        mov edx,dword ptr [ebp+13C0h]
    L_0040e218:
        xor ecx,ecx
    L_0040e21a:
        test edx,edx
    L_0040e21c:
        mov edx,dword ptr [ebp+1444h]
    L_0040e222:
        setle cl
    L_0040e225:
        shr edx,6
    L_0040e228:
        not edx
    L_0040e22a:
        and ecx,edx
    L_0040e22c:
        test cl,1
    L_0040e22f:
        je short L_0040e261
    L_0040e231:
        mov eax,dword ptr [ebp+13BCh]
    L_0040e237:
        push eax
    L_0040e238:
        mov ecx,474C40h
    L_0040e23d:
        call asm_AddScaled_GameScore_00409d90
    L_0040e242:
        mov ecx,dword ptr [ebp+14D8h]
    L_0040e248:
        push ecx
    L_0040e249:
        call asm_BossUi_ReleaseIndicatorsRetail_0040e5f0
    L_0040e24e:
        test eax,eax
    L_0040e250:
        je short L_0040e261
    L_0040e252:
        pop ebx
    L_0040e253:
        pop edi
    L_0040e254:
        pop esi
    L_0040e255:
        mov eax,1
    L_0040e25a:
        pop ebp
    L_0040e25b:
        add esp,18h
    L_0040e25e:
        ret 4
    L_0040e261:
        or dword ptr [ebp+1444h],2000h
    L_0040e26b:
        mov dword ptr [data_00474c50],1
    L_0040e275:
        mov ecx,dword ptr [ebp+14D8h]
    L_0040e27b:
        call asm_FUN_004127a0_004127a0
    L_0040e280:
        mov edi,eax
    L_0040e282:
        test edi,edi
    L_0040e284:
        je short L_0040e2bd
    L_0040e286:
        mov eax,dword ptr [ebp+14D8h]
    L_0040e28c:
        call asm_BulletEntity_ClearResourceList_0040c6e0
    L_0040e291:
        mov eax,dword ptr [ebp+14D8h]
    L_0040e297:
        call asm_FUN_0040c730_0040c730
    L_0040e29c:
        mov esi,dword ptr [ebp+14D8h]
    L_0040e2a2:
        mov eax,dword ptr [esi+102Ch]
    L_0040e2a8:
        push edi
    L_0040e2a9:
        call asm_FUN_00450470_00450470
    L_0040e2ae:
        mov edx,dword ptr [esi+4]
    L_0040e2b1:
        mov dword ptr [edx+4],eax
    L_0040e2b4:
        mov eax,dword ptr [esi+4]
    L_0040e2b7:
        mov dword ptr [eax],0
    L_0040e2bd:
        test byte ptr [ebp+1444h],12h
    L_0040e2c4:
        jne short L_0040e2e4
    L_0040e2c6:
        mov eax,dword ptr [ebp+1434h]
    L_0040e2cc:
        test eax,eax
    L_0040e2ce:
        jg short L_0040e2e4
    L_0040e2d0:
        mov edx,dword ptr [g_player]
    L_0040e2d6:
        lea eax,[ebp+0B8h]
    L_0040e2dc:
        lea ecx,[ebp+2Ch]
    L_0040e2df:
        call asm_FUN_004266b0_004266b0
    L_0040e2e4:
        mov eax,dword ptr [ebp+1444h]
    L_0040e2ea:
        test ah,10h
    L_0040e2ed:
        je asm_target_0040e379
    L_0040e2f3:
        fld dword ptr [ebp+38h]
    L_0040e2f6:
        xor ecx,ecx
    L_0040e2f8:
        fcomp dword ptr [data_00470d30]
    L_0040e2fe:
        fnstsw ax
    L_0040e300:
        test ah,5
    L_0040e303:
        jp short L_0040e30c
    L_0040e305:
        mov eax,0FFFFFFFFh
    L_0040e30a:
        jmp short L_0040e325
    L_0040e30c:
        fld dword ptr [ebp+38h]
    L_0040e30f:
        fcomp dword ptr [data_00470c18]
    L_0040e315:
        fnstsw ax
    L_0040e317:
        test ah,41h
    L_0040e31a:
        jne short L_0040e323
    L_0040e31c:
        mov eax,1
    L_0040e321:
        jmp short L_0040e325
    L_0040e323:
        xor eax,eax
    L_0040e325:
        mov edx,dword ptr [ebp+0F8h]
    L_0040e32b:
        cmp edx,eax
    L_0040e32d:
        je short L_0040e379
    L_0040e32f:
        cmp edx,0FFFFFFFFh
    L_0040e332:
        je short L_0040e356
    L_0040e334:
        test edx,edx
    L_0040e336:
        je short L_0040e34b
    L_0040e338:
        cmp edx,1
    L_0040e33b:
        jne short L_0040e35f
    L_0040e33d:
        mov ecx,eax
    L_0040e33f:
        neg ecx
    L_0040e341:
        sbb ecx,ecx
    L_0040e343:
        and ecx,0FFFFFFFDh
    L_0040e346:
        add ecx,4
    L_0040e349:
        jmp short L_0040e35f
    L_0040e34b:
        xor ecx,ecx
    L_0040e34d:
        cmp eax,0FFFFFFFFh
    L_0040e350:
        setne cl
    L_0040e353:
        inc ecx
    L_0040e354:
        jmp short L_0040e35f
    L_0040e356:
        mov ecx,eax
    L_0040e358:
        neg ecx
    L_0040e35a:
        sbb ecx,ecx
    L_0040e35c:
        add ecx,3
    L_0040e35f:
        mov edx,dword ptr [ebp+0F4h]
    L_0040e365:
        add edx,ecx
    L_0040e367:
        mov dword ptr [ebp+0F8h],eax
    L_0040e36d:
        push edx
    L_0040e36e:
        lea eax,[ebp+0C0h]
    L_0040e374:
        call asm_FUN_004496d0_004496d0
    L_0040e379:
        test dword ptr [ebp+1444h],40000h
    L_0040e383:
        lea edi,[ebp+0C0h]
    L_0040e389:
        jne short L_0040e3b2
    L_0040e38b:
        mov dword ptr [esp+2Ch],ebx
    L_0040e38f:
        mov ebx,dword ptr [g_sprt_ctrl]
    L_0040e395:
        mov eax,dword ptr [edi]
    L_0040e397:
        push eax
    L_0040e398:
        lea esi,[ebp+2Ch]
    L_0040e39b:
        mov edx,ebx
    L_0040e39d:
        call asm_AnimationManager_SetTranslatedPosition_00449350
    L_0040e3a2:
        mov eax,dword ptr [esp+2Ch]
    L_0040e3a6:
        add edi,4
    L_0040e3a9:
        dec eax
    L_0040e3aa:
        mov dword ptr [esp+2Ch],eax
    L_0040e3ae:
        jne short L_0040e395
    L_0040e3b0:
        jmp short L_0040e3db
    L_0040e3b2:
        mov dword ptr [esp+2Ch],ebx
    L_0040e3b6:
        mov ebx,dword ptr [g_sprt_ctrl]
    L_0040e3bc:
        TH10_NOP_LEA_ESP_DISP8()
    L_0040e3c0:
        mov ecx,dword ptr [edi]
    L_0040e3c2:
        push ecx
    L_0040e3c3:
        lea esi,[ebp+2Ch]
    L_0040e3c6:
        mov edx,ebx
    L_0040e3c8:
        call asm_AnimationManager_SetPosition_004492f0
    L_0040e3cd:
        mov eax,dword ptr [esp+2Ch]
    L_0040e3d1:
        add edi,4
    L_0040e3d4:
        dec eax
    L_0040e3d5:
        mov dword ptr [esp+2Ch],eax
    L_0040e3d9:
        jne short L_0040e3c0
    L_0040e3db:
        mov eax,dword ptr [ebp+1444h]
    L_0040e3e1:
        test al,11h
    L_0040e3e3:
        jne short L_0040e43e
    L_0040e3e5:
        test eax,0C0000h
    L_0040e3ea:
        jne short L_0040e43e
    L_0040e3ec:
        mov ecx,dword ptr [g_player]
    L_0040e3f2:
        mov eax,dword ptr [ecx+3504h]
    L_0040e3f8:
        test eax,eax
    L_0040e3fa:
        je short L_0040e421
    L_0040e3fc:
        fld dword ptr [eax+1068h]
    L_0040e402:
        fsub dword ptr [ecx+3C0h]
    L_0040e408:
        fabs
    L_0040e40a:
        fld dword ptr [esi]
    L_0040e40c:
        fsub dword ptr [ecx+3C0h]
    L_0040e412:
        fabs
    L_0040e414:
        fxch
    L_0040e416:
        fxch
    L_0040e418:
        fcompp
    L_0040e41a:
        fnstsw ax
    L_0040e41c:
        test ah,41h
    L_0040e41f:
        jne short L_0040e43e
    L_0040e421:
        mov al,byte ptr [ecx+3508h]
    L_0040e427:
        test al,al
    L_0040e429:
        jne short L_0040e437
    L_0040e42b:
        mov edx,dword ptr [ebp+14D8h]
    L_0040e431:
        mov dword ptr [ecx+3504h],edx
    L_0040e437:
        mov byte ptr [ecx+3508h],1
    L_0040e43e:
        mov eax,dword ptr [ebp+0C0h]
    L_0040e444:
        push eax
    L_0040e445:
        mov edx,ebx
    L_0040e447:
        call asm_AnimationManager_Find_004491c0
    L_0040e44c:
        test eax,eax
    L_0040e44e:
        jne short L_0040e456
    L_0040e450:
        mov dword ptr [ebp+0C0h],eax
    L_0040e456:
        mov ecx,dword ptr [ebp+1414h]
    L_0040e45c:
        test ecx,ecx
    L_0040e45e:
        jne asm_target_0040e510
    L_0040e464:
        mov ecx,dword ptr [ebp+1444h]
    L_0040e46a:
        test ch,20h
    L_0040e46d:
        je asm_target_0040e53e
    L_0040e473:
        mov edx,dword ptr [eax+35Ch]
    L_0040e479:
        mov ecx,8000h
    L_0040e47e:
        or edx,ecx
    L_0040e480:
        mov dword ptr [eax+300h],0FF0000FFh
    L_0040e48a:
        mov dword ptr [eax+35Ch],edx
    L_0040e490:
        test dword ptr [ebp+1444h],ecx
    L_0040e496:
        mov dword ptr [ebp+1414h],4
    L_0040e4a0:
        je short L_0040e4fb
    L_0040e4a2:
        mov ecx,dword ptr [g_card]
    L_0040e4a8:
        mov ecx,dword ptr [ecx+378Ch]
    L_0040e4ae:
        mov eax,ecx
    L_0040e4b0:
        and eax,1
    L_0040e4b3:
        je short L_0040e4ba
    L_0040e4b5:
        test cl,8
    L_0040e4b8:
        jne short L_0040e4fb
    L_0040e4ba:
        test eax,eax
    L_0040e4bc:
        je short L_0040e4d4
    L_0040e4be:
        mov edx,dword ptr [ebp+14D8h]
    L_0040e4c4:
        cmp dword ptr [edx+2404h],12Ch
    L_0040e4ce:
        jl short L_0040e4e6
    L_0040e4d0:
        test eax,eax
    L_0040e4d2:
        jne short L_0040e4fb
    L_0040e4d4:
        mov eax,dword ptr [ebp+14D8h]
    L_0040e4da:
        cmp dword ptr [eax+2404h],384h
    L_0040e4e4:
        jge short L_0040e4fb
    L_0040e4e6:
        mov ecx,dword ptr [ebp+2Ch]
    L_0040e4e9:
        push ecx
    L_0040e4ea:
        mov ebx,23h
    L_0040e4ef:
        mov esi,492590h
    L_0040e4f4:
        call asm_FUN_0043dd10_0043dd10
    L_0040e4f9:
        jmp short L_0040e53e
    L_0040e4fb:
        mov edx,dword ptr [ebp+2Ch]
    L_0040e4fe:
        push edx
    L_0040e4ff:
        mov ebx,13h
    L_0040e504:
        mov esi,492590h
    L_0040e509:
        call asm_FUN_0043dd10_0043dd10
    L_0040e50e:
        jmp short L_0040e53e
    L_0040e510:
        mov edx,dword ptr [eax+35Ch]
    L_0040e516:
        mov ecx,0FFFF7FFFh
    L_0040e51b:
        and edx,ecx
    L_0040e51d:
        mov dword ptr [eax+35Ch],edx
    L_0040e523:
        mov eax,dword ptr [ebp+1444h]
    L_0040e529:
        test ah,ah
    L_0040e52b:
        jns short L_0040e538
    L_0040e52d:
        mov eax,dword ptr [g_front]
    L_0040e532:
        and dword ptr [eax+9DA4h],ecx
    L_0040e538:
        dec dword ptr [ebp+1414h]
    L_0040e53e:
        mov eax,dword ptr [ebp+1420h]
    L_0040e544:
        test eax,eax
    L_0040e546:
        jle short L_0040e558
    L_0040e548:
        push 0BF800000h
    L_0040e54d:
        lea esi,[ebp+141Ch]
    L_0040e553:
        call asm_FrameTimer_Advance_0044bf40
    L_0040e558:
        mov eax,dword ptr [ebp+1434h]
    L_0040e55e:
        test eax,eax
    L_0040e560:
        jle short L_0040e572
    L_0040e562:
        push 0BF800000h
    L_0040e567:
        lea esi,[ebp+1430h]
    L_0040e56d:
        call asm_FrameTimer_Advance_0044bf40
    L_0040e572:
        mov edx,dword ptr [ebp+120h]
    L_0040e578:
        mov ecx,dword ptr [ebp+128h]
    L_0040e57e:
        mov dword ptr [ebp+11Ch],edx
    L_0040e584:
        fld dword ptr [ecx]
    L_0040e586:
        fcomp dword ptr [flt_0_99]
    L_0040e58c:
        fnstsw ax
    L_0040e58e:
        test ah,41h
    L_0040e591:
        jne short L_0040e5c7
    L_0040e593:
        fld dword ptr [ecx]
    L_0040e595:
        fcomp dword ptr [flt_1_01]
    L_0040e59b:
        fnstsw ax
    L_0040e59d:
        test ah,5
    L_0040e5a0:
        jp short L_0040e5c7
    L_0040e5a2:
        fld dword ptr [ebp+124h]
    L_0040e5a8:
        pop ebx
    L_0040e5a9:
        fadd dword ptr [flt_1]
    L_0040e5af:
        pop edi
    L_0040e5b0:
        inc edx
    L_0040e5b1:
        pop esi
    L_0040e5b2:
        fstp dword ptr [ebp+124h]
    L_0040e5b8:
        mov dword ptr [ebp+120h],edx
    L_0040e5be:
        xor eax,eax
    L_0040e5c0:
        pop ebp
    L_0040e5c1:
        add esp,18h
    L_0040e5c4:
        ret 4
    L_0040e5c7:
        fld dword ptr [ecx]
    L_0040e5c9:
        fadd dword ptr [ebp+124h]
    L_0040e5cf:
        fst dword ptr [ebp+124h]
    L_0040e5d5:
        call asm_FUN_00463b2c_00463b2c
    L_0040e5da:
        pop ebx
    L_0040e5db:
        pop edi
    L_0040e5dc:
        mov dword ptr [ebp+120h],eax
    L_0040e5e2:
        pop esi
    L_0040e5e3:
        xor eax,eax
    L_0040e5e5:
        pop ebp
    L_0040e5e6:
        add esp,18h
    L_0040e5e9:
        ret 4
    }
}
#include "th10/source_views/bullet_99a1d5_2.hpp"
#include "../../../../src/game/enemy/bullet_spawn_parameters_initialize.cpp"
#include "../../../../src/game/effect/entity_attach_resource_snapshot.cpp"

