#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00437DB0..0x00437FD9: FUN_00437db0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00437db0_00437db0() {
    __asm {
    L_00437db0:
        sub esp,14h
    L_00437db3:
        push ebx
    L_00437db4:
        mov ebx,dword ptr [esp+24h]
    L_00437db8:
        cmp ebx,11h
    L_00437dbb:
        push ebp
    L_00437dbc:
        push esi
    L_00437dbd:
        push edi
    L_00437dbe:
        jg short L_00437dcb
    L_00437dc0:
        mov edx,dword ptr [data_004918a0]
    L_00437dc6:
        jmp asm_target_00437e81
    L_00437dcb:
        cmp ebx,12h
    L_00437dce:
        jg short L_00437ddb
    L_00437dd0:
        mov edx,dword ptr [data_0049189c]
    L_00437dd6:
        jmp asm_target_00437e81
    L_00437ddb:
        cmp ebx,13h
    L_00437dde:
        jg short L_00437deb
    L_00437de0:
        mov edx,dword ptr [data_00491898]
    L_00437de6:
        jmp asm_target_00437e81
    L_00437deb:
        cmp ebx,14h
    L_00437dee:
        jg short L_00437dfb
    L_00437df0:
        mov edx,dword ptr [data_00491894]
    L_00437df6:
        jmp asm_target_00437e81
    L_00437dfb:
        cmp ebx,15h
    L_00437dfe:
        jg short L_00437e08
    L_00437e00:
        mov edx,dword ptr [data_00491890]
    L_00437e06:
        jmp short L_00437e81
    L_00437e08:
        cmp ebx,16h
    L_00437e0b:
        jg short L_00437e15
    L_00437e0d:
        mov edx,dword ptr [data_0049188c]
    L_00437e13:
        jmp short L_00437e81
    L_00437e15:
        cmp ebx,17h
    L_00437e18:
        jg short L_00437e22
    L_00437e1a:
        mov edx,dword ptr [data_00491888]
    L_00437e20:
        jmp short L_00437e81
    L_00437e22:
        cmp ebx,18h
    L_00437e25:
        jg short L_00437e2f
    L_00437e27:
        mov edx,dword ptr [data_00491884]
    L_00437e2d:
        jmp short L_00437e81
    L_00437e2f:
        cmp ebx,19h
    L_00437e32:
        jg short L_00437e3c
    L_00437e34:
        mov edx,dword ptr [data_00491880]
    L_00437e3a:
        jmp short L_00437e81
    L_00437e3c:
        cmp ebx,1Ah
    L_00437e3f:
        jg short L_00437e49
    L_00437e41:
        mov edx,dword ptr [data_0049187c]
    L_00437e47:
        jmp short L_00437e81
    L_00437e49:
        cmp ebx,1Bh
    L_00437e4c:
        jg short L_00437e56
    L_00437e4e:
        mov edx,dword ptr [data_00491878]
    L_00437e54:
        jmp short L_00437e81
    L_00437e56:
        cmp ebx,1Ch
    L_00437e59:
        jg short L_00437e63
    L_00437e5b:
        mov edx,dword ptr [data_00491874]
    L_00437e61:
        jmp short L_00437e81
    L_00437e63:
        cmp ebx,1Dh
    L_00437e66:
        jg short L_00437e70
    L_00437e68:
        mov edx,dword ptr [data_00491870]
    L_00437e6e:
        jmp short L_00437e81
    L_00437e70:
        cmp ebx,1Eh
    L_00437e73:
        mov edx,dword ptr [data_0049186c]
    L_00437e79:
        jle short L_00437e81
    L_00437e7b:
        mov edx,dword ptr [data_00491868]
    L_00437e81:
        cmp ebx,11h
    L_00437e84:
        jge short L_00437e92
    L_00437e86:
        mov dword ptr [esp+30h],11h
    L_00437e8e:
        mov ebx,dword ptr [esp+30h]
    L_00437e92:
        mov ecx,dword ptr [data_00474dbc]
    L_00437e98:
        mov edi,dword ptr [data_00474dd0]
    L_00437e9e:
        mov esi,ecx
    L_00437ea0:
        shr ecx,2
    L_00437ea3:
        xor eax,eax
    L_00437ea5:
        rep stosd
    L_00437ea7:
        mov ecx,esi
    L_00437ea9:
        and ecx,3
    L_00437eac:
        rep stosb
    L_00437eae:
        mov esi,dword ptr [data_00474dc4]
    L_00437eb4:
        push edx
    L_00437eb5:
        push esi
    L_00437eb6:
        call dword ptr [data_0046602c]
    L_00437ebc:
        lea ebx,[ebx+ebx+6]
    L_00437ec0:
        push ebx
    L_00437ec1:
        mov ecx,474CB0h
    L_00437ec6:
        mov dword ptr [esp+14h],eax
    L_00437eca:
        call asm_FUN_00437160_00437160
    L_00437ecf:
        push 1
    L_00437ed1:
        push esi
    L_00437ed2:
        call dword ptr [data_0046601c]
    L_00437ed8:
        mov eax,dword ptr [esp+38h]
    L_00437edc:
        lea edi,[eax+1]
    L_00437edf:
        nop
    L_00437ee0:
        mov cl,byte ptr [eax]
    L_00437ee2:
        inc eax
    L_00437ee3:
        test cl,cl
    L_00437ee5:
        jne short L_00437ee0
    L_00437ee7:
        push 0
    L_00437ee9:
        sub eax,edi
    L_00437eeb:
        push esi
    L_00437eec:
        mov edi,eax
    L_00437eee:
        call dword ptr [data_00466018]
    L_00437ef4:
        mov eax,dword ptr [esp+38h]
    L_00437ef8:
        mov ebp,dword ptr [esp+2Ch]
    L_00437efc:
        push edi
    L_00437efd:
        push eax
    L_00437efe:
        add ebp,ebp
    L_00437f00:
        push 2
    L_00437f02:
        lea ecx,[ebp+2]
    L_00437f05:
        push ecx
    L_00437f06:
        push esi
    L_00437f07:
        call dword ptr [data_00466014]
    L_00437f0d:
        mov edx,dword ptr [esp+34h]
    L_00437f11:
        push edx
    L_00437f12:
        push esi
    L_00437f13:
        call dword ptr [data_00466018]
    L_00437f19:
        mov eax,dword ptr [esp+38h]
    L_00437f1d:
        push edi
    L_00437f1e:
        push eax
    L_00437f1f:
        push 0
    L_00437f21:
        push ebp
    L_00437f22:
        push esi
    L_00437f23:
        call dword ptr [data_00466014]
    L_00437f29:
        mov edi,dword ptr [esp+10h]
    L_00437f2d:
        mov ebp,dword ptr [data_0046602c]
    L_00437f33:
        push edi
    L_00437f34:
        push esi
    L_00437f35:
        call ebp
    L_00437f37:
        push ebx
    L_00437f38:
        mov ecx,474CB0h
    L_00437f3d:
        call asm_FUN_00437160_00437160
    L_00437f42:
        push ebx
    L_00437f43:
        push 474CB0h
    L_00437f48:
        call asm_FUN_00436da0_00436da0
    L_00437f4d:
        push edi
    L_00437f4e:
        push esi
    L_00437f4f:
        call ebp
    L_00437f51:
        mov esi,dword ptr [esp+28h]
    L_00437f55:
        mov edx,dword ptr [esi]
    L_00437f57:
        mov eax,dword ptr [esi+8]
    L_00437f5a:
        mov ecx,dword ptr [esp+30h]
    L_00437f5e:
        sub eax,edx
    L_00437f60:
        xor edi,edi
    L_00437f62:
        lea eax,[eax+eax+16h]
    L_00437f66:
        cmp eax,400h
    L_00437f6b:
        lea edx,[ecx+ecx+2]
    L_00437f6f:
        mov dword ptr [esp+14h],edi
    L_00437f73:
        mov dword ptr [esp+18h],edi
    L_00437f77:
        mov dword ptr [esp+1Ch],eax
    L_00437f7b:
        mov dword ptr [esp+20h],edx
    L_00437f7f:
        jle short L_00437f89
    L_00437f81:
        mov dword ptr [esp+1Ch],400h
    L_00437f89:
        mov eax,dword ptr [esp+3Ch]
    L_00437f8d:
        mov ecx,dword ptr [eax]
    L_00437f8f:
        lea edx,[esp+30h]
    L_00437f93:
        push edx
    L_00437f94:
        push edi
    L_00437f95:
        push eax
    L_00437f96:
        call dword ptr [ecx+48h]
    L_00437f99:
        mov ecx,dword ptr [data_00474dc0]
    L_00437f9f:
        mov edx,dword ptr [data_00474db0]
    L_00437fa5:
        push edi
    L_00437fa6:
        push 4
    L_00437fa8:
        lea eax,[esp+1Ch]
    L_00437fac:
        push eax
    L_00437fad:
        mov eax,dword ptr [data_00474dd0]
    L_00437fb2:
        push edi
    L_00437fb3:
        push ecx
    L_00437fb4:
        mov ecx,dword ptr [esp+44h]
    L_00437fb8:
        push edx
    L_00437fb9:
        push eax
    L_00437fba:
        push esi
    L_00437fbb:
        push edi
    L_00437fbc:
        push ecx
    L_00437fbd:
        call asm_D3DXLoadSurfaceFromMemory_004521a6
    L_00437fc2:
        mov eax,dword ptr [esp+30h]
    L_00437fc6:
        cmp eax,edi
    L_00437fc8:
        pop edi
    L_00437fc9:
        pop esi
    L_00437fca:
        pop ebp
    L_00437fcb:
        pop ebx
    L_00437fcc:
        je short L_00437fd4
    L_00437fce:
        mov edx,dword ptr [eax]
    L_00437fd0:
        push eax
    L_00437fd1:
        call dword ptr [edx+8]
    L_00437fd4:
        add esp,14h
    L_00437fd7:
        ret 18h
    }
}

// 0x00437FE0..0x004381DC: FUN_00437fe0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00437fe0_00437fe0() {
    __asm {
    L_00437fe0:
        sub esp,14h
    L_00437fe3:
        push ebx
    L_00437fe4:
        push ebp
    L_00437fe5:
        mov ebp,dword ptr [esp+28h]
    L_00437fe9:
        cmp ebp,11h
    L_00437fec:
        push esi
    L_00437fed:
        push edi
    L_00437fee:
        jg short L_00437ffb
    L_00437ff0:
        mov edi,dword ptr [data_004918a0]
    L_00437ff6:
        jmp asm_target_004380b1
    L_00437ffb:
        cmp ebp,12h
    L_00437ffe:
        jg short L_0043800b
    L_00438000:
        mov edi,dword ptr [data_0049189c]
    L_00438006:
        jmp asm_target_004380b1
    L_0043800b:
        cmp ebp,13h
    L_0043800e:
        jg short L_0043801b
    L_00438010:
        mov edi,dword ptr [data_00491898]
    L_00438016:
        jmp asm_target_004380b1
    L_0043801b:
        cmp ebp,14h
    L_0043801e:
        jg short L_0043802b
    L_00438020:
        mov edi,dword ptr [data_00491894]
    L_00438026:
        jmp asm_target_004380b1
    L_0043802b:
        cmp ebp,15h
    L_0043802e:
        jg short L_00438038
    L_00438030:
        mov edi,dword ptr [data_00491890]
    L_00438036:
        jmp short L_004380b1
    L_00438038:
        cmp ebp,16h
    L_0043803b:
        jg short L_00438045
    L_0043803d:
        mov edi,dword ptr [data_0049188c]
    L_00438043:
        jmp short L_004380b1
    L_00438045:
        cmp ebp,17h
    L_00438048:
        jg short L_00438052
    L_0043804a:
        mov edi,dword ptr [data_00491888]
    L_00438050:
        jmp short L_004380b1
    L_00438052:
        cmp ebp,18h
    L_00438055:
        jg short L_0043805f
    L_00438057:
        mov edi,dword ptr [data_00491884]
    L_0043805d:
        jmp short L_004380b1
    L_0043805f:
        cmp ebp,19h
    L_00438062:
        jg short L_0043806c
    L_00438064:
        mov edi,dword ptr [data_00491880]
    L_0043806a:
        jmp short L_004380b1
    L_0043806c:
        cmp ebp,1Ah
    L_0043806f:
        jg short L_00438079
    L_00438071:
        mov edi,dword ptr [data_0049187c]
    L_00438077:
        jmp short L_004380b1
    L_00438079:
        cmp ebp,1Bh
    L_0043807c:
        jg short L_00438086
    L_0043807e:
        mov edi,dword ptr [data_00491878]
    L_00438084:
        jmp short L_004380b1
    L_00438086:
        cmp ebp,1Ch
    L_00438089:
        jg short L_00438093
    L_0043808b:
        mov edi,dword ptr [data_00491874]
    L_00438091:
        jmp short L_004380b1
    L_00438093:
        cmp ebp,1Dh
    L_00438096:
        jg short L_004380a0
    L_00438098:
        mov edi,dword ptr [data_00491870]
    L_0043809e:
        jmp short L_004380b1
    L_004380a0:
        cmp ebp,1Eh
    L_004380a3:
        mov edi,dword ptr [data_0049186c]
    L_004380a9:
        jle short L_004380b1
    L_004380ab:
        mov edi,dword ptr [data_00491868]
    L_004380b1:
        cmp ebp,11h
    L_004380b4:
        jge short L_004380bb
    L_004380b6:
        mov ebp,11h
    L_004380bb:
        mov ecx,dword ptr [esp+34h]
    L_004380bf:
        mov esi,474CB0h
    L_004380c4:
        call asm_FUN_00436ca0_00436ca0
    L_004380c9:
        mov esi,dword ptr [data_00474dc4]
    L_004380cf:
        mov ebx,dword ptr [data_0046602c]
    L_004380d5:
        push edi
    L_004380d6:
        push esi
    L_004380d7:
        call ebx
    L_004380d9:
        lea edi,[ebp+ebp+6]
    L_004380dd:
        push edi
    L_004380de:
        mov ecx,474CB0h
    L_004380e3:
        mov dword ptr [esp+34h],eax
    L_004380e7:
        call asm_FUN_00437160_00437160
    L_004380ec:
        push 1
    L_004380ee:
        push esi
    L_004380ef:
        call dword ptr [data_0046601c]
    L_004380f5:
        mov eax,dword ptr [esp+38h]
    L_004380f9:
        lea ecx,[eax+1]
    L_004380fc:
        TH10_NOP_LEA_ESP_DISP8()
    L_00438100:
        mov dl,byte ptr [eax]
    L_00438102:
        inc eax
    L_00438103:
        test dl,dl
    L_00438105:
        jne short L_00438100
    L_00438107:
        sub eax,ecx
    L_00438109:
        mov dword ptr [esp+10h],eax
    L_0043810d:
        mov eax,dword ptr [esp+34h]
    L_00438111:
        push eax
    L_00438112:
        push esi
    L_00438113:
        call dword ptr [data_00466018]
    L_00438119:
        mov ecx,dword ptr [esp+10h]
    L_0043811d:
        mov edx,dword ptr [esp+38h]
    L_00438121:
        mov eax,dword ptr [esp+2Ch]
    L_00438125:
        push ecx
    L_00438126:
        push edx
    L_00438127:
        push 0
    L_00438129:
        lea ecx,[eax+eax]
    L_0043812c:
        push ecx
    L_0043812d:
        push esi
    L_0043812e:
        call dword ptr [data_00466014]
    L_00438134:
        mov edx,dword ptr [esp+30h]
    L_00438138:
        push edx
    L_00438139:
        push esi
    L_0043813a:
        call ebx
    L_0043813c:
        push edi
    L_0043813d:
        mov ecx,474CB0h
    L_00438142:
        call asm_FUN_00437160_00437160
    L_00438147:
        push edi
    L_00438148:
        push 474CB0h
    L_0043814d:
        call asm_FUN_00436da0_00436da0
    L_00438152:
        mov eax,dword ptr [esp+30h]
    L_00438156:
        push eax
    L_00438157:
        push esi
    L_00438158:
        call ebx
    L_0043815a:
        mov esi,dword ptr [esp+28h]
    L_0043815e:
        mov eax,dword ptr [esi+8]
    L_00438161:
        sub eax,dword ptr [esi]
    L_00438163:
        xor edi,edi
    L_00438165:
        lea eax,[eax+eax+16h]
    L_00438169:
        cmp eax,400h
    L_0043816e:
        lea ecx,[ebp+ebp+2]
    L_00438172:
        mov dword ptr [esp+14h],edi
    L_00438176:
        mov dword ptr [esp+18h],edi
    L_0043817a:
        mov dword ptr [esp+1Ch],eax
    L_0043817e:
        mov dword ptr [esp+20h],ecx
    L_00438182:
        jle short L_0043818c
    L_00438184:
        mov dword ptr [esp+1Ch],400h
    L_0043818c:
        mov eax,dword ptr [esp+3Ch]
    L_00438190:
        mov edx,dword ptr [eax]
    L_00438192:
        lea ecx,[esp+34h]
    L_00438196:
        push ecx
    L_00438197:
        push edi
    L_00438198:
        push eax
    L_00438199:
        call dword ptr [edx+48h]
    L_0043819c:
        mov eax,dword ptr [data_00474dc0]
    L_004381a1:
        mov ecx,dword ptr [data_00474db0]
    L_004381a7:
        push edi
    L_004381a8:
        push 4
    L_004381aa:
        lea edx,[esp+1Ch]
    L_004381ae:
        push edx
    L_004381af:
        mov edx,dword ptr [data_00474dd0]
    L_004381b5:
        push edi
    L_004381b6:
        push eax
    L_004381b7:
        mov eax,dword ptr [esp+48h]
    L_004381bb:
        push ecx
    L_004381bc:
        push edx
    L_004381bd:
        push esi
    L_004381be:
        push edi
    L_004381bf:
        push eax
    L_004381c0:
        call asm_D3DXLoadSurfaceFromMemory_004521a6
    L_004381c5:
        mov eax,dword ptr [esp+34h]
    L_004381c9:
        cmp eax,edi
    L_004381cb:
        pop edi
    L_004381cc:
        pop esi
    L_004381cd:
        pop ebp
    L_004381ce:
        pop ebx
    L_004381cf:
        je short L_004381d7
    L_004381d1:
        mov ecx,dword ptr [eax]
    L_004381d3:
        push eax
    L_004381d4:
        call dword ptr [ecx+8]
    L_004381d7:
        add esp,14h
    L_004381da:
        ret 18h
    }
}
