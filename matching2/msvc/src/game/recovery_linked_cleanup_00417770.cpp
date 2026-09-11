#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x00417770..0x004177B1: RecoveryLinkedCleanup
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_RecoveryLinkedCleanup_00417770() {
    __asm {
    L_00417770:
        push esi
    L_00417771:
        mov esi,dword ptr [eax+18h]
    L_00417774:
        test esi,esi
    L_00417776:
        je short L_004177b0
    L_00417778:
        push edi
    L_00417779:
        lea esp,[esp+force_disp32_zero]
    L_00417780:
        mov edx,dword ptr [esi]
    L_00417782:
        mov edi,dword ptr [esi+8]
    L_00417785:
        mov ecx,esi
    L_00417787:
        call dword ptr [edx+10h]
    L_0041778a:
        mov eax,dword ptr [esi+4]
    L_0041778d:
        mov ecx,dword ptr [esi+8]
    L_00417790:
        mov dword ptr [eax+8],ecx
    L_00417793:
        mov eax,dword ptr [esi+8]
    L_00417796:
        test eax,eax
    L_00417798:
        je short L_004177a0
    L_0041779a:
        mov edx,dword ptr [esi+4]
    L_0041779d:
        mov dword ptr [eax+4],edx
    L_004177a0:
        push esi
    L_004177a1:
        call asm_free_004524a1
    L_004177a6:
        add esp,4
    L_004177a9:
        test edi,edi
    L_004177ab:
        mov esi,edi
    L_004177ad:
        jne short L_00417780
    L_004177af:
        pop edi
    L_004177b0:
        pop esi
    L_004177b1:
        ret
    }
}
