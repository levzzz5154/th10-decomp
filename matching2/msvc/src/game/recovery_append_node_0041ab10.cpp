#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x0041AB10..0x0041AB43: Recovery_AppendNode
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_AppendNode_0041ab10() {
    __asm {
    L_0041ab10:
        lea ecx,[eax+4]
    L_0041ab13:
        push esi
    L_0041ab14:
        cmp dword ptr [ecx],0
    L_0041ab17:
        je short L_0041ab2c
    L_0041ab19:
        lea esp,[esp+force_disp32_zero]
    L_0041ab20:
        mov eax,dword ptr [ecx]
    L_0041ab22:
        mov esi,dword ptr [eax+4]
    L_0041ab25:
        test esi,esi
    L_0041ab27:
        lea ecx,[eax+4]
    L_0041ab2a:
        jne short L_0041ab20
    L_0041ab2c:
        mov ecx,dword ptr [eax+4]
    L_0041ab2f:
        test ecx,ecx
    L_0041ab31:
        pop esi
    L_0041ab32:
        je short L_0041ab3d
    L_0041ab34:
        mov dword ptr [edx+4],ecx
    L_0041ab37:
        mov ecx,dword ptr [eax+4]
    L_0041ab3a:
        mov dword ptr [ecx+8],edx
    L_0041ab3d:
        mov dword ptr [eax+4],edx
    L_0041ab40:
        mov dword ptr [edx+8],eax
    L_0041ab43:
        ret
    }
}
