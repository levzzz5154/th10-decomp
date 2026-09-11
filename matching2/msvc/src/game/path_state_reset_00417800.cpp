#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x00417800..0x00417839: PathState_Reset
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_PathState_Reset_00417800() {
    __asm {
    L_00417800:
        mov ecx,dword ptr [eax+50h]
    L_00417803:
        xor edx,edx
    L_00417805:
        test cl,1
    L_00417808:
        jne short L_00417824
    L_0041780a:
        or ecx,1
    L_0041780d:
        mov dword ptr [eax+44h],edx
    L_00417810:
        mov dword ptr [eax+40h],0FFF0BDC1h
    L_00417817:
        mov dword ptr [eax+48h],edx
    L_0041781a:
        mov dword ptr [eax+4Ch],476F78h
    L_00417821:
        mov dword ptr [eax+50h],ecx
    L_00417824:
        mov dword ptr [eax+44h],edx
    L_00417827:
        mov dword ptr [eax+48h],edx
    L_0041782a:
        mov dword ptr [eax+40h],0FFFFFFFFh
    L_00417831:
        mov dword ptr [eax+58h],edx
    L_00417834:
        mov dword ptr [eax+5Ch],edx
    L_00417837:
        xor eax,eax
    L_00417839:
        ret
    }
}
