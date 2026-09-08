#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00437590..0x00437665: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00437590() {
    __asm {
    L_00437590:
        mov eax,dword ptr [ebx+11Ch]
    L_00437596:
        sub esp,44h
    L_00437599:
        push esi
    L_0043759a:
        mov esi,dword ptr [esp+4Ch]
    L_0043759e:
        push edi
    L_0043759f:
        xor edi,edi
    L_004375a1:
        cmp eax,edi
    L_004375a3:
        jne short L_004375af
    L_004375a5:
        pop edi
    L_004375a6:
        xor al,al
    L_004375a8:
        pop esi
    L_004375a9:
        add esp,44h
    L_004375ac:
        ret 4
    L_004375af:
        mov eax,dword ptr [esi]
    L_004375b1:
        push ebp
    L_004375b2:
        lea ecx,[esp+30h]
    L_004375b6:
        push ecx
    L_004375b7:
        push esi
    L_004375b8:
        call dword ptr [eax+30h]
    L_004375bb:
        mov edx,dword ptr [ebx+104h]
    L_004375c1:
        mov eax,dword ptr [ebx+108h]
    L_004375c7:
        mov ecx,dword ptr [esi]
    L_004375c9:
        push 10h
    L_004375cb:
        mov dword ptr [esp+2Ch],edx
    L_004375cf:
        lea edx,[esp+24h]
    L_004375d3:
        mov dword ptr [esp+30h],eax
    L_004375d7:
        push edx
    L_004375d8:
        lea eax,[esp+20h]
    L_004375dc:
        push eax
    L_004375dd:
        push esi
    L_004375de:
        mov dword ptr [esp+30h],edi
    L_004375e2:
        mov dword ptr [esp+34h],edi
    L_004375e6:
        call dword ptr [ecx+34h]
    L_004375e9:
        mov edx,dword ptr [esp+18h]
    L_004375ed:
        mov ebp,dword ptr [esp+30h]
    L_004375f1:
        cmp ebp,dword ptr [ebx+100h]
    L_004375f7:
        mov ecx,dword ptr [ebx+110h]
    L_004375fd:
        mov eax,dword ptr [esp+1Ch]
    L_00437601:
        mov dword ptr [esp+10h],edx
    L_00437605:
        mov edx,dword ptr [ebx+120h]
    L_0043760b:
        mov dword ptr [esp+14h],ecx
    L_0043760f:
        jne short L_00437655
    L_00437611:
        cmp dword ptr [ebx+108h],edi
    L_00437617:
        mov dword ptr [esp+0Ch],edi
    L_0043761b:
        jle short L_00437655
    L_0043761d:
        TH10_NOP_LEA_ECX_DISP8()
    L_00437620:
        mov ebp,ecx
    L_00437622:
        shr ecx,2
    L_00437625:
        mov esi,eax
    L_00437627:
        mov edi,edx
    L_00437629:
        rep movsd
    L_0043762b:
        mov ecx,ebp
    L_0043762d:
        and ecx,3
    L_00437630:
        rep movsb
    L_00437632:
        mov edi,dword ptr [esp+10h]
    L_00437636:
        mov ecx,dword ptr [esp+14h]
    L_0043763a:
        mov esi,dword ptr [esp+0Ch]
    L_0043763e:
        add eax,edi
    L_00437640:
        mov edi,dword ptr [ebx+108h]
    L_00437646:
        add edx,ecx
    L_00437648:
        inc esi
    L_00437649:
        cmp esi,edi
    L_0043764b:
        mov dword ptr [esp+0Ch],esi
    L_0043764f:
        jl short L_00437620
    L_00437651:
        mov esi,dword ptr [esp+54h]
    L_00437655:
        mov eax,dword ptr [esi]
    L_00437657:
        push esi
    L_00437658:
        call dword ptr [eax+38h]
    L_0043765b:
        pop ebp
    L_0043765c:
        pop edi
    L_0043765d:
        mov al,1
    L_0043765f:
        pop esi
    L_00437660:
        add esp,44h
    L_00437663:
        ret 4
    }
}
