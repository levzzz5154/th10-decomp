#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x00412720..0x0041274F: Ecl_SetResourceSlot
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Ecl_SetResourceSlot_00412720() {
    __asm {
    L_00412720:
        mov eax,edx
    L_00412722:
        shl eax,4
    L_00412725:
        add eax,esi
    L_00412727:
        test ecx,ecx
    L_00412729:
        mov dword ptr [eax+2494h],ecx
    L_0041272f:
        jl short L_0041274d
    L_00412731:
        mov ecx,dword ptr [esp+4]
    L_00412735:
        add edx,24Ah
    L_0041273b:
        shl edx,4
    L_0041273e:
        mov dword ptr [eax+2498h],ecx
    L_00412744:
        mov dword ptr [eax+249Ch],edi
    L_0041274a:
        mov dword ptr [edx+esi],edi
    L_0041274d:
        ret 4
    }
}
