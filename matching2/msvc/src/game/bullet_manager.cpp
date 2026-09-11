#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00402720..0x0040284F: FUN_00402720
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00402720_00402720() {
    __asm {
    L_00402720:
        sub esp,10h
    L_00402723:
        push ebx
    L_00402724:
        mov ebx,eax
    L_00402726:
        mov eax,dword ptr [ebx+2A18h]
    L_0040272c:
        test al,8
    L_0040272e:
        jne asm_target_00402846
    L_00402734:
        test al,4
    L_00402736:
        je short L_00402745
    L_00402738:
        cmp dword ptr [ebx+2A20h],3Ch
    L_0040273f:
        jge asm_target_00402846
    L_00402745:
        mov dword ptr [esp+8],0
    L_0040274d:
        mov ecx,dword ptr [esp+8]
    L_00402751:
        lea eax,[ebx+2B3Ch]
    L_00402757:
        mov dword ptr [eax],ecx
    L_00402759:
        push esi
    L_0040275a:
        mov dword ptr [esp+10h],0
    L_00402762:
        mov edx,dword ptr [esp+10h]
    L_00402766:
        mov dword ptr [eax+4],edx
    L_00402769:
        push edi
    L_0040276a:
        mov dword ptr [esp+18h],0
    L_00402772:
        mov ecx,dword ptr [esp+18h]
    L_00402776:
        lea edx,[ebx+2A58h]
    L_0040277c:
        mov dword ptr [eax+8],ecx
    L_0040277f:
        push edx
    L_00402780:
        lea eax,[ebx+2A70h]
    L_00402786:
        push eax
    L_00402787:
        mov dword ptr [ebx+2B34h],0
    L_00402791:
        mov dword ptr [ebx+2B38h],0
    L_0040279b:
        call asm_D3DXVec3Normalize_0045217c
    L_004027a0:
        mov dword ptr [ebx+1EE8h],808080h
    L_004027aa:
        call asm_FUN_00403990_00403990
    L_004027af:
        push ebx
    L_004027b0:
        call asm_FUN_00403c80_00403c80
    L_004027b5:
        lea esi,[ebx+180h]
    L_004027bb:
        mov edi,8
    L_004027c0:
        push esi
    L_004027c1:
        call asm_FUN_0043ee30_0043ee30
    L_004027c6:
        add esi,3ACh
    L_004027cc:
        dec edi
    L_004027cd:
        jne short L_004027c0
    L_004027cf:
        mov eax,dword ptr [ebx+1EECh]
    L_004027d5:
        test eax,eax
    L_004027d7:
        je short L_0040281b
    L_004027d9:
        mov ecx,dword ptr [data_00476f78]
    L_004027df:
        lea edx,[ebx+1F08h]
    L_004027e5:
        push edx
    L_004027e6:
        mov dword ptr [esp+10h],ecx
    L_004027ea:
        mov dword ptr [data_00476f78],3F800000h
    L_004027f4:
        call asm_FUN_0043ee30_0043ee30
    L_004027f9:
        lea eax,[ebx+22B4h]
    L_004027ff:
        push eax
    L_00402800:
        call asm_FUN_0043ee30_0043ee30
    L_00402805:
        lea ecx,[ebx+2660h]
    L_0040280b:
        push ecx
    L_0040280c:
        call asm_FUN_0043ee30_0043ee30
    L_00402811:
        mov edx,dword ptr [esp+0Ch]
    L_00402815:
        mov dword ptr [data_00476f78],edx
    L_0040281b:
        lea esi,[ebx+2A4Ch]
    L_00402821:
        mov ecx,46h
    L_00402826:
        mov edi,491D7Ch
    L_0040282b:
        mov dword ptr [ebx+1EECh],0
    L_00402835:
        rep movsd
    L_00402837:
        mov eax,dword ptr [ebx+2A34h]
    L_0040283d:
        inc eax
    L_0040283e:
        pop edi
    L_0040283f:
        mov dword ptr [ebx+2A34h],eax
    L_00402845:
        pop esi
    L_00402846:
        mov eax,1
    L_0040284b:
        pop ebx
    L_0040284c:
        add esp,10h
    L_0040284f:
        ret
    }
}








