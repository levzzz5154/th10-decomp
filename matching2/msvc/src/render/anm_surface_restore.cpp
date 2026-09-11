#include "asm_encoding.hpp"
#include "asm_symbols.hpp"


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

