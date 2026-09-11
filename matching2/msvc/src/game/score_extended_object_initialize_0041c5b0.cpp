#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/game/score.hpp"

// 0x0041C5B0..0x0041C679: ScoreExtendedObject_Initialize
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ScoreExtendedObject_Initialize_0041c5b0() {
    __asm {
    L_0041c5b0:
        push esi
    L_0041c5b1:
        push edi
    L_0041c5b2:
        mov edx,ebx
    L_0041c5b4:
        call asm_ScoreObject_Initialize_0041c030
    L_0041c5b9:
        mov dword ptr [ebx],46DA60h
    L_0041c5bf:
        lea edx,[ebx+600h]
    L_0041c5c5:
        xor eax,eax
    L_0041c5c7:
        mov esi,0FFFFFFFEh
    L_0041c5cc:
        mov ecx,77h
    L_0041c5d1:
        lea edi,[ebx+424h]
    L_0041c5d7:
        rep stosd
    L_0041c5d9:
        and dword ptr [edx+6Ch],esi
    L_0041c5dc:
        and dword ptr [edx+0B0h],esi
    L_0041c5e2:
        and dword ptr [edx+0FCh],esi
    L_0041c5e8:
        and dword ptr [edx+128h],esi
    L_0041c5ee:
        and dword ptr [edx+174h],esi
    L_0041c5f4:
        and dword ptr [edx+1B0h],esi
    L_0041c5fa:
        and dword ptr [edx+1FCh],esi
    L_0041c600:
        and dword ptr [edx+228h],esi
    L_0041c606:
        and dword ptr [edx+378h],esi
    L_0041c60c:
        xor eax,eax
    L_0041c60e:
        mov edi,edx
    L_0041c610:
        mov ecx,0EBh
    L_0041c615:
        rep stosd
    L_0041c617:
        mov word ptr [edx+384h],0FFFFh
    L_0041c620:
        mov edi,dword ptr [ebx+0A18h]
    L_0041c626:
        lea edx,[ebx+9ACh]
    L_0041c62c:
        and edi,esi
    L_0041c62e:
        mov dword ptr [edx+6Ch],edi
    L_0041c631:
        and dword ptr [edx+0B0h],esi
    L_0041c637:
        and dword ptr [edx+0FCh],esi
    L_0041c63d:
        and dword ptr [edx+128h],esi
    L_0041c643:
        and dword ptr [edx+174h],esi
    L_0041c649:
        and dword ptr [edx+1B0h],esi
    L_0041c64f:
        and dword ptr [edx+1FCh],esi
    L_0041c655:
        and dword ptr [edx+228h],esi
    L_0041c65b:
        and dword ptr [edx+378h],esi
    L_0041c661:
        xor eax,eax
    L_0041c663:
        mov ecx,0EBh
    L_0041c668:
        mov edi,edx
    L_0041c66a:
        rep stosd
    L_0041c66c:
        pop edi
    L_0041c66d:
        mov word ptr [edx+384h],0FFFFh
    L_0041c676:
        mov eax,ebx
    L_0041c678:
        pop esi
    L_0041c679:
        ret
    }
}
