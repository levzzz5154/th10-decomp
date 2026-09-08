#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00437670..0x00437745: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00437670() {
    __asm {
    L_00437670:
        mov eax,dword ptr [ebx+11Ch]
    L_00437676:
        sub esp,44h
    L_00437679:
        push esi
    L_0043767a:
        mov esi,dword ptr [esp+4Ch]
    L_0043767e:
        push edi
    L_0043767f:
        xor edi,edi
    L_00437681:
        cmp eax,edi
    L_00437683:
        je short L_004376c1
    L_00437685:
        mov eax,dword ptr [esi]
    L_00437687:
        lea ecx,[esp+2Ch]
    L_0043768b:
        push ecx
    L_0043768c:
        push esi
    L_0043768d:
        call dword ptr [eax+30h]
    L_00437690:
        mov edx,dword ptr [ebx+104h]
    L_00437696:
        mov eax,dword ptr [ebx+108h]
    L_0043769c:
        mov ecx,dword ptr [esi]
    L_0043769e:
        push edi
    L_0043769f:
        mov dword ptr [esp+28h],edx
    L_004376a3:
        lea edx,[esp+20h]
    L_004376a7:
        mov dword ptr [esp+2Ch],eax
    L_004376ab:
        push edx
    L_004376ac:
        lea eax,[esp+1Ch]
    L_004376b0:
        push eax
    L_004376b1:
        push esi
    L_004376b2:
        mov dword ptr [esp+2Ch],edi
    L_004376b6:
        mov dword ptr [esp+30h],edi
    L_004376ba:
        call dword ptr [ecx+34h]
    L_004376bd:
        test eax,eax
    L_004376bf:
        je short L_004376cb
    L_004376c1:
        pop edi
    L_004376c2:
        xor al,al
    L_004376c4:
        pop esi
    L_004376c5:
        add esp,44h
    L_004376c8:
        ret 4
    L_004376cb:
        mov ecx,dword ptr [esp+14h]
    L_004376cf:
        mov eax,dword ptr [ebx+120h]
    L_004376d5:
        mov edx,dword ptr [esp+18h]
    L_004376d9:
        push ebp
    L_004376da:
        mov ebp,dword ptr [esp+30h]
    L_004376de:
        cmp ebp,dword ptr [ebx+100h]
    L_004376e4:
        mov dword ptr [esp+14h],ecx
    L_004376e8:
        mov ecx,dword ptr [ebx+110h]
    L_004376ee:
        mov dword ptr [esp+10h],ecx
    L_004376f2:
        jne short L_00437735
    L_004376f4:
        cmp dword ptr [ebx+108h],edi
    L_004376fa:
        mov dword ptr [esp+0Ch],edi
    L_004376fe:
        jle short L_00437735
    L_00437700:
        mov ebp,ecx
    L_00437702:
        shr ecx,2
    L_00437705:
        mov esi,eax
    L_00437707:
        mov edi,edx
    L_00437709:
        rep movsd
    L_0043770b:
        mov ecx,ebp
    L_0043770d:
        and ecx,3
    L_00437710:
        rep movsb
    L_00437712:
        mov esi,dword ptr [esp+14h]
    L_00437716:
        mov ecx,dword ptr [esp+10h]
    L_0043771a:
        mov edi,dword ptr [ebx+108h]
    L_00437720:
        add edx,esi
    L_00437722:
        mov esi,dword ptr [esp+0Ch]
    L_00437726:
        add eax,ecx
    L_00437728:
        inc esi
    L_00437729:
        cmp esi,edi
    L_0043772b:
        mov dword ptr [esp+0Ch],esi
    L_0043772f:
        jl short L_00437700
    L_00437731:
        mov esi,dword ptr [esp+54h]
    L_00437735:
        mov edx,dword ptr [esi]
    L_00437737:
        push esi
    L_00437738:
        call dword ptr [edx+38h]
    L_0043773b:
        pop ebp
    L_0043773c:
        pop edi
    L_0043773d:
        mov al,1
    L_0043773f:
        pop esi
    L_00437740:
        add esp,44h
    L_00437743:
        ret 4
    }
}
