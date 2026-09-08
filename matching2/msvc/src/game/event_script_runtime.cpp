#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00403C80..0x0040438D: FUN_00403c80
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00403c80_00403c80() {
    __asm {
    L_00403c80:
        sub esp,8Ch
    L_00403c86:
        push ebx
    L_00403c87:
        push ebp
    L_00403c88:
        mov ebp,dword ptr [esp+98h]
    L_00403c8f:
        mov eax,dword ptr [ebp+4Ch]
    L_00403c92:
        mov ecx,dword ptr [eax]
    L_00403c94:
        cmp ecx,dword ptr [ebp+3Ch]
    L_00403c97:
        push esi
    L_00403c98:
        push edi
    L_00403c99:
        jg asm_target_0040426b
    L_00403c9f:
        mov ebx,0FFF0BDC1h
    L_00403ca4:
        mov edi,dword ptr [ebp+4Ch]
    L_00403ca7:
        movsx eax,word ptr [edi+4]
    L_00403cab:
        cmp eax,0Eh
    L_00403cae:
        ja asm_target_00404251
    L_00403cb4:
        jmp dword ptr [eax*4+404390h]
    L_00403cbb:
        mov eax,dword ptr [ebp+48h]
    L_00403cbe:
        test al,1
    L_00403cc0:
        mov edi,dword ptr [edi+0Ch]
    L_00403cc3:
        mov dword ptr [esp+10h],edi
    L_00403cc7:
        jne short L_00403ce1
    L_00403cc9:
        xor ecx,ecx
    L_00403ccb:
        or eax,1
    L_00403cce:
        mov dword ptr [ebp+3Ch],ecx
    L_00403cd1:
        mov dword ptr [ebp+38h],ebx
    L_00403cd4:
        mov dword ptr [ebp+40h],ecx
    L_00403cd7:
        mov dword ptr [ebp+44h],476F78h
    L_00403cde:
        mov dword ptr [ebp+48h],eax
    L_00403ce1:
        fild dword ptr [esp+10h]
    L_00403ce5:
        mov dword ptr [ebp+3Ch],edi
    L_00403ce8:
        dec edi
    L_00403ce9:
        mov dword ptr [ebp+38h],edi
    L_00403cec:
        fstp dword ptr [ebp+40h]
    L_00403cef:
        mov edx,dword ptr [ebp+4Ch]
    L_00403cf2:
        mov ecx,dword ptr [edx+8]
    L_00403cf5:
        mov eax,dword ptr [ebp+1Ch]
    L_00403cf8:
        add eax,ecx
    L_00403cfa:
        mov dword ptr [ebp+4Ch],eax
    L_00403cfd:
        jmp asm_target_0040425d
    L_00403d02:
        lea ecx,[ebp+2A4Ch]
    L_00403d08:
        lea eax,[ebp+2B3Ch]
    L_00403d0e:
        mov edx,ecx
    L_00403d10:
        mov ebx,dword ptr [edx]
    L_00403d12:
        mov esi,eax
    L_00403d14:
        mov dword ptr [esi],ebx
    L_00403d16:
        mov ebx,dword ptr [edx+4]
    L_00403d19:
        mov edx,dword ptr [edx+8]
    L_00403d1c:
        mov dword ptr [esi+4],ebx
    L_00403d1f:
        mov dword ptr [esi+8],edx
    L_00403d22:
        mov edx,dword ptr [edi+8]
    L_00403d25:
        mov dword ptr [ecx],edx
    L_00403d27:
        mov edx,dword ptr [edi+0Ch]
    L_00403d2a:
        mov dword ptr [ebp+2A50h],edx
    L_00403d30:
        mov edx,dword ptr [edi+10h]
    L_00403d33:
        mov dword ptr [ebp+2A54h],edx
    L_00403d39:
        fld dword ptr [ecx]
    L_00403d3b:
        fsub dword ptr [eax]
    L_00403d3d:
        mov ebx,0FFF0BDC1h
    L_00403d42:
        fstp dword ptr [esp+74h]
    L_00403d46:
        fld dword ptr [ecx+4]
    L_00403d49:
        fsub dword ptr [eax+4]
    L_00403d4c:
        fstp dword ptr [esp+78h]
    L_00403d50:
        mov edx,dword ptr [esp+78h]
    L_00403d54:
        fld dword ptr [ecx+8]
    L_00403d57:
        mov ecx,dword ptr [esp+74h]
    L_00403d5b:
        fsub dword ptr [eax+8]
    L_00403d5e:
        mov dword ptr [eax],ecx
    L_00403d60:
        mov dword ptr [eax+4],edx
    L_00403d63:
        fstp dword ptr [esp+7Ch]
    L_00403d67:
        mov ecx,dword ptr [esp+7Ch]
    L_00403d6b:
        mov dword ptr [eax+8],ecx
    L_00403d6e:
        jmp asm_target_00404251
    L_00403d73:
        mov edx,dword ptr [edi+10h]
    L_00403d76:
        mov eax,dword ptr [edi+14h]
    L_00403d79:
        mov ecx,dword ptr [edi+18h]
    L_00403d7c:
        mov dword ptr [esp+68h],edx
    L_00403d80:
        mov edx,dword ptr [edi+8]
    L_00403d83:
        mov dword ptr [ebp+0E0h],edx
    L_00403d89:
        mov dword ptr [esp+6Ch],eax
    L_00403d8d:
        mov eax,dword ptr [edi+0Ch]
    L_00403d90:
        mov dword ptr [esp+70h],ecx
    L_00403d94:
        mov dword ptr [ebp+0E4h],eax
    L_00403d9a:
        lea ecx,[ebp+2A4Ch]
    L_00403da0:
        mov eax,dword ptr [ecx]
    L_00403da2:
        lea edx,[ebp+9Ch]
    L_00403da8:
        mov dword ptr [edx],eax
    L_00403daa:
        mov eax,dword ptr [ecx+4]
    L_00403dad:
        mov ecx,dword ptr [ecx+8]
    L_00403db0:
        mov dword ptr [edx+4],eax
    L_00403db3:
        mov eax,dword ptr [esp+68h]
    L_00403db7:
        mov dword ptr [edx+8],ecx
    L_00403dba:
        mov ecx,dword ptr [esp+6Ch]
    L_00403dbe:
        lea edx,[ebp+0A8h]
    L_00403dc4:
        mov dword ptr [edx],eax
    L_00403dc6:
        mov eax,dword ptr [esp+70h]
    L_00403dca:
        mov dword ptr [edx+4],ecx
    L_00403dcd:
        mov dword ptr [edx+8],eax
    L_00403dd0:
        jmp asm_target_00404086
    L_00403dd5:
        mov ecx,dword ptr [edi+8]
    L_00403dd8:
        mov dword ptr [ebp+2A58h],ecx
    L_00403dde:
        mov edx,dword ptr [edi+0Ch]
    L_00403de1:
        mov dword ptr [ebp+2A5Ch],edx
    L_00403de7:
        mov eax,dword ptr [edi+10h]
    L_00403dea:
        mov dword ptr [ebp+2A60h],eax
    L_00403df0:
        jmp asm_target_00404251
    L_00403df5:
        mov ecx,dword ptr [edi+10h]
    L_00403df8:
        mov edx,dword ptr [edi+14h]
    L_00403dfb:
        mov eax,dword ptr [edi+18h]
    L_00403dfe:
        mov dword ptr [esp+5Ch],ecx
    L_00403e02:
        mov ecx,dword ptr [edi+8]
    L_00403e05:
        mov dword ptr [ebp+94h],ecx
    L_00403e0b:
        mov dword ptr [esp+60h],edx
    L_00403e0f:
        mov edx,dword ptr [edi+0Ch]
    L_00403e12:
        mov dword ptr [esp+64h],eax
    L_00403e16:
        mov dword ptr [ebp+98h],edx
    L_00403e1c:
        lea eax,[ebp+2A58h]
    L_00403e22:
        mov edx,dword ptr [eax]
    L_00403e24:
        lea ecx,[ebp+50h]
    L_00403e27:
        mov dword ptr [ecx],edx
    L_00403e29:
        mov edx,dword ptr [eax+4]
    L_00403e2c:
        mov eax,dword ptr [eax+8]
    L_00403e2f:
        mov dword ptr [ecx+4],edx
    L_00403e32:
        mov edx,dword ptr [esp+5Ch]
    L_00403e36:
        mov dword ptr [ecx+8],eax
    L_00403e39:
        mov eax,dword ptr [esp+60h]
    L_00403e3d:
        lea ecx,[ebp+5Ch]
    L_00403e40:
        mov dword ptr [ecx],edx
    L_00403e42:
        mov edx,dword ptr [esp+64h]
    L_00403e46:
        mov dword ptr [ecx+4],eax
    L_00403e49:
        mov dword ptr [ecx+8],edx
    L_00403e4c:
        jmp asm_target_00404182
    L_00403e51:
        mov eax,dword ptr [edi+8]
    L_00403e54:
        mov dword ptr [ebp+2A64h],eax
    L_00403e5a:
        mov ecx,dword ptr [edi+0Ch]
    L_00403e5d:
        mov dword ptr [ebp+2A68h],ecx
    L_00403e63:
        mov edx,dword ptr [edi+10h]
    L_00403e66:
        mov dword ptr [ebp+2A6Ch],edx
    L_00403e6c:
        jmp asm_target_00404251
    L_00403e71:
        mov eax,dword ptr [edi+8]
    L_00403e74:
        mov dword ptr [ebp+2A94h],eax
    L_00403e7a:
        jmp asm_target_00404251
    L_00403e7f:
        mov ecx,dword ptr [edi+8]
    L_00403e82:
        movzx edx,cl
    L_00403e85:
        mov dword ptr [ebp+2B60h],ecx
    L_00403e8b:
        movzx eax,byte ptr [ebp+2B61h]
    L_00403e92:
        movzx ecx,byte ptr [ebp+2B62h]
    L_00403e99:
        mov dword ptr [esp+10h],edx
    L_00403e9d:
        movzx edx,byte ptr [ebp+2B63h]
    L_00403ea4:
        fild dword ptr [esp+10h]
    L_00403ea8:
        mov dword ptr [esp+10h],eax
    L_00403eac:
        fstp dword ptr [ebp+2B50h]
    L_00403eb2:
        fild dword ptr [esp+10h]
    L_00403eb6:
        mov dword ptr [esp+10h],ecx
    L_00403eba:
        fstp dword ptr [ebp+2B54h]
    L_00403ec0:
        fild dword ptr [esp+10h]
    L_00403ec4:
        mov dword ptr [esp+10h],edx
    L_00403ec8:
        fstp dword ptr [ebp+2B58h]
    L_00403ece:
        fild dword ptr [esp+10h]
    L_00403ed2:
        fstp dword ptr [ebp+2B5Ch]
    L_00403ed8:
        mov eax,dword ptr [edi+0Ch]
    L_00403edb:
        mov dword ptr [ebp+2B48h],eax
    L_00403ee1:
        mov ecx,dword ptr [edi+10h]
    L_00403ee4:
        mov dword ptr [ebp+2B4Ch],ecx
    L_00403eea:
        jmp asm_target_00404251
    L_00403eef:
        movzx edx,byte ptr [edi+13h]
    L_00403ef3:
        movzx eax,byte ptr [edi+12h]
    L_00403ef7:
        movzx ecx,byte ptr [edi+11h]
    L_00403efb:
        mov dword ptr [esp+10h],edx
    L_00403eff:
        movzx edx,byte ptr [edi+10h]
    L_00403f03:
        fild dword ptr [esp+10h]
    L_00403f07:
        sub esp,10h
    L_00403f0a:
        mov dword ptr [esp+20h],eax
    L_00403f0e:
        mov eax,dword ptr [edi+18h]
    L_00403f11:
        fstp dword ptr [esp+0Ch]
    L_00403f15:
        lea esi,[esp+90h]
    L_00403f1c:
        fild dword ptr [esp+20h]
    L_00403f20:
        mov dword ptr [esp+20h],ecx
    L_00403f24:
        mov ecx,dword ptr [edi+14h]
    L_00403f27:
        fstp dword ptr [esp+8]
    L_00403f2b:
        fild dword ptr [esp+20h]
    L_00403f2f:
        mov dword ptr [esp+20h],edx
    L_00403f33:
        fstp dword ptr [esp+4]
    L_00403f37:
        fild dword ptr [esp+20h]
    L_00403f3b:
        fstp dword ptr [esp]
    L_00403f3e:
        push eax
    L_00403f3f:
        push ecx
    L_00403f40:
        call asm_Recovery_InitializeWordColor_00405040
    L_00403f45:
        mov edx,dword ptr [edi+8]
    L_00403f48:
        mov dword ptr [ebp+16Ch],edx
    L_00403f4e:
        mov eax,dword ptr [edi+0Ch]
    L_00403f51:
        lea esi,[ebp+2B48h]
    L_00403f57:
        lea edi,[ebp+0E8h]
    L_00403f5d:
        mov ecx,7
    L_00403f62:
        rep movsd
    L_00403f64:
        lea edi,[ebp+104h]
    L_00403f6a:
        mov ecx,7
    L_00403f6f:
        lea esi,[esp+80h]
    L_00403f76:
        rep movsd
    L_00403f78:
        mov dword ptr [ebp+170h],eax
    L_00403f7e:
        mov eax,dword ptr [ebp+168h]
    L_00403f84:
        xor ecx,ecx
    L_00403f86:
        test al,1
    L_00403f88:
        jne short L_00403faf
    L_00403f8a:
        or eax,1
    L_00403f8d:
        mov dword ptr [ebp+15Ch],ecx
    L_00403f93:
        mov dword ptr [ebp+158h],ebx
    L_00403f99:
        mov dword ptr [ebp+160h],ecx
    L_00403f9f:
        mov dword ptr [ebp+164h],476F78h
    L_00403fa9:
        mov dword ptr [ebp+168h],eax
    L_00403faf:
        mov dword ptr [ebp+15Ch],ecx
    L_00403fb5:
        mov dword ptr [ebp+160h],ecx
    L_00403fbb:
        mov dword ptr [ebp+158h],0FFFFFFFFh
    L_00403fc5:
        jmp asm_target_00404251
    L_00403fca:
        mov ecx,dword ptr [edi+10h]
    L_00403fcd:
        mov edx,dword ptr [edi+14h]
    L_00403fd0:
        mov eax,dword ptr [edi+18h]
    L_00403fd3:
        mov dword ptr [esp+44h],ecx
    L_00403fd7:
        mov ecx,dword ptr [edi+1Ch]
    L_00403fda:
        mov dword ptr [esp+48h],edx
    L_00403fde:
        mov edx,dword ptr [edi+20h]
    L_00403fe1:
        mov dword ptr [esp+4Ch],eax
    L_00403fe5:
        mov eax,dword ptr [edi+24h]
    L_00403fe8:
        mov dword ptr [esp+20h],ecx
    L_00403fec:
        mov ecx,dword ptr [edi+28h]
    L_00403fef:
        mov dword ptr [esp+24h],edx
    L_00403ff3:
        mov edx,dword ptr [edi+2Ch]
    L_00403ff6:
        mov dword ptr [esp+28h],eax
    L_00403ffa:
        mov eax,dword ptr [edi+30h]
    L_00403ffd:
        mov dword ptr [esp+2Ch],ecx
    L_00404001:
        mov ecx,dword ptr [edi+8]
    L_00404004:
        mov dword ptr [esp+30h],edx
    L_00404008:
        mov dword ptr [esp+34h],eax
    L_0040400c:
        mov dword ptr [ebp+0E0h],ecx
    L_00404012:
        lea edx,[ebp+2A4Ch]
    L_00404018:
        mov ecx,dword ptr [edx]
    L_0040401a:
        lea eax,[ebp+9Ch]
    L_00404020:
        mov dword ptr [eax],ecx
    L_00404022:
        mov ecx,dword ptr [edx+4]
    L_00404025:
        mov edx,dword ptr [edx+8]
    L_00404028:
        mov dword ptr [eax+4],ecx
    L_0040402b:
        mov ecx,dword ptr [esp+44h]
    L_0040402f:
        mov dword ptr [eax+8],edx
    L_00404032:
        mov edx,dword ptr [esp+48h]
    L_00404036:
        lea eax,[ebp+0B4h]
    L_0040403c:
        mov dword ptr [eax],ecx
    L_0040403e:
        mov ecx,dword ptr [esp+4Ch]
    L_00404042:
        mov dword ptr [eax+4],edx
    L_00404045:
        mov dword ptr [eax+8],ecx
    L_00404048:
        mov eax,dword ptr [esp+20h]
    L_0040404c:
        mov ecx,dword ptr [esp+24h]
    L_00404050:
        lea edx,[ebp+0A8h]
    L_00404056:
        mov dword ptr [edx],eax
    L_00404058:
        mov eax,dword ptr [esp+28h]
    L_0040405c:
        mov dword ptr [edx+4],ecx
    L_0040405f:
        mov dword ptr [edx+8],eax
    L_00404062:
        mov edx,dword ptr [esp+2Ch]
    L_00404066:
        mov eax,dword ptr [esp+30h]
    L_0040406a:
        lea ecx,[ebp+0C0h]
    L_00404070:
        mov dword ptr [ecx],edx
    L_00404072:
        mov edx,dword ptr [esp+34h]
    L_00404076:
        mov dword ptr [ecx+4],eax
    L_00404079:
        mov dword ptr [ebp+0E4h],8
    L_00404083:
        mov dword ptr [ecx+8],edx
    L_00404086:
        mov eax,dword ptr [ebp+0DCh]
    L_0040408c:
        xor ecx,ecx
    L_0040408e:
        test al,1
    L_00404090:
        jne short L_004040b7
    L_00404092:
        mov dword ptr [ebp+0D0h],ecx
    L_00404098:
        mov dword ptr [ebp+0CCh],ebx
    L_0040409e:
        mov dword ptr [ebp+0D4h],ecx
    L_004040a4:
        or eax,1
    L_004040a7:
        mov dword ptr [ebp+0D8h],476F78h
    L_004040b1:
        mov dword ptr [ebp+0DCh],eax
    L_004040b7:
        mov dword ptr [ebp+0D0h],ecx
    L_004040bd:
        mov dword ptr [ebp+0D4h],ecx
    L_004040c3:
        mov dword ptr [ebp+0CCh],0FFFFFFFFh
    L_004040cd:
        jmp asm_target_00404251
    L_004040d2:
        mov eax,dword ptr [edi+10h]
    L_004040d5:
        mov ecx,dword ptr [edi+14h]
    L_004040d8:
        mov edx,dword ptr [edi+18h]
    L_004040db:
        mov dword ptr [esp+38h],eax
    L_004040df:
        mov eax,dword ptr [edi+1Ch]
    L_004040e2:
        mov dword ptr [esp+3Ch],ecx
    L_004040e6:
        mov ecx,dword ptr [edi+20h]
    L_004040e9:
        mov dword ptr [esp+40h],edx
    L_004040ed:
        mov edx,dword ptr [edi+24h]
    L_004040f0:
        mov dword ptr [esp+50h],eax
    L_004040f4:
        mov eax,dword ptr [edi+28h]
    L_004040f7:
        mov dword ptr [esp+54h],ecx
    L_004040fb:
        mov ecx,dword ptr [edi+2Ch]
    L_004040fe:
        mov dword ptr [esp+58h],edx
    L_00404102:
        mov edx,dword ptr [edi+30h]
    L_00404105:
        mov dword ptr [esp+14h],eax
    L_00404109:
        mov eax,dword ptr [edi+8]
    L_0040410c:
        mov dword ptr [esp+18h],ecx
    L_00404110:
        mov dword ptr [esp+1Ch],edx
    L_00404114:
        mov dword ptr [ebp+94h],eax
    L_0040411a:
        lea ecx,[ebp+2A58h]
    L_00404120:
        mov eax,dword ptr [ecx]
    L_00404122:
        lea edx,[ebp+50h]
    L_00404125:
        mov dword ptr [edx],eax
    L_00404127:
        mov eax,dword ptr [ecx+4]
    L_0040412a:
        mov ecx,dword ptr [ecx+8]
    L_0040412d:
        mov dword ptr [edx+4],eax
    L_00404130:
        mov eax,dword ptr [esp+38h]
    L_00404134:
        mov dword ptr [edx+8],ecx
    L_00404137:
        mov ecx,dword ptr [esp+3Ch]
    L_0040413b:
        lea edx,[ebp+68h]
    L_0040413e:
        mov dword ptr [edx],eax
    L_00404140:
        mov eax,dword ptr [esp+40h]
    L_00404144:
        mov dword ptr [edx+4],ecx
    L_00404147:
        mov dword ptr [edx+8],eax
    L_0040414a:
        mov edx,dword ptr [esp+50h]
    L_0040414e:
        mov eax,dword ptr [esp+54h]
    L_00404152:
        lea ecx,[ebp+5Ch]
    L_00404155:
        mov dword ptr [ecx],edx
    L_00404157:
        mov edx,dword ptr [esp+58h]
    L_0040415b:
        mov dword ptr [ecx+4],eax
    L_0040415e:
        mov dword ptr [ecx+8],edx
    L_00404161:
        mov ecx,dword ptr [esp+14h]
    L_00404165:
        mov edx,dword ptr [esp+18h]
    L_00404169:
        lea eax,[ebp+74h]
    L_0040416c:
        mov dword ptr [eax],ecx
    L_0040416e:
        mov ecx,dword ptr [esp+1Ch]
    L_00404172:
        mov dword ptr [eax+4],edx
    L_00404175:
        mov dword ptr [ebp+98h],8
    L_0040417f:
        mov dword ptr [eax+8],ecx
    L_00404182:
        mov eax,dword ptr [ebp+90h]
    L_00404188:
        xor ecx,ecx
    L_0040418a:
        test al,1
    L_0040418c:
        jne short L_004041b3
    L_0040418e:
        mov dword ptr [ebp+84h],ecx
    L_00404194:
        mov dword ptr [ebp+80h],ebx
    L_0040419a:
        mov dword ptr [ebp+88h],ecx
    L_004041a0:
        or eax,1
    L_004041a3:
        mov dword ptr [ebp+8Ch],476F78h
    L_004041ad:
        mov dword ptr [ebp+90h],eax
    L_004041b3:
        mov dword ptr [ebp+84h],ecx
    L_004041b9:
        mov dword ptr [ebp+88h],ecx
    L_004041bf:
        mov dword ptr [ebp+80h],0FFFFFFFFh
    L_004041c9:
        jmp asm_target_00404251
    L_004041ce:
        mov dl,byte ptr [edi+8]
    L_004041d1:
        mov byte ptr [ebp+20h],dl
    L_004041d4:
        mov eax,dword ptr [ebp+34h]
    L_004041d7:
        xor ecx,ecx
    L_004041d9:
        test al,1
    L_004041db:
        jne short L_004041f3
    L_004041dd:
        or eax,1
    L_004041e0:
        mov dword ptr [ebp+28h],ecx
    L_004041e3:
        mov dword ptr [ebp+24h],ebx
    L_004041e6:
        mov dword ptr [ebp+2Ch],ecx
    L_004041e9:
        mov dword ptr [ebp+30h],476F78h
    L_004041f0:
        mov dword ptr [ebp+34h],eax
    L_004041f3:
        mov dword ptr [ebp+28h],ecx
    L_004041f6:
        mov dword ptr [ebp+2Ch],ecx
    L_004041f9:
        mov dword ptr [ebp+24h],0FFFFFFFFh
    L_00404200:
        jmp short L_00404251
    L_00404202:
        mov eax,dword ptr [edi+8]
    L_00404205:
        mov dword ptr [data_004923a8],eax
    L_0040420a:
        jmp short L_00404251
    L_0040420c:
        mov eax,dword ptr [edi+0Ch]
    L_0040420f:
        test eax,eax
    L_00404211:
        jl short L_00404231
    L_00404213:
        mov ecx,dword ptr [edi+8]
    L_00404216:
        mov edx,dword ptr [ebp+178h]
    L_0040421c:
        imul ecx,3ACh
    L_00404222:
        lea esi,[ecx+ebp+180h]
    L_00404229:
        push edx
    L_0040422a:
        call asm_FUN_00404f30_00404f30
    L_0040422f:
        jmp short L_00404251
    L_00404231:
        mov eax,dword ptr [edi+8]
    L_00404234:
        imul eax,3ACh
    L_0040423a:
        mov ecx,dword ptr [eax+ebp+4DCh]
    L_00404241:
        lea eax,[eax+ebp+180h]
    L_00404248:
        and ecx,0FFFFFFFEh
    L_0040424b:
        mov dword ptr [eax+35Ch],ecx
    L_00404251:
        mov eax,dword ptr [ebp+4Ch]
    L_00404254:
        movsx ecx,word ptr [eax+6]
    L_00404258:
        add ecx,eax
    L_0040425a:
        mov dword ptr [ebp+4Ch],ecx
    L_0040425d:
        mov edx,dword ptr [ebp+4Ch]
    L_00404260:
        mov eax,dword ptr [edx]
    L_00404262:
        cmp eax,dword ptr [ebp+3Ch]
    L_00404265:
        jle asm_target_00403ca4
    L_0040426b:
        mov edx,dword ptr [ebp+3Ch]
    L_0040426e:
        mov ecx,dword ptr [ebp+44h]
    L_00404271:
        mov dword ptr [ebp+38h],edx
    L_00404274:
        fld dword ptr [ecx]
    L_00404276:
        fcomp dword ptr [data_00470b68]
    L_0040427c:
        fnstsw ax
    L_0040427e:
        test ah,41h
    L_00404281:
        jne short L_004042a4
    L_00404283:
        fld dword ptr [ecx]
    L_00404285:
        fcomp dword ptr [data_00470b64]
    L_0040428b:
        fnstsw ax
    L_0040428d:
        test ah,5
    L_00404290:
        jp short L_004042a4
    L_00404292:
        fld dword ptr [ebp+40h]
    L_00404295:
        inc edx
    L_00404296:
        fadd dword ptr [data_00470afc]
    L_0040429c:
        mov dword ptr [ebp+3Ch],edx
    L_0040429f:
        fstp dword ptr [ebp+40h]
    L_004042a2:
        jmp short L_004042b4
    L_004042a4:
        fld dword ptr [ecx]
    L_004042a6:
        fadd dword ptr [ebp+40h]
    L_004042a9:
        fst dword ptr [ebp+40h]
    L_004042ac:
        call asm_FUN_00463b2c_00463b2c
    L_004042b1:
        mov dword ptr [ebp+3Ch],eax
    L_004042b4:
        mov eax,dword ptr [ebp+94h]
    L_004042ba:
        test eax,eax
    L_004042bc:
        je short L_004042e0
    L_004042be:
        lea eax,[ebp+50h]
    L_004042c1:
        lea edi,[esp+14h]
    L_004042c5:
        call asm_FUN_00404610_00404610
    L_004042ca:
        mov edx,dword ptr [eax]
    L_004042cc:
        lea ecx,[ebp+2A58h]
    L_004042d2:
        mov dword ptr [ecx],edx
    L_004042d4:
        mov edx,dword ptr [eax+4]
    L_004042d7:
        mov dword ptr [ecx+4],edx
    L_004042da:
        mov eax,dword ptr [eax+8]
    L_004042dd:
        mov dword ptr [ecx+8],eax
    L_004042e0:
        mov eax,dword ptr [ebp+0E0h]
    L_004042e6:
        test eax,eax
    L_004042e8:
        je short L_0040430f
    L_004042ea:
        lea eax,[ebp+9Ch]
    L_004042f0:
        lea edi,[esp+14h]
    L_004042f4:
        call asm_FUN_00404610_00404610
    L_004042f9:
        mov edx,dword ptr [eax]
    L_004042fb:
        lea ecx,[ebp+2A4Ch]
    L_00404301:
        mov dword ptr [ecx],edx
    L_00404303:
        mov edx,dword ptr [eax+4]
    L_00404306:
        mov dword ptr [ecx+4],edx
    L_00404309:
        mov eax,dword ptr [eax+8]
    L_0040430c:
        mov dword ptr [ecx+8],eax
    L_0040430f:
        mov eax,dword ptr [ebp+16Ch]
    L_00404315:
        test eax,eax
    L_00404317:
        je short L_0040433b
    L_00404319:
        lea ecx,[esp+80h]
    L_00404320:
        push ecx
    L_00404321:
        lea ebx,[ebp+0E8h]
    L_00404327:
        call asm_FUN_004049a0_004049a0
    L_0040432c:
        lea edi,[ebp+2B48h]
    L_00404332:
        mov ecx,7
    L_00404337:
        mov esi,eax
    L_00404339:
        rep movsd
    L_0040433b:
        mov al,byte ptr [ebp+20h]
    L_0040433e:
        test al,al
    L_00404340:
        je short L_0040437f
    L_00404342:
        movzx eax,al
    L_00404345:
        dec eax
    L_00404346:
        jne short L_0040437f
    L_00404348:
        fld dword ptr [ebp+2Ch]
    L_0040434b:
        lea esi,[ebp+24h]
    L_0040434e:
        fmul dword ptr [data_00470cb0]
    L_00404354:
        fsub dword ptr [data_00470b18]
    L_0040435a:
        fsin
    L_0040435c:
        fmul dword ptr [data_00470cac]
    L_00404362:
        fstp dword ptr [ebp+2A88h]
    L_00404368:
        call asm_FrameTimer_Tick_00404ed0
    L_0040436d:
        cmp dword ptr [ebp+28h],200h
    L_00404374:
        jl short L_0040437f
    L_00404376:
        push 0
    L_00404378:
        mov eax,esi
    L_0040437a:
        call asm_Player_SetSchedulerValue_00405410
    L_0040437f:
        pop edi
    L_00404380:
        pop esi
    L_00404381:
        pop ebp
    L_00404382:
        xor eax,eax
    L_00404384:
        pop ebx
    L_00404385:
        add esp,8Ch
    L_0040438b:
        ret 4
    }
}

// 0x0040BD80..0x0040BDD9: FUN_0040bd80
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040bd80_0040bd80() {
    __asm {
    L_0040bd80:
        sub esp,0Ch
    L_0040bd83:
        push ebp
    L_0040bd84:
        mov ebp,dword ptr [esp+14h]
    L_0040bd88:
        mov eax,dword ptr [ebp+74h]
    L_0040bd8b:
        test al,4
    L_0040bd8d:
        je short L_0040bd98
    L_0040bd8f:
        xor eax,eax
    L_0040bd91:
        pop ebp
    L_0040bd92:
        add esp,0Ch
    L_0040bd95:
        ret 4
    L_0040bd98:
        mov ecx,dword ptr [data_00477700]
    L_0040bd9e:
        test byte ptr [ecx+20h],1
    L_0040bda2:
        jne short L_0040bdc6
    L_0040bda4:
        test al,2
    L_0040bda6:
        jne short L_0040bdc6
    L_0040bda8:
        mov ecx,dword ptr [data_00474e30]
    L_0040bdae:
        test ch,1
    L_0040bdb1:
        je short L_0040bdc6
    L_0040bdb3:
        test al,1
    L_0040bdb5:
        je short L_0040bdc6
    L_0040bdb7:
        mov edx,dword ptr [ebp+54h]
    L_0040bdba:
        movzx eax,word ptr [edx]
    L_0040bdbd:
        push eax
    L_0040bdbe:
        lea eax,[ebp+18h]
    L_0040bdc1:
        call asm_Player_SetSchedulerValue_00405410
    L_0040bdc6:
        mov ecx,dword ptr [ebp+54h]
    L_0040bdc9:
        movzx edx,word ptr [ecx]
    L_0040bdcc:
        cmp dword ptr [ebp+1Ch],edx
    L_0040bdcf:
        push ebx
    L_0040bdd0:
        push esi
    L_0040bdd1:
        push edi
    L_0040bdd2:
        jl asm_target_0040c27c
    L_0040bdd8:
        TH10_REL8(0xeb, 0x0040bdd8, VA_asm_FUN_0040bd80_part_0040bde0)
    }
}

// 0x0040BDE0..0x0040C355: FUN_0040bd80
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040bd80_part_0040bde0() {
    __asm {
    L_0040bde0:
        mov eax,dword ptr [ebp+54h]
    L_0040bde3:
        movzx ecx,byte ptr [eax+2]
    L_0040bde7:
        cmp ecx,11h
    L_0040bdea:
        ja asm_target_0040c25f
    L_0040bdf0:
        jmp dword ptr [ecx*4+40C358h]
    L_0040bdf7:
        mov ecx,dword ptr [ebp+78h]
    L_0040bdfa:
        test ecx,ecx
    L_0040bdfc:
        jne asm_target_0040be8c
    L_0040be02:
        lea edi,[ebp+40h]
    L_0040be05:
        mov ebx,5
    L_0040be0a:
        lea ebx,[ebx+force_disp32_zero]
    L_0040be10:
        mov eax,dword ptr [edi]
    L_0040be12:
        mov esi,dword ptr [data_00491c10]
    L_0040be18:
        push eax
    L_0040be19:
        mov edx,esi
    L_0040be1b:
        call asm_AnimationManager_Find_004491c0
    L_0040be20:
        test eax,eax
    L_0040be22:
        jne short L_0040be26
    L_0040be24:
        mov dword ptr [edi],eax
    L_0040be26:
        push 46CFD4h
    L_0040be2b:
        push 0FFFFFFh
    L_0040be30:
        push esi
    L_0040be31:
        mov esi,eax
    L_0040be33:
        call asm_Recovery_MarkLogState_00447a50
    L_0040be38:
        add esp,0Ch
    L_0040be3b:
        mov eax,edi
    L_0040be3d:
        call asm_AnimationManager_StopAtFrame3_0040c4d0
    L_0040be42:
        add edi,4
    L_0040be45:
        dec ebx
    L_0040be46:
        jne short L_0040be10
    L_0040be48:
        mov ecx,dword ptr [ebp+40h]
    L_0040be4b:
        mov ebx,dword ptr [data_00491c10]
    L_0040be51:
        lea edi,[ebp+40h]
    L_0040be54:
        push ecx
    L_0040be55:
        mov edx,ebx
    L_0040be57:
        call asm_AnimationManager_Find_004491c0
    L_0040be5c:
        mov esi,eax
    L_0040be5e:
        test esi,esi
    L_0040be60:
        jne short L_0040be64
    L_0040be62:
        mov dword ptr [edi],eax
    L_0040be64:
        mov eax,dword ptr [ebp+54h]
    L_0040be67:
        add eax,4
    L_0040be6a:
        call asm_Path_DecodeXor_00417010
    L_0040be6f:
        mov edx,dword ptr [ebp+7Ch]
    L_0040be72:
        push eax
    L_0040be73:
        push edx
    L_0040be74:
        push ebx
    L_0040be75:
        call asm_Recovery_MarkLogState_00447a50
    L_0040be7a:
        add esp,0Ch
    L_0040be7d:
        mov eax,edi
    L_0040be7f:
        call asm_AnimationManager_StopAtFrame2_0040c480
    L_0040be84:
        inc dword ptr [ebp+78h]
    L_0040be87:
        jmp asm_target_0040c25f
    L_0040be8c:
        add eax,4
    L_0040be8f:
        call asm_Path_DecodeXor_00417010
    L_0040be94:
        mov ecx,dword ptr [ebp+78h]
    L_0040be97:
        push eax
    L_0040be98:
        mov eax,dword ptr [ebp+7Ch]
    L_0040be9b:
        push eax
    L_0040be9c:
        lea esi,[ebp+ecx*4+40h]
    L_0040bea0:
        call asm_AnimationManager_ValidateHandle_00449450
    L_0040bea5:
        mov edx,dword ptr [data_00491c10]
    L_0040beab:
        push edx
    L_0040beac:
        mov esi,eax
    L_0040beae:
        call asm_Recovery_MarkLogState_00447a50
    L_0040beb3:
        mov eax,dword ptr [ebp+78h]
    L_0040beb6:
        add esp,0Ch
    L_0040beb9:
        lea eax,[ebp+eax*4+40h]
    L_0040bebd:
        call asm_AnimationManager_StopAtFrame2_0040c480
    L_0040bec2:
        mov ecx,dword ptr [ebp+78h]
    L_0040bec5:
        inc ecx
    L_0040bec6:
        mov eax,ecx
    L_0040bec8:
        cmp eax,5
    L_0040becb:
        mov dword ptr [ebp+78h],ecx
    L_0040bece:
        jl asm_target_0040c25f
    L_0040bed4:
        mov dword ptr [ebp+78h],0
    L_0040bedb:
        jmp asm_target_0040c25f
    L_0040bee0:
        lea esi,[ebp+40h]
    L_0040bee3:
        mov edi,5
    L_0040bee8:
        mov eax,esi
    L_0040beea:
        call asm_AnimationManager_StopAtFrame3_0040c4d0
    L_0040beef:
        add esi,4
    L_0040bef2:
        dec edi
    L_0040bef3:
        jne short L_0040bee8
    L_0040bef5:
        jmp asm_target_0040c25f
    L_0040befa:
        mov ecx,dword ptr [ebp+30h]
    L_0040befd:
        test ecx,ecx
    L_0040beff:
        jg short L_0040bf0d
    L_0040bf01:
        mov ecx,dword ptr [eax+4]
    L_0040bf04:
        push ecx
    L_0040bf05:
        lea eax,[ebp+2Ch]
    L_0040bf08:
        call asm_Player_SetSchedulerValue_00405410
    L_0040bf0d:
        lea esi,[ebp+2Ch]
    L_0040bf10:
        push 0BF800000h
    L_0040bf15:
        call asm_FrameTimer_Advance_0044bf40
    L_0040bf1a:
        mov edx,dword ptr [ebp+54h]
    L_0040bf1d:
        mov eax,dword ptr [edx+4]
    L_0040bf20:
        test eax,eax
    L_0040bf22:
        jge short L_0040bf30
    L_0040bf24:
        push 3E7h
    L_0040bf29:
        mov eax,esi
    L_0040bf2b:
        call asm_Player_SetSchedulerValue_00405410
    L_0040bf30:
        test dword ptr [data_00474e36],1001h
    L_0040bf3a:
        jne short L_0040bf7f
    L_0040bf3c:
        mov eax,dword ptr [ebp+30h]
    L_0040bf3f:
        test eax,eax
    L_0040bf41:
        jle short L_0040bf7f
    L_0040bf43:
        mov ecx,dword ptr [data_00477700]
    L_0040bf49:
        test byte ptr [ecx+20h],1
    L_0040bf4d:
        jne asm_target_0040c34a
    L_0040bf53:
        mov ecx,dword ptr [data_00474e30]
    L_0040bf59:
        test ch,1
    L_0040bf5c:
        je asm_target_0040c34a
    L_0040bf62:
        cdq
    L_0040bf63:
        mov ecx,6
    L_0040bf68:
        idiv ecx
    L_0040bf6a:
        test edx,edx
    L_0040bf6c:
        jne asm_target_0040c34a
    L_0040bf72:
        push edx
    L_0040bf73:
        mov eax,esi
    L_0040bf75:
        call asm_Player_SetSchedulerValue_00405410
    L_0040bf7a:
        jmp asm_target_0040c25f
    L_0040bf7f:
        push 0
    L_0040bf81:
        xor edi,edi
    L_0040bf83:
        mov ecx,492590h
    L_0040bf88:
        call asm_AnimationManager_QueueResource_0043dc90
    L_0040bf8d:
        push edi
    L_0040bf8e:
        mov eax,esi
    L_0040bf90:
        call asm_Player_SetSchedulerValue_00405410
    L_0040bf95:
        jmp asm_target_0040c25f
    L_0040bf9a:
        mov ecx,dword ptr [ebp+30h]
    L_0040bf9d:
        xor ebx,ebx
    L_0040bf9f:
        cmp ecx,ebx
    L_0040bfa1:
        jg short L_0040bfaf
    L_0040bfa3:
        mov edx,dword ptr [eax+4]
    L_0040bfa6:
        push edx
    L_0040bfa7:
        lea eax,[ebp+2Ch]
    L_0040bfaa:
        call asm_Player_SetSchedulerValue_00405410
    L_0040bfaf:
        lea esi,[ebp+2Ch]
    L_0040bfb2:
        push 0BF800000h
    L_0040bfb7:
        call asm_FrameTimer_Advance_0044bf40
    L_0040bfbc:
        test dword ptr [data_00474e36],1001h
    L_0040bfc6:
        jne short L_0040c000
    L_0040bfc8:
        mov eax,dword ptr [ebp+30h]
    L_0040bfcb:
        cmp eax,ebx
    L_0040bfcd:
        jle short L_0040c000
    L_0040bfcf:
        mov ecx,dword ptr [data_00477700]
    L_0040bfd5:
        test byte ptr [ecx+20h],1
    L_0040bfd9:
        jne asm_target_0040c34a
    L_0040bfdf:
        mov ecx,dword ptr [data_00474e30]
    L_0040bfe5:
        test ch,1
    L_0040bfe8:
        je asm_target_0040c34a
    L_0040bfee:
        cdq
    L_0040bfef:
        mov ecx,6
    L_0040bff4:
        idiv ecx
    L_0040bff6:
        test edx,edx
    L_0040bff8:
        jne asm_target_0040c34a
    L_0040bffe:
        jmp short L_0040c00d
    L_0040c000:
        push ebx
    L_0040c001:
        xor edi,edi
    L_0040c003:
        mov ecx,492590h
    L_0040c008:
        call asm_AnimationManager_QueueResource_0043dc90
    L_0040c00d:
        push ebx
    L_0040c00e:
        mov eax,esi
    L_0040c010:
        call asm_Player_SetSchedulerValue_00405410
    L_0040c015:
        mov dword ptr [ebp+78h],ebx
    L_0040c018:
        mov dword ptr [data_004918a4],ebx
    L_0040c01e:
        jmp asm_target_0040c25f
    L_0040c023:
        mov edx,dword ptr [eax+4]
    L_0040c026:
        mov eax,dword ptr [ebp+edx*4+90h]
    L_0040c02d:
        lea esi,[ebp+edx*4+90h]
    L_0040c034:
        mov edx,dword ptr [data_00491c10]
    L_0040c03a:
        push eax
    L_0040c03b:
        call asm_AnimationManager_SetFlag_004492a0
    L_0040c040:
        mov dword ptr [esi],0
    L_0040c046:
        mov eax,dword ptr [ebp+54h]
    L_0040c049:
        mov ecx,dword ptr [eax+0Ch]
    L_0040c04c:
        mov edx,dword ptr [eax+8]
    L_0040c04f:
        mov eax,dword ptr [ebp+edx*4+80h]
    L_0040c056:
        push 0Fh
    L_0040c058:
        push ecx
    L_0040c059:
        push eax
    L_0040c05a:
        lea edi,[esp+2Ch]
    L_0040c05e:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_0040c063:
        mov ecx,dword ptr [ebp+54h]
    L_0040c066:
        mov edx,dword ptr [ecx+4]
    L_0040c069:
        mov eax,dword ptr [eax]
    L_0040c06b:
        mov dword ptr [ebp+edx*4+90h],eax
    L_0040c072:
        jmp asm_target_0040c25f
    L_0040c077:
        cmp dword ptr [data_00474c74],1
    L_0040c07e:
        jne asm_target_0040c25f
    L_0040c084:
        mov ecx,dword ptr [eax+4]
    L_0040c087:
        lea esi,[ebp+ecx*4+90h]
    L_0040c08e:
        call asm_AnimationManager_MarkForRemovalAndClearHandle_00449630
    L_0040c093:
        mov eax,dword ptr [ebp+54h]
    L_0040c096:
        mov edx,dword ptr [eax+0Ch]
    L_0040c099:
        mov eax,dword ptr [eax+8]
    L_0040c09c:
        mov ecx,dword ptr [ebp+eax*4+80h]
    L_0040c0a3:
        push 0Fh
    L_0040c0a5:
        push edx
    L_0040c0a6:
        push ecx
    L_0040c0a7:
        lea edi,[esp+1Ch]
    L_0040c0ab:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_0040c0b0:
        mov edx,dword ptr [ebp+54h]
    L_0040c0b3:
        mov ecx,dword ptr [edx+4]
    L_0040c0b6:
        mov edx,dword ptr [eax]
    L_0040c0b8:
        mov dword ptr [ebp+ecx*4+90h],edx
    L_0040c0bf:
        jmp asm_target_0040c25f
    L_0040c0c4:
        cmp dword ptr [data_00474c74],2
    L_0040c0cb:
        jne asm_target_0040c25f
    L_0040c0d1:
        mov eax,dword ptr [eax+4]
    L_0040c0d4:
        lea esi,[ebp+eax*4+90h]
    L_0040c0db:
        call asm_AnimationManager_MarkForRemovalAndClearHandle_00449630
    L_0040c0e0:
        mov eax,dword ptr [ebp+54h]
    L_0040c0e3:
        mov ecx,dword ptr [eax+0Ch]
    L_0040c0e6:
        mov edx,dword ptr [eax+8]
    L_0040c0e9:
        mov eax,dword ptr [ebp+edx*4+80h]
    L_0040c0f0:
        push 0Fh
    L_0040c0f2:
        push ecx
    L_0040c0f3:
        push eax
    L_0040c0f4:
        lea edi,[esp+20h]
    L_0040c0f8:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_0040c0fd:
        mov ecx,dword ptr [ebp+54h]
    L_0040c100:
        mov edx,dword ptr [ecx+4]
    L_0040c103:
        mov eax,dword ptr [eax]
    L_0040c105:
        mov dword ptr [ebp+edx*4+90h],eax
    L_0040c10c:
        jmp asm_target_0040c25f
    L_0040c111:
        cmp dword ptr [data_00474c74],3
    L_0040c118:
        jne asm_target_0040c25f
    L_0040c11e:
        mov ecx,dword ptr [eax+4]
    L_0040c121:
        lea esi,[ebp+ecx*4+90h]
    L_0040c128:
        call asm_AnimationManager_MarkForRemovalAndClearHandle_00449630
    L_0040c12d:
        mov eax,dword ptr [ebp+54h]
    L_0040c130:
        mov edx,dword ptr [eax+0Ch]
    L_0040c133:
        mov eax,dword ptr [eax+8]
    L_0040c136:
        mov ecx,dword ptr [ebp+eax*4+80h]
    L_0040c13d:
        push 0Fh
    L_0040c13f:
        push edx
    L_0040c140:
        push ecx
    L_0040c141:
        lea edi,[esp+24h]
    L_0040c145:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_0040c14a:
        mov edx,dword ptr [ebp+54h]
    L_0040c14d:
        mov ecx,dword ptr [edx+4]
    L_0040c150:
        mov edx,dword ptr [eax]
    L_0040c152:
        mov dword ptr [ebp+ecx*4+90h],edx
    L_0040c159:
        jmp asm_target_0040c25f
    L_0040c15e:
        mov eax,dword ptr [eax+4]
    L_0040c161:
        mov dword ptr [ebp+7Ch],eax
    L_0040c164:
        jmp asm_target_0040c25f
    L_0040c169:
        add eax,4
    L_0040c16c:
        push eax
    L_0040c16d:
        push 0
    L_0040c16f:
        call asm_Recovery_ReplaceExtensionWav_00420a90
    L_0040c174:
        mov esi,dword ptr [ebp+54h]
    L_0040c177:
        add esi,4
    L_0040c17a:
        mov edi,46CFC4h
    L_0040c17f:
        mov ecx,10h
    L_0040c184:
        xor edx,edx
    L_0040c186:
        repe cmpsb
    L_0040c188:
        jne short L_0040c197
    L_0040c18a:
        push 0Fh
    L_0040c18c:
        push edx
    L_0040c18d:
        call asm_Sound_PlayDummyRetail_00420b10
    L_0040c192:
        jmp asm_target_0040c25f
    L_0040c197:
        push 10h
    L_0040c199:
        push 0
    L_0040c19b:
        call asm_Sound_PlayDummyRetail_00420b10
    L_0040c1a0:
        jmp asm_target_0040c25f
    L_0040c1a5:
        push 40400000h
    L_0040c1aa:
        call asm_Sound_PlayRandomVoiceRetail_00420c30
    L_0040c1af:
        and dword ptr [ebp+74h],0FFFFFFFEh
    L_0040c1b3:
        jmp asm_target_0040c25f
    L_0040c1b8:
        mov ebx,dword ptr [data_00491c10]
    L_0040c1be:
        lea esi,[ebp+40h]
    L_0040c1c1:
        mov edi,5
    L_0040c1c6:
        mov eax,dword ptr [esi]
    L_0040c1c8:
        push eax
    L_0040c1c9:
        mov edx,ebx
    L_0040c1cb:
        call asm_AnimationManager_SetFlag_004492a0
    L_0040c1d0:
        mov dword ptr [esi],0
    L_0040c1d6:
        add esi,4
    L_0040c1d9:
        dec edi
    L_0040c1da:
        jne short L_0040c1c6
    L_0040c1dc:
        mov eax,dword ptr [ebp+54h]
    L_0040c1df:
        mov ecx,dword ptr [data_00477700]
    L_0040c1e5:
        add eax,4
    L_0040c1e8:
        push ecx
    L_0040c1e9:
        call asm_FUN_0040b480_0040b480
    L_0040c1ee:
        mov edx,eax
    L_0040c1f0:
        test edx,edx
    L_0040c1f2:
        je asm_target_0040c2c7
    L_0040c1f8:
        xor eax,eax
    L_0040c1fa:
        mov ecx,3Bh
    L_0040c1ff:
        mov edi,ebp
    L_0040c201:
        rep stosd
    L_0040c203:
        mov eax,dword ptr [edx+4]
    L_0040c206:
        add eax,edx
    L_0040c208:
        mov dword ptr [ebp+54h],eax
    L_0040c20b:
        push 0
    L_0040c20d:
        lea eax,[ebp+4]
    L_0040c210:
        call asm_Player_SetSchedulerValue_00405410
    L_0040c215:
        push 0
    L_0040c217:
        lea eax,[ebp+18h]
    L_0040c21a:
        call asm_Player_SetSchedulerValue_00405410
    L_0040c21f:
        push 0
    L_0040c221:
        lea eax,[ebp+2Ch]
    L_0040c224:
        call asm_Player_SetSchedulerValue_00405410
    L_0040c229:
        mov eax,dword ptr [ebp+74h]
    L_0040c22c:
        or eax,2
    L_0040c22f:
        mov dword ptr [ebp+7Ch],0FFFFFFh
    L_0040c236:
        mov dword ptr [ebp+74h],eax
    L_0040c239:
        jmp short L_0040c26d
    L_0040c23b:
        mov ecx,dword ptr [eax+4]
    L_0040c23e:
        push 0
    L_0040c240:
        push 0
    L_0040c242:
        push 0
    L_0040c244:
        push ecx
    L_0040c245:
        push 0
    L_0040c247:
        jmp short L_0040c255
    L_0040c249:
        mov edx,dword ptr [eax+4]
    L_0040c24c:
        push 0
    L_0040c24e:
        push 0
    L_0040c250:
        push 0
    L_0040c252:
        push edx
    L_0040c253:
        push 5
    L_0040c255:
        mov ebx,31h
    L_0040c25a:
        call asm_AsciiManager_CreateRetail_0043c8b0
    L_0040c25f:
        mov eax,dword ptr [ebp+54h]
    L_0040c262:
        movzx ecx,byte ptr [eax+3]
    L_0040c266:
        lea edx,[ecx+eax+4]
    L_0040c26a:
        mov dword ptr [ebp+54h],edx
    L_0040c26d:
        mov eax,dword ptr [ebp+54h]
    L_0040c270:
        movzx ecx,word ptr [eax]
    L_0040c273:
        cmp dword ptr [ebp+1Ch],ecx
    L_0040c276:
        jge asm_FUN_0040bd80_part_0040bde0
    L_0040c27c:
        mov edx,dword ptr [ebp+1Ch]
    L_0040c27f:
        mov ecx,dword ptr [ebp+24h]
    L_0040c282:
        mov dword ptr [ebp+18h],edx
    L_0040c285:
        fld dword ptr [ecx]
    L_0040c287:
        fcomp dword ptr [data_00470b68]
    L_0040c28d:
        fnstsw ax
    L_0040c28f:
        test ah,41h
    L_0040c292:
        jne asm_target_0040c33a
    L_0040c298:
        fld dword ptr [ecx]
    L_0040c29a:
        fcomp dword ptr [data_00470b64]
    L_0040c2a0:
        fnstsw ax
    L_0040c2a2:
        test ah,5
    L_0040c2a5:
        jp asm_target_0040c33a
    L_0040c2ab:
        fld dword ptr [ebp+20h]
    L_0040c2ae:
        pop edi
    L_0040c2af:
        fadd dword ptr [data_00470afc]
    L_0040c2b5:
        pop esi
    L_0040c2b6:
        inc edx
    L_0040c2b7:
        pop ebx
    L_0040c2b8:
        fstp dword ptr [ebp+20h]
    L_0040c2bb:
        mov dword ptr [ebp+1Ch],edx
    L_0040c2be:
        xor eax,eax
    L_0040c2c0:
        pop ebp
    L_0040c2c1:
        add esp,0Ch
    L_0040c2c4:
        ret 4
    L_0040c2c7:
        pop edi
    L_0040c2c8:
        pop esi
    L_0040c2c9:
        pop ebx
    L_0040c2ca:
        or eax,0FFFFFFFFh
    L_0040c2cd:
        pop ebp
    L_0040c2ce:
        add esp,0Ch
    L_0040c2d1:
        ret 4
    L_0040c2d4:
        mov esi,dword ptr [data_004776e0]
    L_0040c2da:
        push 43C40000h
    L_0040c2df:
        push 43F00000h
    L_0040c2e4:
        call asm_FUN_0040c540_0040c540
    L_0040c2e9:
        mov edx,dword ptr [ebp+54h]
    L_0040c2ec:
        mov esi,dword ptr [edx+4]
    L_0040c2ef:
        mov ebx,dword ptr [data_00491c10]
    L_0040c2f5:
        add esi,1Dh
    L_0040c2f8:
        call asm_AnimationManager_ClearResourceSlot_004477d0
    L_0040c2fd:
        mov eax,dword ptr [ebp+54h]
    L_0040c300:
        mov edx,dword ptr [ebp+74h]
    L_0040c303:
        add eax,8
    L_0040c306:
        or edx,4
    L_0040c309:
        mov dword ptr [ebp+70h],eax
    L_0040c30c:
        push ebp
    L_0040c30d:
        lea eax,[ebp+0D0h]
    L_0040c313:
        mov edi,40C3A0h
    L_0040c318:
        mov dword ptr [ebp+74h],edx
    L_0040c31b:
        call asm_FUN_0044c1c0_0044c1c0
    L_0040c320:
        mov eax,dword ptr [ebp+54h]
    L_0040c323:
        movzx ecx,byte ptr [eax+3]
    L_0040c327:
        pop edi
    L_0040c328:
        pop esi
    L_0040c329:
        lea edx,[ecx+eax+4]
    L_0040c32d:
        pop ebx
    L_0040c32e:
        mov dword ptr [ebp+54h],edx
    L_0040c331:
        xor eax,eax
    L_0040c333:
        pop ebp
    L_0040c334:
        add esp,0Ch
    L_0040c337:
        ret 4
    L_0040c33a:
        fld dword ptr [ecx]
    L_0040c33c:
        fadd dword ptr [ebp+20h]
    L_0040c33f:
        fst dword ptr [ebp+20h]
    L_0040c342:
        call asm_FUN_00463b2c_00463b2c
    L_0040c347:
        mov dword ptr [ebp+1Ch],eax
    L_0040c34a:
        pop edi
    L_0040c34b:
        pop esi
    L_0040c34c:
        pop ebx
    L_0040c34d:
        xor eax,eax
    L_0040c34f:
        pop ebp
    L_0040c350:
        add esp,0Ch
    L_0040c353:
        ret 4
    }
}
