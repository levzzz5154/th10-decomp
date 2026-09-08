#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00446D70..0x00446EAF: FUN_00446d70
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00446d70_00446d70() {
    __asm {
    L_00446d70:
        sub esp,34h
    L_00446d73:
        push ebx
    L_00446d74:
        push ebp
    L_00446d75:
        mov ebp,dword ptr [esp+48h]
    L_00446d79:
        push esi
    L_00446d7a:
        mov esi,ecx
    L_00446d7c:
        mov cl,byte ptr [data_00491d78]
    L_00446d82:
        xor ebx,ebx
    L_00446d84:
        test cl,1
    L_00446d87:
        mov dword ptr [esp+0Ch],eax
    L_00446d8b:
        je short L_00446db4
    L_00446d8d:
        mov eax,dword ptr [eax*4+46F288h]
    L_00446d94:
        cmp eax,15h
    L_00446d97:
        je short L_00446dac
    L_00446d99:
        cmp eax,ebx
    L_00446d9b:
        je short L_00446dac
    L_00446d9d:
        cmp eax,14h
    L_00446da0:
        jne short L_00446db4
    L_00446da2:
        mov dword ptr [esp+0Ch],3
    L_00446daa:
        jmp short L_00446db4
    L_00446dac:
        mov dword ptr [esp+0Ch],5
    L_00446db4:
        mov eax,dword ptr [esp+48h]
    L_00446db8:
        lea edx,[esp+4Ch]
    L_00446dbc:
        push edx
    L_00446dbd:
        mov dword ptr [eax+8],ebp
    L_00446dc0:
        mov eax,dword ptr [eax]
    L_00446dc2:
        push ebx
    L_00446dc3:
        mov dword ptr [esp+54h],ebx
    L_00446dc7:
        mov ecx,dword ptr [eax]
    L_00446dc9:
        push eax
    L_00446dca:
        call dword ptr [ecx+48h]
    L_00446dcd:
        cmp dword ptr [esp+50h],ebx
    L_00446dd1:
        jne short L_00446e13
    L_00446dd3:
        mov eax,dword ptr [esp+4Ch]
    L_00446dd7:
        mov ecx,dword ptr [eax]
    L_00446dd9:
        lea edx,[esp+20h]
    L_00446ddd:
        push edx
    L_00446dde:
        push eax
    L_00446ddf:
        call dword ptr [ecx+30h]
    L_00446de2:
        mov eax,dword ptr [esp+38h]
    L_00446de6:
        mov ecx,dword ptr [esp+3Ch]
    L_00446dea:
        push ebx
    L_00446deb:
        push ebx
    L_00446dec:
        push 1
    L_00446dee:
        push ebx
    L_00446def:
        push ebp
    L_00446df0:
        push edi
    L_00446df1:
        lea edx,[esp+28h]
    L_00446df5:
        push edx
    L_00446df6:
        mov dword ptr [esp+34h],eax
    L_00446dfa:
        mov eax,dword ptr [esp+68h]
    L_00446dfe:
        push ebx
    L_00446dff:
        push eax
    L_00446e00:
        mov dword ptr [esp+34h],ebx
    L_00446e04:
        mov dword ptr [esp+38h],esi
    L_00446e08:
        mov dword ptr [esp+40h],ecx
    L_00446e0c:
        call asm_D3DXLoadSurfaceFromFileInMemory_004521d0
    L_00446e11:
        jmp short L_00446e82
    L_00446e13:
        mov ecx,dword ptr [edi+30h]
    L_00446e16:
        lea eax,[ecx+edi]
    L_00446e19:
        mov dword ptr [esp+10h],ebx
    L_00446e1d:
        mov dword ptr [esp+14h],ebx
    L_00446e21:
        movsx edx,word ptr [eax+8]
    L_00446e25:
        mov dword ptr [esp+18h],edx
    L_00446e29:
        movsx ecx,word ptr [eax+0Ah]
    L_00446e2d:
        mov dword ptr [esp+1Ch],ecx
    L_00446e31:
        mov dword ptr [esp+20h],ebx
    L_00446e35:
        mov dword ptr [esp+24h],esi
    L_00446e39:
        movsx edx,word ptr [eax+8]
    L_00446e3d:
        mov dword ptr [esp+28h],edx
    L_00446e41:
        movsx ecx,word ptr [eax+0Ah]
    L_00446e45:
        push ebx
    L_00446e46:
        push 1
    L_00446e48:
        add ecx,esi
    L_00446e4a:
        mov dword ptr [esp+34h],ecx
    L_00446e4e:
        movsx ecx,word ptr [eax+6]
    L_00446e52:
        lea edx,[esp+18h]
    L_00446e56:
        push edx
    L_00446e57:
        movsx edx,word ptr [eax+8]
    L_00446e5b:
        shl ecx,2
    L_00446e5e:
        imul edx,dword ptr [ecx+46F2A0h]
    L_00446e65:
        mov ecx,dword ptr [ecx+46F288h]
    L_00446e6b:
        push ebx
    L_00446e6c:
        push edx
    L_00446e6d:
        push ecx
    L_00446e6e:
        add eax,10h
    L_00446e71:
        push eax
    L_00446e72:
        mov eax,dword ptr [esp+68h]
    L_00446e76:
        lea edx,[esp+3Ch]
    L_00446e7a:
        push edx
    L_00446e7b:
        push ebx
    L_00446e7c:
        push eax
    L_00446e7d:
        call asm_D3DXLoadSurfaceFromMemory_004521a6
    L_00446e82:
        mov eax,dword ptr [esp+4Ch]
    L_00446e86:
        mov ecx,dword ptr [eax]
    L_00446e88:
        push eax
    L_00446e89:
        call dword ptr [ecx+8]
    L_00446e8c:
        mov esi,dword ptr [esp+48h]
    L_00446e90:
        mov eax,esi
    L_00446e92:
        call asm_FUN_004465b0_004465b0
    L_00446e97:
        mov edx,dword ptr [esp+0Ch]
    L_00446e9b:
        mov eax,dword ptr [edx*4+46F2A0h]
    L_00446ea2:
        mov dword ptr [esi+0Ch],eax
    L_00446ea5:
        pop esi
    L_00446ea6:
        pop ebp
    L_00446ea7:
        xor eax,eax
    L_00446ea9:
        pop ebx
    L_00446eaa:
        add esp,34h
    L_00446ead:
        ret 10h
    }
}

// 0x00447FD0..0x00448119: FUN_00447fd0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00447fd0_00447fd0() {
    __asm {
    L_00447fd0:
        sub esp,1Ch
    L_00447fd3:
        push esi
    L_00447fd4:
        mov esi,eax
    L_00447fd6:
        mov eax,dword ptr [ebx+esi*4+3AD560h]
    L_00447fdd:
        test eax,eax
    L_00447fdf:
        je asm_target_00448113
    L_00447fe5:
        mov eax,dword ptr [data_00491c30]
    L_00447fea:
        mov ecx,dword ptr [eax]
    L_00447fec:
        lea edx,[esp+4]
    L_00447ff0:
        push edx
    L_00447ff1:
        push 0
    L_00447ff3:
        push 0
    L_00447ff5:
        push 0
    L_00447ff7:
        push eax
    L_00447ff8:
        call dword ptr [ecx+48h]
    L_00447ffb:
        test eax,eax
    L_00447ffd:
        jne asm_target_00448113
    L_00448003:
        mov eax,dword ptr [ebx+esi*4+3AD4E0h]
    L_0044800a:
        test eax,eax
    L_0044800c:
        push ebp
    L_0044800d:
        push edi
    L_0044800e:
        lea edi,[ebx+esi*4+3AD4E0h]
    L_00448015:
        jne asm_target_004480af
    L_0044801b:
        mov eax,dword ptr [data_00491c30]
    L_00448020:
        mov edx,dword ptr [eax]
    L_00448022:
        push 0
    L_00448024:
        mov ecx,esi
    L_00448026:
        imul ecx,1Ch
    L_00448029:
        push edi
    L_0044802a:
        push 1
    L_0044802c:
        push 0
    L_0044802e:
        lea ebp,[ecx+ebx]
    L_00448031:
        mov ecx,dword ptr [data_00491d14]
    L_00448037:
        push 0
    L_00448039:
        push ecx
    L_0044803a:
        mov ecx,dword ptr [ebp+3AD6E4h]
    L_00448040:
        push ecx
    L_00448041:
        mov ecx,dword ptr [ebp+3AD6E0h]
    L_00448047:
        push ecx
    L_00448048:
        push eax
    L_00448049:
        call dword ptr [edx+70h]
    L_0044804c:
        test eax,eax
    L_0044804e:
        je short L_0044807c
    L_00448050:
        mov ecx,dword ptr [data_00491d14]
    L_00448056:
        mov eax,dword ptr [data_00491c30]
    L_0044805b:
        mov edx,dword ptr [eax]
    L_0044805d:
        push 0
    L_0044805f:
        push edi
    L_00448060:
        push 3
    L_00448062:
        push ecx
    L_00448063:
        mov ecx,dword ptr [ebp+3AD6E4h]
    L_00448069:
        push ecx
    L_0044806a:
        mov ecx,dword ptr [ebp+3AD6E0h]
    L_00448070:
        push ecx
    L_00448071:
        push eax
    L_00448072:
        call dword ptr [edx+90h]
    L_00448078:
        test eax,eax
    L_0044807a:
        jne short L_0044809c
    L_0044807c:
        mov eax,dword ptr [ebx+esi*4+3AD560h]
    L_00448083:
        mov ecx,dword ptr [edi]
    L_00448085:
        push 0
    L_00448087:
        push 1
    L_00448089:
        push 0
    L_0044808b:
        push 0
    L_0044808d:
        push eax
    L_0044808e:
        push 0
    L_00448090:
        push 0
    L_00448092:
        push ecx
    L_00448093:
        call asm_D3DXLoadSurfaceFromSurface_004521d6
    L_00448098:
        test eax,eax
    L_0044809a:
        je short L_004480af
    L_0044809c:
        mov eax,dword ptr [esp+0Ch]
    L_004480a0:
        mov edx,dword ptr [eax]
    L_004480a2:
        push eax
    L_004480a3:
        call dword ptr [edx+8]
    L_004480a6:
        pop edi
    L_004480a7:
        pop ebp
    L_004480a8:
        pop esi
    L_004480a9:
        add esp,1Ch
    L_004480ac:
        ret 10h
    L_004480af:
        mov eax,dword ptr [esp+2Ch]
    L_004480b3:
        imul esi,1Ch
    L_004480b6:
        mov edx,dword ptr [esi+ebx+3AD6E0h]
    L_004480bd:
        mov ecx,dword ptr [esp+30h]
    L_004480c1:
        mov dword ptr [esp+18h],eax
    L_004480c5:
        lea eax,[esi+ebx]
    L_004480c8:
        mov eax,dword ptr [eax+3AD6E4h]
    L_004480ce:
        mov dword ptr [esp+20h],edx
    L_004480d2:
        mov edx,dword ptr [esp+38h]
    L_004480d6:
        mov dword ptr [esp+14h],edx
    L_004480da:
        lea edx,[esp+10h]
    L_004480de:
        push edx
    L_004480df:
        mov edx,dword ptr [esp+10h]
    L_004480e3:
        push edx
    L_004480e4:
        lea edx,[esp+20h]
    L_004480e8:
        push edx
    L_004480e9:
        mov edx,dword ptr [edi]
    L_004480eb:
        mov dword ptr [esp+28h],ecx
    L_004480ef:
        mov ecx,dword ptr [esp+40h]
    L_004480f3:
        mov dword ptr [esp+30h],eax
    L_004480f7:
        mov eax,dword ptr [data_00491c30]
    L_004480fc:
        push edx
    L_004480fd:
        mov dword ptr [esp+20h],ecx
    L_00448101:
        mov ecx,dword ptr [eax]
    L_00448103:
        push eax
    L_00448104:
        call dword ptr [ecx+78h]
    L_00448107:
        mov eax,dword ptr [esp+0Ch]
    L_0044810b:
        mov ecx,dword ptr [eax]
    L_0044810d:
        push eax
    L_0044810e:
        call dword ptr [ecx+8]
    L_00448111:
        pop edi
    L_00448112:
        pop ebp
    L_00448113:
        pop esi
    L_00448114:
        add esp,1Ch
    L_00448117:
        ret 10h
    }
}

// 0x00448120..0x00448264: FUN_00448120
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00448120_00448120() {
    __asm {
    L_00448120:
        sub esp,18h
    L_00448123:
        push ebp
    L_00448124:
        mov ebp,dword ptr [esp+20h]
    L_00448128:
        mov eax,dword ptr [ebp+ebx*4+3AD560h]
    L_0044812f:
        test eax,eax
    L_00448131:
        je asm_target_0044825e
    L_00448137:
        mov eax,dword ptr [data_00491c30]
    L_0044813c:
        mov ecx,dword ptr [eax]
    L_0044813e:
        lea edx,[esp+20h]
    L_00448142:
        push edx
    L_00448143:
        push 0
    L_00448145:
        push 0
    L_00448147:
        push 0
    L_00448149:
        push eax
    L_0044814a:
        call dword ptr [ecx+48h]
    L_0044814d:
        test eax,eax
    L_0044814f:
        jne asm_target_0044825e
    L_00448155:
        mov eax,dword ptr [ebp+ebx*4+3AD4E0h]
    L_0044815c:
        test eax,eax
    L_0044815e:
        push esi
    L_0044815f:
        lea esi,[ebp+ebx*4+3AD4E0h]
    L_00448166:
        push edi
    L_00448167:
        jne asm_target_00448201
    L_0044816d:
        mov eax,dword ptr [data_00491c30]
    L_00448172:
        mov edx,dword ptr [eax]
    L_00448174:
        push 0
    L_00448176:
        mov ecx,ebx
    L_00448178:
        imul ecx,1Ch
    L_0044817b:
        push esi
    L_0044817c:
        push 1
    L_0044817e:
        push 0
    L_00448180:
        lea edi,[ecx+ebp]
    L_00448183:
        mov ecx,dword ptr [data_00491d14]
    L_00448189:
        push 0
    L_0044818b:
        push ecx
    L_0044818c:
        mov ecx,dword ptr [edi+3AD6E4h]
    L_00448192:
        push ecx
    L_00448193:
        mov ecx,dword ptr [edi+3AD6E0h]
    L_00448199:
        push ecx
    L_0044819a:
        push eax
    L_0044819b:
        call dword ptr [edx+70h]
    L_0044819e:
        test eax,eax
    L_004481a0:
        je short L_004481ce
    L_004481a2:
        mov ecx,dword ptr [data_00491d14]
    L_004481a8:
        mov eax,dword ptr [data_00491c30]
    L_004481ad:
        mov edx,dword ptr [eax]
    L_004481af:
        push 0
    L_004481b1:
        push esi
    L_004481b2:
        push 3
    L_004481b4:
        push ecx
    L_004481b5:
        mov ecx,dword ptr [edi+3AD6E4h]
    L_004481bb:
        push ecx
    L_004481bc:
        mov ecx,dword ptr [edi+3AD6E0h]
    L_004481c2:
        push ecx
    L_004481c3:
        push eax
    L_004481c4:
        call dword ptr [edx+90h]
    L_004481ca:
        test eax,eax
    L_004481cc:
        jne short L_004481ee
    L_004481ce:
        mov eax,dword ptr [ebp+ebx*4+3AD560h]
    L_004481d5:
        mov ecx,dword ptr [esi]
    L_004481d7:
        push 0
    L_004481d9:
        push 1
    L_004481db:
        push 0
    L_004481dd:
        push 0
    L_004481df:
        push eax
    L_004481e0:
        push 0
    L_004481e2:
        push 0
    L_004481e4:
        push ecx
    L_004481e5:
        call asm_D3DXLoadSurfaceFromSurface_004521d6
    L_004481ea:
        test eax,eax
    L_004481ec:
        je short L_00448201
    L_004481ee:
        mov eax,dword ptr [esp+28h]
    L_004481f2:
        mov edx,dword ptr [eax]
    L_004481f4:
        push eax
    L_004481f5:
        call dword ptr [edx+8]
    L_004481f8:
        pop edi
    L_004481f9:
        pop esi
    L_004481fa:
        pop ebp
    L_004481fb:
        add esp,18h
    L_004481fe:
        ret 1Ch
    L_00448201:
        mov ecx,dword ptr [esp+34h]
    L_00448205:
        mov edx,dword ptr [esp+3Ch]
    L_00448209:
        mov eax,dword ptr [esp+38h]
    L_0044820d:
        mov dword ptr [esp+14h],ecx
    L_00448211:
        add ecx,edx
    L_00448213:
        mov edx,dword ptr [esp+2Ch]
    L_00448217:
        mov dword ptr [esp+0Ch],edx
    L_0044821b:
        lea edx,[esp+0Ch]
    L_0044821f:
        push edx
    L_00448220:
        mov edx,dword ptr [esp+2Ch]
    L_00448224:
        mov dword ptr [esp+1Ch],eax
    L_00448228:
        mov dword ptr [esp+20h],ecx
    L_0044822c:
        mov ecx,dword ptr [esp+44h]
    L_00448230:
        push edx
    L_00448231:
        add eax,ecx
    L_00448233:
        mov dword ptr [esp+28h],eax
    L_00448237:
        mov eax,dword ptr [esp+38h]
    L_0044823b:
        lea edx,[esp+1Ch]
    L_0044823f:
        push edx
    L_00448240:
        mov edx,dword ptr [esi]
    L_00448242:
        mov dword ptr [esp+1Ch],eax
    L_00448246:
        mov eax,dword ptr [data_00491c30]
    L_0044824b:
        mov ecx,dword ptr [eax]
    L_0044824d:
        push edx
    L_0044824e:
        push eax
    L_0044824f:
        call dword ptr [ecx+78h]
    L_00448252:
        mov eax,dword ptr [esp+28h]
    L_00448256:
        mov ecx,dword ptr [eax]
    L_00448258:
        push eax
    L_00448259:
        call dword ptr [ecx+8]
    L_0044825c:
        pop edi
    L_0044825d:
        pop esi
    L_0044825e:
        pop ebp
    L_0044825f:
        add esp,18h
    L_00448262:
        ret 1Ch
    }
}
