#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x00413200..0x00413216: ScoreList_InsertAfter
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ScoreList_InsertAfter_00413200() {
    __asm {
    L_00413200:
        mov edx,dword ptr [ecx+4]
    L_00413203:
        test edx,edx
    L_00413205:
        je short L_00413210
    L_00413207:
        mov dword ptr [eax+4],edx
    L_0041320a:
        mov edx,dword ptr [ecx+4]
    L_0041320d:
        mov dword ptr [edx+8],eax
    L_00413210:
        mov dword ptr [ecx+4],eax
    L_00413213:
        mov dword ptr [eax+8],ecx
    L_00413216:
        ret
    }
}
