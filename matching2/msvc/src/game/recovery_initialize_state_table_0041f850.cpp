#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x0041F850..0x0041F8CF: Recovery_InitializeStateTable
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_InitializeStateTable_0041f850() {
    __asm {
    L_0041f850:
        mov dword ptr [esi+10h],4703E4h
    L_0041f857:
        lea edx,[esi+30h]
    L_0041f85a:
        xor eax,eax
    L_0041f85c:
        mov dword ptr [esi+14h],eax
    L_0041f85f:
        mov dword ptr [esi+18h],eax
    L_0041f862:
        mov dword ptr [esi+1Ch],eax
    L_0041f865:
        mov dword ptr [esi+20h],eax
    L_0041f868:
        mov ecx,dword ptr [edx+6Ch]
    L_0041f86b:
        mov eax,0FFFFFFFEh
    L_0041f870:
        and ecx,eax
    L_0041f872:
        mov dword ptr [edx+6Ch],ecx
    L_0041f875:
        push edi
    L_0041f876:
        and dword ptr [edx+0B0h],eax
    L_0041f87c:
        and dword ptr [edx+0FCh],eax
    L_0041f882:
        and dword ptr [edx+128h],eax
    L_0041f888:
        and dword ptr [edx+174h],eax
    L_0041f88e:
        and dword ptr [edx+1B0h],eax
    L_0041f894:
        and dword ptr [edx+1FCh],eax
    L_0041f89a:
        and dword ptr [edx+228h],eax
    L_0041f8a0:
        and dword ptr [edx+378h],eax
    L_0041f8a6:
        xor eax,eax
    L_0041f8a8:
        mov ecx,0EBh
    L_0041f8ad:
        mov edi,edx
    L_0041f8af:
        rep stosd
    L_0041f8b1:
        mov word ptr [edx+384h],0FFFFh
    L_0041f8ba:
        mov ecx,0FCh
    L_0041f8bf:
        mov edi,esi
    L_0041f8c1:
        rep stosd
    L_0041f8c3:
        or dword ptr [esi],2
    L_0041f8c6:
        mov dword ptr [data_00477820],esi
    L_0041f8cc:
        mov eax,esi
    L_0041f8ce:
        pop edi
    L_0041f8cf:
        ret
    }
}
