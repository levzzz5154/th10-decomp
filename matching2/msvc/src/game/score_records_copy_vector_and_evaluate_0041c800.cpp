#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/game/score.hpp"

// 0x0041C800..0x0041C84B: ?ScoreRecords_CopyVectorAndEvaluate@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ScoreRecords_CopyVectorAndEvaluate_0041c800() {
    __asm {
    L_0041c800:
        mov ecx,dword ptr [eax+18h]
    L_0041c803:
        push esi
    L_0041c804:
        add eax,440h
    L_0041c809:
        mov edx,ebx
    L_0041c80b:
        mov esi,dword ptr [edx]
    L_0041c80d:
        mov dword ptr [eax],esi
    L_0041c80f:
        mov esi,dword ptr [edx+4]
    L_0041c812:
        mov dword ptr [eax+4],esi
    L_0041c815:
        mov edx,dword ptr [edx+8]
    L_0041c818:
        push edi
    L_0041c819:
        xor edi,edi
    L_0041c81b:
        test ecx,ecx
    L_0041c81d:
        mov dword ptr [eax+8],edx
    L_0041c820:
        je short L_0041c845
    L_0041c822:
        push ebp
    L_0041c823:
        mov ebp,dword ptr [esp+10h]
    L_0041c827:
        cmp dword ptr [ecx+0Ch],1
    L_0041c82b:
        mov esi,dword ptr [ecx+8]
    L_0041c82e:
        je short L_0041c83e
    L_0041c830:
        mov edx,dword ptr [esp+14h]
    L_0041c834:
        mov eax,dword ptr [ecx]
    L_0041c836:
        push edx
    L_0041c837:
        push ebp
    L_0041c838:
        push ebx
    L_0041c839:
        call dword ptr [eax+1Ch]
    L_0041c83c:
        add edi,eax
    L_0041c83e:
        test esi,esi
    L_0041c840:
        mov ecx,esi
    L_0041c842:
        jne short L_0041c827
    L_0041c844:
        pop ebp
    L_0041c845:
        mov eax,edi
    L_0041c847:
        pop edi
    L_0041c848:
        pop esi
    L_0041c849:
        ret 8
    }
}
