#include <string.h>
#include "../../../include/asm_encoding.hpp"
#include "../../../include/asm_symbols.hpp"

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
        mov ebx,dword ptr [imp_SelectObject]
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
        call dword ptr [imp_SetBkMode]
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
        call dword ptr [imp_SetTextColor]
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
        call dword ptr [imp_TextOutA]
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
